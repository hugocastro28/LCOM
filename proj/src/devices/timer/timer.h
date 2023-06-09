#ifndef _LCOM_TIMER_H_
#define _LCOM_TIMER_H_

/**
 * Subscribes the timer interruptions.
 * 
*/
int (timer_subscribe_int)(uint8_t* bit_no);

/**
 * Unsubscribes the timer interruptions.
 * 
*/
int (timer_unsubscribe_int)();

/**
 * Increments the number of interrupts generated by the timer.
*/
void (timer_int_handler)();

/**
 * @brief Set the frequency of a given timer.
 * @param timer is the timer.
 * @param freq is the frequency.
 * 
 */
int (timer_set_frequency)(uint8_t timer, uint32_t freq);

/**
 * @brief reads the time configuration and stores it in a givern variable.
 * @param timer is the timer whose configuration will be read.
 * @param status is the variable that will be updated with the timer configuration.
 * 
 */
int (timer_get_conf)(uint8_t timer, uint8_t *st);

/**
 * @brief Displays the configuration of a timer.
 * 
 */
int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field);

#endif
