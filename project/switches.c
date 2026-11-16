#include <msp430.h>
#include "switches.h"
#include "buzzer.h"
#include "stateMachines.h"

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

  /* buttons read 0 when pressed */
  if      (!(p2val & SW1)) transition(0);
  else if (!(p2val & SW2)) transition(1);
  else if (!(p2val & SW3)) transition(2);
  else if (!(p2val & SW4)) transition(3);
}


void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {         
    P2IFG &= ~SWITCHES;            
    switch_interrupt_handler();   
  }
}
