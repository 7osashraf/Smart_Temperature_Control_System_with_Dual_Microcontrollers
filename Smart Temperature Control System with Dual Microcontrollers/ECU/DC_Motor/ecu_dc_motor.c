/* 
 * File:   ecu_dc_motor_cfg.h
 * Author: ENG HOSAM
 *
 * Created on July 18, 2023, 9:14 PM
 */

#include "ecu_dc_motor.h"

static pin_config_t motor_pin1;
static pin_config_t motor_pin2;

/**
 * @brief Initialize the assigned pin to be OUTPUT and turn the motor OFF or ON.
 * @param _dc_motor
 * @return Status of the function 
 *         (E_OK)  :  The function done successfully
 *         (E_NOT_OK)  :  The function has issue to perform this action
 */
Std_ReturnType dc_motor_initialize(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor){
       ret = E_NOT_OK; 
    }
    else{
         gpio_pin_initialize(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]));
         gpio_pin_initialize(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]));
    }
    return ret;
}
/**
 * @brief Move the motor to the right direction
 * @param _dc_motor
 * @return Status of the function 
 *         (E_OK)  :  The function done successfully
 *         (E_NOT_OK)  :  The function has issue to perform this action
 */
Std_ReturnType dc_motor_move_right(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor){
       ret = E_NOT_OK; 
    }
    else{
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_HIGH);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_LOW);
    }
    return ret;
}
/**
 * @brief Move the motor to the left direction
 * @param _dc_motor
 * @return Status of the function 
 *         (E_OK)  :  The function done successfully
 *         (E_NOT_OK)  :  The function has issue to perform this action
 */
Std_ReturnType dc_motor_move_left(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor){
       ret = E_NOT_OK; 
    }
    else{
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_LOW);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_HIGH);
    }
       
    return ret;
}
/**
 * 
 * @brief stop the motor
 * @param _dc_motor
 * @return Status of the function 
 *         (E_OK)  :  The function done successfully
 *         (E_NOT_OK)  :  The function has issue to perform this action
 */
Std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor){
       ret = E_NOT_OK; 
    }
    else{
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_LOW);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_LOW);
    }
    return ret;
}
