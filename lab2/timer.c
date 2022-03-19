#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_unsubscribe_int)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

void (timer_int_handler)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);
}

/* To be implemented by the students */
int (timer_get_conf)(uint8_t timer, uint8_t *st) {  
  if (timer != 0 && timer != 1 && timer != 2)
    return 1;
  
  uint8_t read_back_cmd = TIMER_RB_CMD | TIMER_RB_COUNT_| TIMER_RB_SEL(timer);
  sys_outb(0x43, (uint32_t) read_back_cmd);
  
  switch (timer) {
  case 0:
    if (util_sys_inb(TIMER_0, st) != 0)
      return 1;
    break;
  case 1:
    if (util_sys_inb(TIMER_1, st) != 0)
      return 1;
    break;
  case 2:
    if (util_sys_inb(TIMER_2, st) != 0)
      return 1;
  }
  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}
