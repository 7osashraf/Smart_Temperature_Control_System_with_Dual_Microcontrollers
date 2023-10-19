/* 
 * File:   mcal_interrupt_manager.c
 * Author: ENG HOSAM
 *
 * Created on August 3, 2023, 9:50 PM
 */

#include "mcal_interrupt_manager.h"

static volatile uint8 RB4_Flag = 1, RB5_Flag = 1, RB6_Flag = 1, RB7_Flag = 1;

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
void __interrupt() InterruptManagerHigh(void){
    if((INNTERRUPT_ENALBE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF)){
        INT0_ISR();
    }
    else{  /*      Nothing     */}
    if((INNTERRUPT_ENALBE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF)){
        INT2_ISR();
    }
    else{  /*      Nothing     */}
}

void __interrupt(low_priority) InterruptManagerLow(void){
    if((INNTERRUPT_ENALBE == INTCON3bits.INT1E) && (INTERRUPT_OCCUR == INTCON3bits.INT1F)){
        INT1_ISR();
    }
    else{  /*      Nothing     */
}
}
#else 
void __interrupt() InterruptManagerHigh(void){
    if((INNTERRUPT_ENALBE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF)){
        INT0_ISR();
    }
    else{  /*      Nothing     */}
    if((INNTERRUPT_ENALBE == INTCON3bits.INT1E) && (INTERRUPT_OCCUR == INTCON3bits.INT1F)){
        INT1_ISR();
    }
    else{  /*      Nothing     */}
    if((INNTERRUPT_ENALBE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF)){
        INT2_ISR();
    }
    else{  /*      Nothing     */}
    
    if((INNTERRUPT_ENALBE == PIE1bits.ADIE) && (INTERRUPT_OCCUR == PIR1bits.ADIF)){
        ADC_ISR();
    }
    else{  /*      Nothing     */}
    
    if((INNTERRUPT_ENALBE == INTCONbits.TMR0IE) && (INTERRUPT_OCCUR == INTCONbits.TMR0IF)){
        TMR0_ISR();
    }
    else{  /*      Nothing     */}
    if((INNTERRUPT_ENALBE == PIE1bits.TMR1IE) && (INTERRUPT_OCCUR == PIR1bits.TMR1IF)){
        TMR1_ISR();
    }
    else{  /*      Nothing     */}
    if((INNTERRUPT_ENALBE == PIE1bits.TMR2IE) && (INTERRUPT_OCCUR == PIR1bits.TMR2IF)){
        TMR2_ISR();
    }
    else{  /*      Nothing     */}
    if((INNTERRUPT_ENALBE == PIE2bits.TMR3IE) && (INTERRUPT_OCCUR == PIR2bits.TMR3IF)){
        TMR3_ISR();
    }
    else{  /*      Nothing     */}
    
    /*  ==========  PortB External OnChange Interrupt Start =========   */
    if((INNTERRUPT_ENALBE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB4 == GPIO_HIGH) && (RB4_Flag == 0)){
        RB4_Flag = 0;
        RB4_ISR(0);
    }
    else{  /*      Nothing     */}
    if((INNTERRUPT_ENALBE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB4 == GPIO_LOW) && (RB4_Flag == 1)){
        RB4_Flag = 1;
        RB4_ISR(1);
    }
    else{  /*      Nothing     */}
    
    
    if((INNTERRUPT_ENALBE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB5 == GPIO_HIGH) && (RB5_Flag == 0)){
        RB5_Flag = 0;
        RB5_ISR(0);
    }
    else{  /*      Nothing     */}
    if((INNTERRUPT_ENALBE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB5 == GPIO_LOW) && (RB5_Flag == 1)){
        RB5_Flag = 1;
        RB5_ISR(1);
    }
    else{  /*      Nothing     */}
    
    
    if((INNTERRUPT_ENALBE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB6 == GPIO_HIGH) && (RB6_Flag == 0)){
        RB6_Flag = 0;
        RB6_ISR(0);
    }
    else{  /*      Nothing     */}
    if((INNTERRUPT_ENALBE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB6 == GPIO_LOW) && (RB6_Flag == 1)){
        RB6_Flag = 1;
        RB6_ISR(1);
    }
    else{  /*      Nothing     */}
    
    
    if((INNTERRUPT_ENALBE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB7 == GPIO_HIGH) && (RB7_Flag == 0)){
        RB7_Flag = 0;
        RB7_ISR(0);
    }
    else{  /*      Nothing     */}
    if((INNTERRUPT_ENALBE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB7 == GPIO_LOW) && (RB7_Flag == 1)){
        RB7_Flag = 1;
        RB7_ISR(1);
    }
    else{  /*      Nothing     */}
    
    
    
    /*  ==========  PortB External OnChange Interrupt End =========   */
    
    /*  ==========  CCP1 and CCP2 Modules Interrupt Start =========   */
    if((INNTERRUPT_ENALBE == PIE1bits.CCP1IE) && (INTERRUPT_OCCUR == PIR1bits.CCP1IF)){
        CCP1_ISR();
    }
    else{  /*      Nothing     */}
    if((INNTERRUPT_ENALBE == PIE2bits.CCP2IE) && (INTERRUPT_OCCUR == PIR2bits.CCP2IF)){
        CCP2_ISR();
    }
    else{  /*      Nothing     */}
    
    /*  ========== CCP1 and CCP2 Modules Interrupt  End =========   */
    
    /*  ==========  EUSART Modules Interrupt Start =========   */
    if((INNTERRUPT_ENALBE == PIE1bits.TXIE) && (INTERRUPT_OCCUR == PIR1bits.TXIF)){
        EUSART_TX_ISR();
    }
    else{  /*      Nothing     */}
    
    if((INNTERRUPT_ENALBE == PIE1bits.RCIE) && (INTERRUPT_OCCUR == PIR1bits.RCIF)){
        EUSART_RX_ISR();
    }
    else{  /*      Nothing     */}
    
    /*  ========== EUSART Modules Interrupt  End =========   */
    
    
    /*  ==========  EUSART Modules Interrupt Start =========   */
    if((INNTERRUPT_ENALBE == PIE1bits.SSPIE) && (INTERRUPT_OCCUR == PIR1bits.SSPIF)){
        MSSP_I2C_ISR();
    }
    else{  /*      Nothing     */}
    
    if((INNTERRUPT_ENALBE == PIE2bits.BCLIE) && (INTERRUPT_OCCUR == PIR2bits.BCLIF)){
        MSSP_I2C_BC_ISR();
    }
    else{  /*      Nothing     */}
    /*  ========== EUSART Modules Interrupt  End =========   */
}
#endif