/* 
 * File:   ecu_relay.h
 * Author: ENG HOSAM
 *
 * Created on July 18, 2023, 2:53 AM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H


/* ------------------Includes------------------*/
#include "ecu_relay_cfg.h"
#include "../../MCAL/GPIO/hal_gpio.h"
/* ------------------Macro Declarations------------------*/
#define RELAY_ON_STATUS 0x01U
#define RELAY_OFF_STATUS 0x00U

/* ------------------Macro Function Declarations------------------*/


/* ------------------Data Type Declarations------------------*/
typedef struct{
    uint8 relay_port   : 4;
    uint8 relay_pin    : 3;
    uint8 relay_status : 1;
}relay_t;
/* ------------------Software Interface Declarations------------------*/
Std_ReturnType relay_initialize(const relay_t *_relay);
Std_ReturnType relay_turn_on(const relay_t *_relay);
Std_ReturnType relay_turn_off(const relay_t *_relay);

#endif	/* ECU_RELAY_H */

