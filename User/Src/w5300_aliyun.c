#include <string.h>
#include <stdio.h>

#include "w5300_aliyun.h"

#define MQTT_SOCKET_ID 2
#define mqtt_clientid "a13IqBFgbLz.w5300|securemode=2,signmethod=hmacsha256,timestamp=1690181173593|"
#define mqtt_username "w5300&a13IqBFgbLz"
#define mqtt_password "d830d732a20f973e1da736b674ba68b9d79f3d2661cf7781f48958e1ba6a63d3"
#define mqtt_port 1883

#define MQTT_SEND_BUFF_SIZE 2048
#define MQTT_RECV_BUFF_SIZE 2048
uint8_t mqtt_send_buff[MQTT_SEND_BUFF_SIZE] = {0};
uint8_t mqtt_recv_buff[MQTT_RECV_BUFF_SIZE] = {0};

Network network = {0};
MQTTClient mqtt = {0};

MQTTPacket_connectData mqtt_connect_data = MQTTPacket_connectData_initializer;

uint8_t aliyun_connected = 0;

void messageArrived(MessageData *md)
{
  MQTTMessage *message = md->message;

  printf("%.*s%s", (int)message->payloadlen, (char *)message->payload, "\r\n");
}

void aliyun_init(void)
{
  int ret;
  uint8_t mqttHostIp[4] = {101, 133, 196, 111};

  NewNetwork(&network, MQTT_SOCKET_ID);
  ConnectNetwork(&network, mqttHostIp, 1883);
  MQTTClientInit(&mqtt, &network, 1000, mqtt_send_buff, MQTT_SEND_BUFF_SIZE, mqtt_recv_buff, MQTT_RECV_BUFF_SIZE);
  mqtt_connect_data.willFlag = 0;
  mqtt_connect_data.MQTTVersion = 3;
  mqtt_connect_data.clientID.cstring = "a1bfjh2yQJ2.W5300|securemode=2,signmethod=hmacsha256,timestamp=1690791535565|";
  mqtt_connect_data.username.cstring = "W5300&a1bfjh2yQJ2";
  mqtt_connect_data.password.cstring = "10688625b5af51108c2352cb69375127255a21a3526b0aa5747c6ffae492a15c";
  mqtt_connect_data.keepAliveInterval = 30;
  mqtt_connect_data.cleansession = 1;
  ret = MQTTConnect(&mqtt, &mqtt_connect_data);
  printf("Connected %d\r\n", ret);
  if (ret != 0)
  {
    return;
  }
  ret = MQTTSubscribe(&mqtt, "/sys/a1bfjh2yQJ2/W5300/thing/service/property/set", QOS0, messageArrived);
  printf("Subscribed %d\r\n", ret);
  if (ret != 0)
  {
    return;
  }
  aliyun_connected = 1;
}

void aliyun_publish(uint8_t *payload)
{
  int ret;
  MQTTMessage msg;

  if (aliyun_connected == 1)
  {
    msg.qos = QOS0;
    msg.payload = payload;
    msg.payloadlen = strlen((char *)payload);

    ret = MQTTPublish(&mqtt, "/sys/a1bfjh2yQJ2/W5300/thing/event/property/post", &msg);
    printf("Publish %d\r\n", ret);
  }
}

void do_aliyun_run(void)
{
  MQTTYield(&mqtt, mqtt_connect_data.keepAliveInterval);
}
