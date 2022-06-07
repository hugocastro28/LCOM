#include "timer_controller.h"

#include <stdint.h>

unsigned int game_time;
unsigned int timer_minutes;
unsigned int timer_seconds;

unsigned int time_before_pause;

extern unsigned int int_counter;
extern bool game_is_on;


void initialize_game_time() {
    game_time = 120;
    update_timer_units();
}

void timer_interrupt_handler() {
    timer_int_handler();
    if (int_counter % 60 == 0)
        decrease_game_time();
}

void decrease_game_time() {
    game_time--;
    update_timer_units();
    check_time_out();
}

void pause_game() {
    time_before_pause = game_time;
}

void continue_game() {
    game_time = time_before_pause;
    update_timer_units();
}

void increase_time() {
    game_time += 30;
    update_timer_units();
}

void check_time_out() {
    if (game_time == 0) 
        game_is_on = false;
}

void update_timer_units() {
    timer_minutes = game_time / 60;
    timer_seconds = game_time % 60;
}