/* 
 * File:   app.c
 * Author: ENG HOSAM
 *
 * Created on July 4, 2023, 12:50 AM
 */



#include "app.h"



uint16 lm35_res_1, lm35_res_1_celsius = 0;
uint8 lm35_res_2_txt[7];
uint8 result;

chr_lcd_4bit_t lcd_1 = {
    .lcd_rs.port = PORTD_INDEX,
    .lcd_rs.pin = GPIO_PIN0,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_rs.logic = GPIO_LOW,
    .lcd_en.port = PORTD_INDEX,
    .lcd_en.pin = GPIO_PIN1,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_en.logic = GPIO_LOW,
    .lcd_data[0].port = PORTD_INDEX,
    .lcd_data[0].pin = GPIO_PIN2,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[0].logic = GPIO_LOW,
    .lcd_data[1].port = PORTD_INDEX,
    .lcd_data[1].pin = GPIO_PIN3,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].logic = GPIO_LOW,
    .lcd_data[2].port = PORTD_INDEX,
    .lcd_data[2].pin = GPIO_PIN4,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].logic = GPIO_LOW,
    .lcd_data[3].port = PORTD_INDEX,
    .lcd_data[3].pin = GPIO_PIN5,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[3].logic = GPIO_LOW
};
dc_motor_t motor_1 = {
  .dc_motor_pin[0].port = PORTC_INDEX,
  .dc_motor_pin[0].pin = GPIO_PIN0,
  .dc_motor_pin[0].logic = DC_MOTOR_OFF_STATUS,
  .dc_motor_pin[0].direction = GPIO_DIRECTION_OUTPUT,
  .dc_motor_pin[1].port = PORTC_INDEX,
  .dc_motor_pin[1].pin = GPIO_PIN1,
  .dc_motor_pin[1].logic = DC_MOTOR_OFF_STATUS,
  .dc_motor_pin[1].direction = GPIO_DIRECTION_OUTPUT
          
};
void usart_module_init(){
    usart_t usart_obj;
    Std_ReturnType ret = E_NOT_OK;
    
    usart_obj.baudrate = 9600;
    usart_obj.baudrate_gen_gonfig = BAUDRATE_ASYN_8BIT_lOW_SPEED;
    
    usart_obj.usart_tx_cfg.usart_tx_enable = EUSART_ASYNCHRONOUS_TX_ENABLE;
    usart_obj.usart_tx_cfg.usart_tx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE;
    usart_obj.usart_tx_cfg.usart_tx_9bit_enable = EUSART_ASYNCHRONOUS_9Bit_TX_DISABLE;
    
    usart_obj.usart_rx_cfg.usart_rx_enable = EUSART_ASYNCHRONOUS_RX_ENABLE;
    usart_obj.usart_rx_cfg.usart_rx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE;
    usart_obj.usart_rx_cfg.usart_rx_9bit_enable = EUSART_ASYNCHRONOUS_9Bit_RX_DISABLE;
    
    usart_obj.EUSART_TxDefaultInterruptHandler = NULL;
    usart_obj.EUSART_RxDefaultInterruptHandler = NULL;
    usart_obj.EUSART_FramingErrorHandler = NULL;
    usart_obj.EUSART_OverrunErrorHandler = NULL;
    
    ret = EUSART_ASYNC_Init(&usart_obj);
}

uint8 rec_usart_data;
int main() {
    
    Std_ReturnType ret = E_NOT_OK;
    
    app_initialize();
    
    ret = lcd_4bit_send_string_pos(&lcd_1, 1, 2, "LM35 Project Start");
    
    ret = lcd_4bit_send_string_pos(&lcd_1, 2, 1, "Temp ");
    
    while(1){
        
        ret = EUSART_ASYNC_ReadStringBlocking(lm35_res_2_txt, 7);
        
        ret = lcd_4bit_send_string_pos(&lcd_1, 2, 8, lm35_res_2_txt);
        
        result = StringToUint8(lm35_res_2_txt);
        
        
        if(result >= 25){
            ret = dc_motor_move_right(&motor_1);
        }
        else{
            ret = dc_motor_stop(&motor_1);
        }
        
    }
    return (EXIT_SUCCESS);
}

void app_initialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ret = lcd_4bit_initialize(&lcd_1);
    ret = dc_motor_initialize(&motor_1);
    usart_module_init();
    
    
}

uint8 StringToUint8(const char *str){
    uint8 result = 0;
    uint8 sign = 1; /*  Positive Number By Default  */
    
    /*  Handle Negative Number  */
    if(*str == '-'){
        sign = -1;
        str++; /*   Move to the Next Char   */
    }
    
    /*  Iterate through the string and convert characters   */
    while(*str != '/0'){
        if(*str >= '0' && *str <= '9'){
            result = result * 10 + (*str - '0');
        }
        else{
            /* Invalid Char */
            break;
        }
        str++; /* Move to the Next Char */
    }
    
    return sign * result;
}