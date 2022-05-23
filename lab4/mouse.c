#include <lcom/lcf.h>

#include "mouse.h"
#include "i8042.h"
#include "utils.c"
#include <stdint.h>

int* mouse_hook_id;
int ih_success;
int packet_index;
uint8_t packet_bytes[3];


int (mouse_subscribe_int)(uint8_t *bit_no) {
  mouse_hook_id = (int*) malloc(sizeof(int));
  *mouse_hook_id = MOUSE_IRQ;
  *bit_no = MOUSE_IRQ;
  if (sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, mouse_hook_id) != 0)
    return 1;
  return 0;
}

int (mouse_unsubscribe_int)() {
  if (sys_irqrmpolicy(mouse_hook_id) != 0)
    return 1;
  return 0;
}

int (my_mouse_enable_data_reporting)() {
  for (int i = 0; i < 3; i++) {
    uint8_t* status = (uint8_t*) malloc(sizeof(uint8_t));
    if (util_sys_inb(ST_REG, status) != 0)
      return 1;

    if (*status & IBF)
      continue;

    if (sys_outb(KBC_CMD_REG, WRITE_MOUSE_BYTE) != 0)
      return 1;
    if (sys_outb(KBC_CMD_REG, ENABLE_DATA) != 0)
      return 1;

    uint8_t* acknowledgement = (uint8_t*) malloc(sizeof(uint8_t));
    if (util_sys_inb(OUT_BUF_REG, acknowledgement) != 0)
      return 1;
    if (*acknowledgement == ACK)
      return 0;
    if (*acknowledgement == ERROR)
      return 1;
  }
  return 1;
}

int (my_mouse_disable_data_reporting)() {
  for (int i = 0; i < 3; i++) {
    uint8_t* status = (uint8_t*) malloc(sizeof(uint8_t));
    if (util_sys_inb(ST_REG, status) != 0)
      return 1;

    if (*status & IBF)
      continue;

    if (sys_outb(KBC_CMD_REG, WRITE_MOUSE_BYTE) != 0)
      return 1;
    if (sys_outb(KBC_CMD_REG, DISABLE_DATA) != 0)
      return 1;

    uint8_t* acknowledgement = (uint8_t*) malloc(sizeof(uint8_t));
    if (util_sys_inb(OUT_BUF_REG, acknowledgement) != 0)
      return 1;
    if (*acknowledgement == ACK)
      return 0;
    if (*acknowledgement == ERROR)
      return 1;
  }
  return 1;
}

void (mouse_ih)() {
  ih_success = 0;

  uint8_t* status = (uint8_t*) malloc(sizeof(uint8_t));
  
  uint8_t* current_byte = (uint8_t*) malloc(sizeof(uint8_t));
  if (util_sys_inb(OUT_BUF_REG, current_byte) != 0) {
    ih_success = 1;
    return;
  }

  if (util_sys_inb(ST_REG, status) != 0) {
    ih_success = 1;
    return;
  }
  if (*status & (TO_ERR | PAR_ERR)) {
    ih_success = 1;
    return;
  }

  if ((packet_index == 0 && *current_byte & BIT(3)) || packet_index != 0) {
    packet_bytes[packet_index] = *current_byte;
    packet_index++;
  }
}

void (parse_mouse_packet)(struct packet* pp) {
  pp->bytes[0] = packet_bytes[0];
  pp->bytes[1] = packet_bytes[1];
  pp->bytes[2] = packet_bytes[2];

  pp->rb = packet_bytes[0] & RB;
  pp->mb = packet_bytes[0] & MB;
  pp->lb = packet_bytes[0] & LB;

  if (packet_bytes[0] & MSB_X)
    pp->delta_x = 0xFF00 | packet_bytes[1];
  pp->delta_x = packet_bytes[1];
  if (packet_bytes[0] & MSB_Y)
    pp->delta_y = 0xFF00 | packet_bytes[2];
  pp->delta_y = packet_bytes[2];

  pp->x_ov = packet_bytes[0] & X_OVFL;
  pp->y_ov = packet_bytes[0] & Y_OVFL;  
}
