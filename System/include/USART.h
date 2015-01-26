/*-----------------------------------------------------------------------------
 * 
 * Released: <2010/03/25>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description: 
 * 
 *-----------------------------------------------------------------------------
 */

#ifndef _USART_H_
#define _USART_H_

#include "Types.h"

  void USART_Initialize(uint8, uint32);
  void USART_Reset(uint8);
  bool USART_IsAvailable(uint8);
  int8 USART_Receive(uint8);
  void USART_Send(uint8, int8);

#endif
