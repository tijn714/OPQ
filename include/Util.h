#include <stdio.h>
#include <time.h>

#define clear() printf("\033[H\033[J")

void delay(int milliseconds) {
  clock_t time_end;
  time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
  while (clock() < time_end) {
  }
}
