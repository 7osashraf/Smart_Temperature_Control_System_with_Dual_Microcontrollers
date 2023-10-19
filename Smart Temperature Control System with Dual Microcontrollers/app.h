/* 
 * File:   app.h
 * Author: ENG HOSAM
 *
 * Created on July 4, 2023, 1:58 AM
 */

#ifndef APP_H
#define	APP_H




/*  Section : includes   */

#include "ECU/LED/ecu_led.h"
#include "ECU/button/ecu_button.h"
#include "ECU/Relay/ecu_relay.h"
#include "ECU/DC_Motor/ecu_dc_motor.h"
#include "ECU/7_segment/ecu_7_segment.h"
#include "ECU/KeyPad/ecu_keypad.h"
#include "ECU/Chr_LCD/ecu_chr_lcd.h"
#include "MCAL/Interrupt/mcal_external_interrupt.h"
#include "MCAL/EEPROM/hal_eeprom.h"
#include "MCAL/ADC/hal_adc.h"
#include "MCAL/usart/hal_usart.h"

/*  Section : Macro Declarations   */

/*  Section : Macro Functions Declarations   */

/*  Section : Data Type Declarations   */

/*  Section : Function Declarations  */
void app_initialize(void);
uint8 StringToUint8(const char *str); 


#endif	/* APP_H */

