#ifndef __W5300_ALIYUN_H__
#define __W5300_ALIYUN_H__

#include "mqtt_interface.h"
#include "MQTTClient.h"

void aliyun_init(void);
void aliyun_publish(uint8_t *payload);
void do_aliyun_run(void);

#endif /* __W5300_ALIYUN_H__ */
