#ifndef MOUSE_H
#define MOUSE_H

int (mouse_subscribe_int)();

int (mouse_unsubscribe_int)();

int (my_mouse_enable_data_reporting)();

int (my_mouse_disable_data_reporting)();

void (mouse_ih)();

#endif