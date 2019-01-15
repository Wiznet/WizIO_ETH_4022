#include <string.h>
#include <stdlib.h>
#include "socket.h"
#include "mqtt_interface.h"
#include "MQTTClient.h"
#include "w7500x.h"
#include "config_data.h"
#include "modbus.h"
#include "digital_handler.h"
#include "flash_handler.h"
#include "gpio_handler.h"
#include "timer_handler.h"
#include "uart_handler.h"
#include "remote_io.h"
#include "common.h"

//#define _MQTT_DEBUG_
//#define _REMOTE_IO_DEBUG_

Network g_mqtt_network;
MQTTClient g_mqtt_client;

uint8_t g_mqtt_init = 0;

extern uint8_t g_send_buf[WORK_BUF_SIZE];
extern uint8_t g_recv_buf[WORK_BUF_SIZE];

uint8_t g_data_buf[1024];

static int32_t ProcessModbusIO(uint8_t sock);
static void ProcessSockIO(uint8_t sock);
static void DataSubscribe(MessageData* md);

static void DataSubscribe(MessageData* md)
{
    struct __digital_out *digital = (struct __digital_out *) GetWIZIOPacketPointer()->digital_out;

    int subMessagelen = 0;

    MQTTMessage* mqttSubMessage = md->message;

    char *sArr[32] = { NULL, };
    char digital_out_alias[6][5] = { "DO10\0", "DO11\0", "DO12\0", "DO20\0", "DO21\0", "DO22\0" };
    char *ptr = NULL;
    uint8_t i = 0, j = 0;
    uint8_t key_count;

    subMessagelen = (int) mqttSubMessage->payloadlen;

#ifdef _MQTT_DEBUG_
    //printf("[APP] MQTT Subscribe Topic : %s, len : %d\r\n", (char*) mqttSubTopic->lenstring.data, subTopiclen);
    printf("[APP] MQTT Subscribe Payload : %s, len : %d\r\n", (char*) mqttSubMessage->payload, subMessagelen);
#endif

    ptr = strtok((char*) mqttSubMessage->payload, "{\":,} ");
    while (ptr != NULL) {
#ifdef _MQTT_DEBUG_
        printf("[APP] MQTT Subscribe Payload Split: %s\r\n", ptr);
#endif
        sArr[i] = ptr;
        i++;
        ptr = strtok(NULL, "{\":,} ");
    }
    key_count = i;

    for (i = 0; i < key_count; i += 2) {
        for (j = 0; j < 6; j++) {
            if (strstr(sArr[i], digital_out_alias[j])) {
                switch (j)
                {
                    case 0:
                        if (digital[0].use == ENABLE && digital[0].mode == kDO) {
                            if (atoi(sArr[i + 1])) {
                                SetDigitalOutHigh(0);
                            } else {
                                SetDigitalOutLow(0);
                            }
                        }
                        break;
                    case 1:
                        if (digital[0].use == ENABLE && digital[0].mode == kDOPulse) {
                            if (digital[0].high_width != atoi(sArr[i + 1])) {
                                digital[0].high_width = atoi(sArr[i + 1]);
                                PWM_Cmd(gk_DigitalOutPwmChannel[0], DISABLE);
                                InitDigitalOutWithPwm(0, digital[0].high_width, digital[0].low_width);
                            }
                        }
                        break;
                    case 2:
                        if (digital[0].use == ENABLE && digital[0].mode == kDOPulse) {
                            if (digital[0].low_width != atoi(sArr[i + 1])) {
                                digital[0].low_width = atoi(sArr[i + 1]);
                                PWM_Cmd(gk_DigitalOutPwmChannel[0], DISABLE);
                                InitDigitalOutWithPwm(0, digital[0].high_width, digital[0].low_width);
                            }
                        }
                        break;
                    case 3:
                        if (digital[1].use == ENABLE && digital[1].mode == kDO) {
                            if (atoi(sArr[i + 1])) {
                                SetDigitalOutHigh(1);
                            } else {
                                SetDigitalOutLow(1);
                            }
                        }
                        break;
                    case 4:
                        if (digital[1].use == ENABLE && digital[1].mode == kDOPulse) {
                            if (digital[1].high_width != atoi(sArr[i + 1])) {
                                digital[1].high_width = atoi(sArr[i + 1]);
                                PWM_Cmd(gk_DigitalOutPwmChannel[1], DISABLE);
                                InitDigitalOutWithPwm(1, digital[1].high_width, digital[1].low_width);
                            }
                        }
                        break;
                    case 5:
                        if (digital[1].use == ENABLE && digital[1].mode == kDOPulse) {
                            if (digital[1].low_width != atoi(sArr[i + 1])) {
                                digital[1].low_width = atoi(sArr[i + 1]);
                                PWM_Cmd(gk_DigitalOutPwmChannel[1], DISABLE);
                                InitDigitalOutWithPwm(1, digital[1].high_width, digital[1].low_width);
                            }
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

static void ProcessSockIO(uint8_t sock)
{
    struct __working_info *working = (struct __working_info *) &GetWIZIOPacketPointer()->working_info;
    struct __options *option = (struct __options *) &GetWIZIOPacketPointer()->options;
    struct __analog_in *ai = (struct __analog_in *) GetWIZIOPacketPointer()->analog_in;
    struct __digital_in *di = (struct __digital_in *) GetWIZIOPacketPointer()->digital_in;
    struct __mqtt_info *mqtt = (struct __mqtt_info *) &GetWIZIOPacketPointer()->mqtt_info;

    MQTTMessage mqttPubMessage;

    uint8_t sock_state, i, input_count = 0;
    uint16_t send_size, sent_size;
    int ret;
    char temp_buf[32] = { '\0', };

    char analog_in_alias[4][4] = { "AI1\0", "AI2\0", "AI3\0", "AI4\0" };
    char digital_in_alias[4][4] = { "DI1\0", "DI2\0", "DI3\0", "DI4\0" };

    /* Transfer Timer Process */
    if (g_interval_flag == 0) {
        return;
    }

    getsockopt(sock, SO_STATUS, &sock_state);

    if (sock_state != SOCK_UDP && sock_state != SOCK_ESTABLISHED) return;

    OnLed(kLED3);
    memset(g_data_buf, '\0', sizeof(g_data_buf));

    if (option->form == kRaw) {
        for (i = 0; i < ANALOG_IN_CHANNEL_NUM; i++) {
            if (ai[i].use == ENABLE) {
                if (input_count == 0) {
                    sprintf(temp_buf, "%s:%d", analog_in_alias[i], ai[i].value);
                } else {
                    sprintf(temp_buf, "%c%s:%d", option->separator, analog_in_alias[i], ai[i].value);
                }
                input_count++;
            }
            strcat(g_data_buf, temp_buf);
            memset(temp_buf, '\0', sizeof(temp_buf));
        }
        for (i = 0; i < DIGITAL_IN_CHANNEL_NUM; i++) {
            if (di[i].use == ENABLE) {
                if (input_count == 0) {
                    sprintf(temp_buf, "%s:%d", digital_in_alias[i], di[i].value);
                } else {
                    sprintf(temp_buf, "%c%s:%d", option->separator, digital_in_alias[i], di[i].value);
                }
                input_count++;
            }
            strcat(g_data_buf, temp_buf);
            memset(temp_buf, '\0', sizeof(temp_buf));
        }
        sprintf(temp_buf, "\r\n");
        strcat(g_data_buf, temp_buf);
    } else if (option->form == kJson) {
        sprintf(temp_buf, "{");
        strcat(g_data_buf, temp_buf);
        memset(temp_buf, '\0', sizeof(temp_buf));
        for (i = 0; i < ANALOG_IN_CHANNEL_NUM; i++) {
            if (ai[i].use == ENABLE) {
                if (input_count == 0) {
                    sprintf(temp_buf, "\"%s\":%d", analog_in_alias[i], ai[i].value);
                } else {
                    sprintf(temp_buf, "%c\"%s\":%d", option->separator, analog_in_alias[i], ai[i].value);
                }
                input_count++;
            }
            strcat(g_data_buf, temp_buf);
            memset(temp_buf, '\0', sizeof(temp_buf));
        }
        for (i = 0; i < DIGITAL_IN_CHANNEL_NUM; i++) {
            if (di[i].use == ENABLE) {
                if (input_count == 0) {
                    sprintf(temp_buf, "\"%s\":%d", digital_in_alias[i], di[i].value);
                } else {
                    sprintf(temp_buf, "%c\"%s\":%d", option->separator, digital_in_alias[i], di[i].value);
                }
                input_count++;
            }
            strcat(g_data_buf, temp_buf);
            memset(temp_buf, '\0', sizeof(temp_buf));
        }
        sprintf(temp_buf, "}\r\n");
        strcat(g_data_buf, temp_buf);
    }

    send_size = strlen(g_data_buf);
    sent_size = 0;

    if (sock_state == SOCK_UDP) {
        uint8_t remote_ip[4];
        memcpy(remote_ip, working->remote_ip, sizeof(remote_ip));
        while (sent_size != send_size) {
            ret = sendto(sock, g_data_buf + sent_size, send_size - sent_size, remote_ip, working->remote_port);
            if (ret < 0) {
#ifdef _REMOTE_IO_DEBUG_
                printf("[APP] sendto error. %ld\r\n", ret);  //for debugging
#endif
                OffLed(kLED3);
                return;
            }
            sent_size += ret;
        }
    } else if (sock_state == SOCK_ESTABLISHED) {
        if (working->mode == MQTT_MODE) {
            mqttPubMessage.payload = g_data_buf;
            mqttPubMessage.payloadlen = send_size;
            mqttPubMessage.qos = QOS0;
            mqttPubMessage.retained = 0;
            mqttPubMessage.dup = 0;
            ret = MQTTPublish(&g_mqtt_client, mqtt->publish_topic, &mqttPubMessage);
            if (ret != SUCCESSS) {
#ifdef _MQTT_DEBUG_
                printf("[APP] MQTT publish error. %ld\r\n", ret);
#endif
                OffLed(kLED3);
                return;
            }

        } else {
            while (sent_size != send_size) {
                ret = send(sock, g_data_buf + sent_size, send_size - sent_size);
                if (ret < 0) {
#ifdef _REMOTE_IO_DEBUG_
                    printf("[APP] send error. %ld\r\n", ret);  //for debugging
#endif
                    OffLed(kLED3);
                    return;
                }
                sent_size += ret;
            }

        }
    }
    g_interval_flag = 0;
    OffLed(kLED3);
}

static int32_t ProcessModbusIO(uint8_t sock)
{
    uint8_t sock_state;
    uint16_t recevie_size, send_size, sent_size;
    uint8_t destination_ip[4];
    uint16_t destination_port;
    int32_t ret;

    getsockopt(sock, SO_STATUS, &sock_state);
    if (sock_state != SOCK_UDP && sock_state != SOCK_ESTABLISHED) {
        return 0;
    }

    getsockopt(sock, SO_RECVBUF, (uint16_t*) &recevie_size);
    if (recevie_size == 0) {
        return 0;
    }

    OnLed(kLED3);
    if (sock_state == SOCK_UDP) {
        ret = recvfrom(sock, g_data_buf, recevie_size, destination_ip, (uint16_t*) &destination_port);
        if (ret <= 0) {
#ifdef _REMOTE_IO_DEBUG_
            printf("[APP] recvfrom error. %ld\r\n", ret);
#endif
            OffLed(kLED3);
            return ret;
        }

        send_size = ModbusSlave(g_data_buf);
        sent_size = 0;

        while (sent_size != send_size) {
            ret = sendto(sock, g_data_buf + sent_size, send_size - sent_size, destination_ip, destination_port);
            if (ret < 0) {
#ifdef _REMOTE_IO_DEBUG_
                printf("[APP] sendto error. %ld\r\n", ret);  //for debugging
#endif
                OffLed(kLED3);
                return ret;
            }
            sent_size += ret;
        }
    } else if (sock_state == SOCK_ESTABLISHED) {
        ret = recv(sock, g_data_buf, recevie_size);
        if (ret <= 0) {
#ifdef _REMOTE_IO_DEBUG_
            printf("[APP] recv error. %ld\r\n", ret);
#endif
            OffLed(kLED3);
            return ret;
        }

        send_size = ModbusSlave(g_data_buf);
        sent_size = 0;

        while (sent_size != send_size) {
            ret = send(sock, g_data_buf + sent_size, send_size - sent_size);
            if (ret < 0) {
#ifdef _REMOTE_IO_DEBUG_
                printf("[APP] send error. %ld\r\n", ret);  //for debugging
#endif
                OffLed(kLED3);
                return ret;
            }
            sent_size += ret;
        }
    }
    OffLed(kLED3);

    return 1;
}

static void ProcessRemoteIoSockClose(uint8_t sock)
{
    struct __working_info *working = (struct __working_info *) &GetWIZIOPacketPointer()->working_info;

    switch (working->mode)
    {
        case MQTT_MODE:
            if (g_mqtt_init == 0) {
                g_mqtt_init = 1;
                NewNetwork(&g_mqtt_network, sock);
            }
            g_mqtt_network.my_socket = sock;
            MQTTClientInit(&g_mqtt_client, &g_mqtt_network, 1000, g_send_buf, WORK_BUF_SIZE, g_recv_buf, WORK_BUF_SIZE);
            InitNetwork(&g_mqtt_network, working->local_port, SF_IO_NONBLOCK);
            break;
        case TCP_CLIENT_MODE:
        case TCP_SERVER_MODE:
        case MODBUS_TCP_MODE:
            socket(sock, Sn_MR_TCP, working->local_port, SF_IO_NONBLOCK);
            break;
        case UDP_MODE:
        case MODBUS_UDP_MODE:
            socket(sock, Sn_MR_UDP, working->local_port, SF_IO_NONBLOCK);
            break;
        default:
            break;
    }
}

static void ProcessRemoteIoSockInit(uint8_t sock)
{
    struct __working_info *working = (struct __working_info *) &(GetWIZIOPacketPointer()->working_info);
    uint8_t remote_ip[4];

    memcpy(remote_ip, working->remote_ip, sizeof(remote_ip));

    switch (working->mode)
    {
        case MQTT_MODE:
            if (!g_reconn_flag) {
                ConnectNetwork(&g_mqtt_network, remote_ip, working->remote_port);
                g_reconn_flag = 1;
            }
            break;
        case TCP_CLIENT_MODE:
            if (!g_reconn_flag) {
                connect(sock, remote_ip, working->remote_port);
                g_reconn_flag = 1;
            }
            break;
        case MODBUS_TCP_MODE:
        case TCP_SERVER_MODE:
            listen(sock);
            break;
        case MODBUS_UDP_MODE:
        case UDP_MODE:
            close(sock);
            break;

        default:
            break;
    }
}

static void ProcessRemoteIoSockListen(uint8_t sock)
{
    struct __working_info *working = (struct __working_info *) &GetWIZIOPacketPointer()->working_info;

    switch (working->mode)
    {
        case MQTT_MODE:
        case TCP_CLIENT_MODE:
            close(sock);
            break;
        case MODBUS_TCP_MODE:
        case TCP_SERVER_MODE:
            break;
        case MODBUS_UDP_MODE:
        case UDP_MODE:
            close(sock);
            break;
        default:
            break;
    }
}

static void ProcessRemoteIoEstablished(uint8_t sock)
{
    int ret;

    WIZIOPacket *value = GetWIZIOPacketPointer();

    MQTTPacket_connectData mqttConnectData = MQTTPacket_connectData_initializer;

    if (g_reconn_flag) g_reconn_flag = g_reconn_time = 0;

    switch (value->working_info.mode)
    {
        case TCP_SERVER_MODE:
        case MQTT_MODE:
            if (value->working_info.mode == MQTT_MODE) {
                if (getSn_IR(sock) & Sn_IR_CON) {
                    setSn_IR(sock, Sn_IR_CON);

                    mqttConnectData.MQTTVersion = 4;
                    mqttConnectData.clientID.cstring = value->options.module_name;
                    mqttConnectData.username.cstring = value->mqtt_info.user;
                    mqttConnectData.password.cstring = value->mqtt_info.pw;
                    mqttConnectData.willFlag = 0;
                    mqttConnectData.keepAliveInterval = 60;
                    mqttConnectData.cleansession = 1;

                    ret = MQTTConnect(&g_mqtt_client, &mqttConnectData);
                    if (ret != SUCCESSS) {
#ifdef _MQTT_DEBUG_
                        printf("[APP] MQTT connect error - ret : %d\r\n", ret);
#endif
                    }
                    if (strlen(value->mqtt_info.subscribe_topic) > 0) {
                        ret = MQTTSubscribe(&g_mqtt_client, value->mqtt_info.subscribe_topic, QOS0, (volatile) DataSubscribe);
#ifdef _MQTT_DEBUG_
                        if (ret != SUCCESSS) {
                            printf("[APP] MQTT subscribe error - ret : %d\r\n", ret);
                        }
#endif
                    }
                }
            }
        case TCP_CLIENT_MODE:
            if (value->working_info.mode == MQTT_MODE) {
                ret = MQTTYield(&g_mqtt_client, mqttConnectData.keepAliveInterval);
                if (ret != SUCCESSS) {
#ifdef _MQTT_DEBUG_
                    printf("[APP] MQTT yield error - ret : %d\r\n", ret);
#endif
                }
                ProcessSockIO(sock);
            } else {
                ProcessSockIO(sock);
            }

            if (g_link_status_flag == 0) {
                g_link_status_flag = 1;
            } else if (g_link_status_flag == 2) {
                g_link_status_flag = 0;

                if (PHY_GetLinkStatus() == PHY_LINK_OFF) {
#ifdef _REMOTE_IO_DEBUG_
                    printf("[APP] LINK OFF\r\n");
#endif
                    if (value->working_info.mode == MQTT_MODE) {
                        ret = MQTTDisconnect(&g_mqtt_client);

                        if (ret != SUCCESSS) {
#ifdef _MQTT_DEBUG_
                            printf("[APP] MQTT disconnect error - ret : %d\r\n", ret);
#endif
                        }
                        wizchip_disconnect(&g_mqtt_network);
                    } else {
                        disconnect(sock);
                        close(sock);
                    }
                }
            }
            break;
        case MODBUS_TCP_MODE:
            ProcessModbusIO(sock);
            if (g_link_status_flag == 0) {
                g_link_status_flag = 1;
            } else if (g_link_status_flag == 2) {
                g_link_status_flag = 0;

                if (PHY_GetLinkStatus() == PHY_LINK_OFF) {
#ifdef _REMOTE_IO_DEBUG_
                    printf("[APP] LINK OFF\r\n");
#endif
                    disconnect(sock);
                    close(sock);
                }
            }
            break;
        case MODBUS_UDP_MODE:
        case UDP_MODE:
            close(sock);
            break;

        default:
            break;
    }
}

static void ProcessRemoteIoSockClosewait(uint8_t sock)
{
    struct __working_info *working = (struct __working_info *) &GetWIZIOPacketPointer()->working_info;
    int ret;

    switch (working->mode)
    {
        case MQTT_MODE:
            ret = MQTTDisconnect(&g_mqtt_client);
            if (ret != SUCCESSS) {
#ifdef _MQTT_DEBUG_
                printf("[APP] MQTT disconnect error - ret : %d\r\n", ret);
#endif
            }
            wizchip_disconnect(&g_mqtt_network);
            close(sock);
            break;
        case TCP_CLIENT_MODE:
        case TCP_SERVER_MODE:
        case MODBUS_TCP_MODE:
        case MODBUS_UDP_MODE:
        case UDP_MODE:
            disconnect(sock);
            close(sock);
            break;
        default:
            break;
    }
}

static void ProcessRemoteIoSockUdp(uint8_t sock)
{
    struct __working_info *working = (struct __working_info *) &GetWIZIOPacketPointer()->working_info;

    switch (working->mode)
    {
        case MQTT_MODE:
        case TCP_CLIENT_MODE:
        case TCP_SERVER_MODE:
        case MODBUS_TCP_MODE:
            close(sock);
            break;
        case UDP_MODE:
            ProcessSockIO(sock);
            break;
        case MODBUS_UDP_MODE:
            ProcessModbusIO(sock);
            break;
        default:
            break;
    }
}

void RunRemoteIO(uint8_t sock)
{
    struct __working_info *working = (struct __working_info *) &(GetWIZIOPacketPointer()->working_info);
    uint8_t sock_state;

    getsockopt(sock, SO_STATUS, &sock_state);

    /* Network State Process */
    switch (working->state)
    {
        case kNetDisconnect:
            if (sock_state == SOCK_UDP) {
                working->state = kNetUdp;
            } else if (sock_state == SOCK_ESTABLISHED) {
                working->state = kNetConnect;
                OnLed(kLED2);
            }
            break;

        case kNetConnect:
            if (sock_state != SOCK_ESTABLISHED) {
                working->state = kNetDisconnect;
                OffLed(kLED2);
            }
            break;

        case kNetUdp:
            if (sock_state != SOCK_UDP) {
                working->state = kNetDisconnect;
                OffLed(kLED2);
            }
            break;

        default:
            working->state = kNetDisconnect;
            OffLed(kLED2);
            break;
    }

    switch (sock_state)
    {
        case SOCK_CLOSED:
            ProcessRemoteIoSockClose(sock);
            break;

        case SOCK_INIT:
            ProcessRemoteIoSockInit(sock);
            break;

        case SOCK_LISTEN:
            ProcessRemoteIoSockListen(sock);
            break;

        case SOCK_ESTABLISHED:
            ProcessRemoteIoEstablished(sock);
            break;

        case SOCK_CLOSE_WAIT:
            ProcessRemoteIoSockClosewait(sock);
            break;

        case SOCK_UDP:
            ProcessRemoteIoSockUdp(sock);
            break;

        default:
            break;
    }
}
