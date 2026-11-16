#include <msp430.h>
#include "led.h"
#include "buzzer.h"
#include "stateMachines.h"

/* State 0: siren -- pitch sweeps up and down, red LED bright */
static void siren()
{
  static short period = 1000;
  static char going_up = 1;

  P1OUT |= LED_RED;
  P1OUT &= ~LED_GREEN;

  if (going_up) period += 20; else period -= 20;
  if (period >= 4000) going_up = 0;
  if (period <= 1000) going_up = 1;
  buzzer_set_period(period);
}

/* State 1: red and green alternate (bright) every half second, with a chirp */
static void blink()
{
  static int count = 0;
  static char red_turn = 1;

  if (++count >= 125) {          /* 125 ticks = 0.5 sec */
    count = 0;
    red_turn = !red_turn;
  }
  if (red_turn) { P1OUT |= LED_RED;   P1OUT &= ~LED_GREEN; }
  else          { P1OUT |= LED_GREEN; P1OUT &= ~LED_RED;   }

  buzzer_set_period(count < 10 ? 2000 : 0);   /* short chirp on each switch */
}

/* State 2: both LEDs dim -- on 1 tick out of every 4 (25% duty cycle), silent */
static void dim()
{
  static char c = 0;

  if (++c >= 4) c = 0;
  if (c == 0) P1OUT |= LEDS;
  else        P1OUT &= ~LEDS;
  buzzer_set_period(0);
}

/* State 3: play a scale; LEDs swap on every note */
static const short notes[] = {3822, 3405, 3034, 2863, 2551, 2273, 2025, 1911}; /* C5..C6 */

static void song()
{
  static char note = 0;
  static char count = 0;

  if (++count >= 50) {           /* 50 ticks = 0.2 sec per note */
    count = 0;
    if (++note >= 8) note = 0;
  }
  if (note & 1) { P1OUT |= LED_GREEN; P1OUT &= ~LED_RED;   }
  else          { P1OUT |= LED_RED;   P1OUT &= ~LED_GREEN; }
  buzzer_set_period(notes[note]);
}

void state_advance()
{
  switch (state) {
  case 0: siren(); break;
  case 1: blink(); break;
  case 2: dim();   break;
  case 3: song();  break;
  }
}
