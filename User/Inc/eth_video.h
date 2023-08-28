#ifndef __ETH_VIDEO_H__
#define __ETH_VIDEO_H__

#include "socket.h"

void eth_video_init(void);
void eth_video_run(void);
uint16_t *get_video_rgb565(void);
void demo_run(void);

#endif /* __ETH_VIDEO_H__ */
