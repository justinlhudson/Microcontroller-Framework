#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "../include/Types.h"
#include "../include/Definitions.h"

#include "../include/USART.h"

#include "Core/include/Configuration.h"

#define UART_BAUD_SELECT(b)     ( ((CPU_CLOCK_HZ)/((b)*16)) -1)
// Used with async operation ONLY!
#define UART_BAUD_SELECT_2X(b)     ( (((CPU_CLOCK_HZ)/((b)*8)) -1)|0x8000)

struct USART_t
{
  int8 buffer[USART_BUFFER_LENGTH];
  uint8 count;
  uint8 offset;
} USART[NUMBER_USARTS];

void USART_Initialize(uint8 usart, uint32 baud)
{
  #if CPU_CLOCK_HZ > 115200
    uint16 brr = UART_BAUD_SELECT_2X(baud);
  #else
    uint16 brr = UART_BAUD_SELECT(baud);
  #endif

  CRITICAL_SECTION_ENTER();
  {
    if(usart == 0)
    {
      UBRR0 = 0;

      #if CPU_CLOCK_HZ > 115200
        UCSR0A = (1<<U2X0);  // enable 2x speed change
      #else
        UCSR0A = (0<<U2X0);
      #endif
      //Enable Tx and Rx, and interrupt on Rx
      UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0)|(0<<UDRIE0);
      //set baud
      UBRR0H = (uint8)(brr>>8);
      UBRR0L = (uint8)brr;
      //UBRR0 = brr;

      //Set frame format: 8data, parity 'none',1stop bit, on falling edge
      UCSR0C = (0<<UMSEL00)|(0<<UMSEL01)|(0<<UPM00)|(0<<USBS0)|(0<<UCSZ02)|(1<<UCSZ01)|(1<<UCSZ00)|(0<<UCPOL0);
    }
    USART_Reset(usart);
  }
  CRITICAL_SECTION_EXIT();
}

void USART_Reset(uint8 usart)
{
  USART[usart].count = 0;
  USART[usart].offset = 0;

  //flush register
  if(usart == 0)
  {
    do
    {
      int8 flushReg = 0;
      flushReg = UDR0;  //clear by reading
      (void)flushReg;
    }while((UCSR0A & (1<<RXC0)));  //go until register empty, or timeout
  }
}

bool USART_IsAvailable(uint8 usart)
{
  bool status = false;

  if(USART[usart].offset != USART[usart].count)
    status = true;

  return status;
}

void USART_Send(uint8 usart, int8 value)
{    
  if(usart == 0)
  {
    // Wait for empty transmit buffer flag
    while(!(UCSR0A & (1<<UDRE0))) NOP;

    // Put data into buffer, sends the data
    UDR0 = value;
  }
}

int8 USART_Receive(uint8 usart)
{  
  int8 result = '\0';

  if(USART_IsAvailable(usart))
  {
    result = USART[usart].buffer[USART[usart].offset];

    USART[usart].offset++;
    if(USART[usart].offset >= USART_BUFFER_LENGTH)
      USART[usart].offset = 0;
  }

  return result;
}

ISR(USART_RX_vect)
{
  CRITICAL_SECTION_ENTER();
  {
    //Wait for empty transmit buffer
    while(!(UCSR0A & (1<<UDRE0))) NOP;

    //Wait for data to be received
    while(!(UCSR0A & (1<<RXC0))) NOP;

    do
    {
      //if no frame, data flow, or parity error 
      //if(!(UCSR0A & ( (1<<FE0) | (1<<DOR0) | (1<<UPE0) )))
      {
        USART[0].buffer[USART[0].count] = UDR0;

        USART[0].count++;
        if(USART[0].count >= USART_BUFFER_LENGTH)  //circle around
          USART[0].count = 0;
      }
    }while((UCSR0A & (1<<RXC0)));  //go until register empty
  }
  CRITICAL_SECTION_EXIT();
}