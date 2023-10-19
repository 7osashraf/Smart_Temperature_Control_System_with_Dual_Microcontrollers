/* 
 * File:   ecu_7_segment.h
 * Author: ENG HOSAM
 *
 * Created on July 21, 2023, 12:53 AM
 */

#ifndef ECU_7_SEGMENT_H
#define	ECU_7_SEGMENT_H

/* ------------------Includes------------------*/
#include "ecu_7_segment_cfg.h"
#include "../../MCAL/GPIO/hal_gpio.h"

/* ------------------Macro Declarations------------------*/
#define SEGMENT_PINO 0
#define SEGMENT_PIN1 1
#define SEGMENT_PIN2 2
#define SEGMENT_PIN3 3


/* ------------------Macro Function Declarations------------------*/


/* ------------------Data Type Declarations------------------*/
typedef enum{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE,
}segment_type_t;

typedef struct{
    pin_config_t segment_pins[4];
    segment_type_t segment_type;
}segment_t;

/* ------------------Software Interface Declarations------------------*/
Std_ReturnType seven_segment_initialize(const segment_t *seg);
Std_ReturnType seven_segment_write_number(const segment_t *seg, uint8 number);



#endif	/* ECU_7_SEGMENT_H */

