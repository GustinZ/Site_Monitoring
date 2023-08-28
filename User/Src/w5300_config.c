#include <stdio.h>
#include <string.h>
#include "w5300.h"
#include "main.h"
#include "w5300_config.h"

uint16_t w5300_bus_rb_cbfunc(uint32_t addr)
{
  return (*((volatile unsigned short *)addr));
}

void w5300_bus_wb_cbfunc(uint32_t addr, uint16_t wb)
{
  *((volatile unsigned short *)addr) = wb;
}

void w5300_reset(void)
{
//  HAL_GPIO_WritePin(W5300_RESET_GPIO_Port, W5300_RESET_Pin, GPIO_PIN_RESET);
//  HAL_Delay(100);
//  HAL_GPIO_WritePin(W5300_RESET_GPIO_Port, W5300_RESET_Pin, GPIO_PIN_SET);
//  HAL_Delay(100);
}

int w5300_init(void)
{
  unsigned short version;
  int retry_count = 0;
  uint8_t txsize[8];
  uint8_t rxsize[8];

  wiz_NetInfo netinfo = {
      .mac = {0x00, 0x08, 0xdc, 0x11, 0x22, 0x33},
      .ip = {192, 168, 124, 233},
      .sn = {255, 255, 255, 0},
      .gw = {192, 168, 124, 1},
      .dhcp = NETINFO_STATIC};

  memset(txsize, 8, 8);
  memset(rxsize, 8, 8);

  reg_wizchip_bus_cbfunc(w5300_bus_rb_cbfunc, w5300_bus_wb_cbfunc);

  wizchip_init(txsize, rxsize);

  w5300_reset();

  do
  {
    HAL_Delay(500);
    version = getIDR();
    retry_count++;
  } while (version != 0x5300 && retry_count < 10);

  if (version != 0x5300)
  {
    printf("version error\r\n");
    return -1;
  }

 while (1)
 {
   if (HAL_GPIO_ReadPin(W5300_LINK_GPIO_Port, W5300_LINK_Pin) != GPIO_PIN_RESET)
   {
     printf(". ");
   }
   else
   {
     break;
   }
   HAL_Delay(500);
 }
  printf("\r\n");
  printf("phy link ok\r\n");

  wizchip_setnetinfo(&netinfo);

  wizchip_getnetinfo(&netinfo);
  printf("mac: %02X%02X%02X%02X%02X%02X\r\n", netinfo.mac[0], netinfo.mac[1], netinfo.mac[2],
         netinfo.mac[3], netinfo.mac[4], netinfo.mac[5]);
  printf("ip: %d.%d.%d.%d\r\n", netinfo.ip[0], netinfo.ip[1], netinfo.ip[2], netinfo.ip[3]);
  printf("sn: %d.%d.%d.%d\r\n", netinfo.sn[0], netinfo.sn[1], netinfo.sn[2], netinfo.sn[3]);
  printf("gw: %d.%d.%d.%d\r\n", netinfo.gw[0], netinfo.gw[1], netinfo.gw[2], netinfo.gw[3]);

  return 0;
}
