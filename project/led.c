#include <msp430.h>
#include "led.h"

void led_init()
{
  P1DIR |= LEDS;            
  P1OUT &= ~LED_GREEN;       
  P1OUT |= LED_RED;          
}
