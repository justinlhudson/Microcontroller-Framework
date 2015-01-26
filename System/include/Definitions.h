/*-----------------------------------------------------------------------------
 * 
 * Released: <2010/03/25>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description: 
 * 
 *-----------------------------------------------------------------------------
 */

#ifndef _DEFINITIONS_H
#define _DEFINITIONS_H

#include <avr/interrupt.h>

#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

//enable and disable interrupts
#define CRITICAL_SECTION_ENTER()          cli()
#define CRITICAL_SECTION_EXIT()           sei()

//inputs are double
#define DELAY_MS(X)                       _delay_ms(X)
#define DELAY_US(X)                       _delay_us(X)

#endif
