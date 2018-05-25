#ifndef _TIME_H_
#define _TIME_H_

void timer_handler();
int ticks_elapsed();
int seconds_elapsed();
extern int get_hour();
extern int get_minutes();
extern int get_seconds();
extern void beep();

#endif
