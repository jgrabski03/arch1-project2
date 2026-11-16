#ifndef stateMachines_included
#define stateMachines_included

extern int state;             /* current toy state (defined in transition.s) */
void transition(int button);  /* written in assembly: button 0-3 -> new state */
void state_advance();         /* called 250x/sec by the watchdog interrupt */

#endif
