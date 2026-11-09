#include <msp430.h>
#include "switches.h"
#include "buzzer.h"

static char switch_update_interrupt_sense()
{
  char p2val = P2IN;
  P2IES |= (p2val & SWITCHES);    
  P2IES &= (p2val | ~SWITCHES);    
  return p2val;
}

void switch_init()
{
  P2REN |= SWITCHES;               
  P2IE  |= SWITCHES;               
  P2OUT |= SWITCHES;               
  P2DIR &= ~SWITCHES;              
  switch_update_interrupt_sense();
}

void switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();

  if      (!(p2val & SW1)) buzzer_set_period(4000);   
  else if (!(p2val & SW2)) buzzer_set_period(2000);   
  else if (!(p2val & SW3)) buzzer_set_period(1000);   
  else if (!(p2val & SW4)) buzzer_set_period(500);    
  else                     buzzer_set_period(0);      
}


void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {         
    P2IFG &= ~SWITCHES;            
    switch_interrupt_handler();   
  }
}
