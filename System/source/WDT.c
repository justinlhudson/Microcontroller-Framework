#include <avr/interrupt.h>
#include <avr/wdt.h>

#include "../include/Definitions.h"
#include "../include/WDT.h"

#include "Core/include/Configuration.h"

uint8_t mcusr_mirror __attribute__ ((section (".noinit")));


// disable watch dog on reset event!!!  (per avr/wdt.h)
void get_mcusr(void) \
  __attribute__((naked)) \
  __attribute__((section(".init3")));
void get_mcusr(void)
{
  mcusr_mirror = MCUSR;
  MCUSR = 0;
  wdt_disable();
}

uint8 WDT_PrescalerChange(uint32);

void WDT_Reset(void) 
{ 
  wdt_reset();
}

void WDT_On(uint16 timeout)
{
  CRITICAL_SECTION_ENTER();
  {
    wdt_enable(WDT_PrescalerChange(timeout));
    wdt_reset();
  }
  CRITICAL_SECTION_EXIT();
}

void WDT_Off(void)
{
  CRITICAL_SECTION_ENTER();
  {
    wdt_reset();
    wdt_disable();
  }
  CRITICAL_SECTION_EXIT();
}

uint8 WDT_PrescalerChange(uint32 timeout)
{
  uint8 scale = 0x00;
  //msec
  switch(timeout)
  {
    case 16:
      scale = WDTO_15MS;
      break;
    case 32:
      scale = WDTO_30MS;
      break;
    case 64:
      scale = WDTO_60MS;
      break;
    case 125:
      scale = WDTO_120MS;
      break;
    case 250:
      scale = WDTO_250MS;
      break;
    case 500:
      scale = WDTO_500MS;
      break;
    case 1000:
      scale = WDTO_1S;
      break;
    case 2000:
      scale = WDTO_2S;
      break;
    default:
      scale = WDTO_2S;
      break;
  }   
  return scale;
}