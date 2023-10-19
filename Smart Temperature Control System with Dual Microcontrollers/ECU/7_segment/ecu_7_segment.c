/* 
 * File:   ecu_7_segment.c
 * Author: ENG HOSAM
 *
 * Created on July 21, 2023, 12:53 AM
 */

#include "ecu_7_segment.h"

/**
 * 
 * @param seg
 * @return Status of the function 
 *         (E_OK)  :  The function done successfully
 *         (E_NOT_OK)  :  The function has issue to perform this action
 */
Std_ReturnType seven_segment_initialize(const segment_t *seg){
    Std_ReturnType ret = E_OK;
    if(NULL == seg){
       ret = E_NOT_OK; 
    }
    else{
        ret = gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PINO]));
        ret = gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PIN1]));
        ret = gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PIN2]));
        ret = gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PIN3]));
    }
    return ret;
}
/**
 * 
 * @param seg
 * @param number
 * @return Status of the function 
 *         (E_OK)  :  The function done successfully
 *         (E_NOT_OK)  :  The function has issue to perform this action
 */
Std_ReturnType seven_segment_write_number(const segment_t *seg, uint8 number){
    Std_ReturnType ret = E_OK;
    if((NULL == seg) && (number > 9)){
       ret = E_NOT_OK; 
    }
    else{
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PINO]), (number & 0x01));
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN1]), ((number >> 1) & 0x01));
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN2]), ((number >> 2) & 0x01));
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN3]), ((number >> 3) & 0x01));
    }
    return ret;
}