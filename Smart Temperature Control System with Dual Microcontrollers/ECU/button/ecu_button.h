/* 
 * File:   ecu_button.h
 * Author: ENG HOSAM
 *
 * Created on July 17, 2023, 1:30 AM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/* ------------------Includes------------------*/
#include "../../MCAL/GPIO/hal_gpio.h"
#include "ecu_button_cfg.h"



/* ------------------Macro Declarations------------------*/


/* ------------------Macro Function Declarations------------------*/


/* ------------------Data Type Declarations------------------*/
typedef enum{
    BUTTON_PRESSED,
    BUTTON_RELEASED
}button_state_t;
typedef enum{
    BUTTON_ACTIVE_HIGH,
    BUTTON_ACTIVE_LOW
}button_active_t;

typedef struct{
    pin_config_t button_pin;
    button_state_t button_state;
    button_active_t button_connection;
}button_t;

/* ------------------Software Interface Declarations------------------*/
Std_ReturnType button_initialize(const button_t *btn);
Std_ReturnType button_read_satae(const button_t *btn, button_state_t *btn_state);


#endif	/* ECU_BUTTON_H */

