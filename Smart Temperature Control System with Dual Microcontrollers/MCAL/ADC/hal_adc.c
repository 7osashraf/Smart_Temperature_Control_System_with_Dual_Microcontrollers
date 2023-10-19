/* 
 * File:   hal_adc.c
 * Author: ENG HOSAM
 *
 * Created on August 12, 2023, 3:29 PM
 */

#include "hal_adc.h"

#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*ADC_InterruptHandler)(void) = NULL;    
#endif


static inline void adc_input_channel_port_configure(adc_channel_select_t channel);
static inline void select_result_format(const adc_conf_t *_adc);
static inline void configure_voltage_reference(const adc_conf_t *_adc);

/**
 * @Summary Initialize the ADC
 * @Description This routine initialize the ADC.
 *              This routine must be called before any other ADC routine is called.
 *              This routine should only be called once during system initialization.
 * @param _adc  Pointer to the ADC configurations
 * @return Status of the function 
 *         (E_OK)  :  The function done successfully
 *         (E_NOT_OK)  :  The function has issue to perform this action
 */
Std_ReturnType  ADC_Init(const adc_conf_t *_adc){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }
    else{
        /*  Disable  the ADC    */
        ADC_CONVERSION_DISABLE();
        /*  Configure the acquisition time  */
        ADCON2bits.ACQT = _adc->acquisition_time;
        /*  Configure the conversion clock  */
        ADCON2bits.ADCS = _adc->conversion_clock;
        /*  Configure the default channel   */
        ADCON0bits.CHS = _adc->adc_channel;
        adc_input_channel_port_configure(_adc->adc_channel);
        /*  Configure the interrupt */
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        
        ADC_InterruptEnable();
        ADC_InterruptFlagClear();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        if(INTERRUPT_HIGH_PRIORITY == _adc->priority){
            ADC_HighPriorityySet();
        }
        else if(INTERRUPT_LOW_PRIORITY == _adc->priority){
            ADC_LowPriorityySet();
        }
        else{
            /*      Nothing     */
        }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable(); 
#endif
        ADC_InterruptHandler = _adc->ADC_InterruptHandler;

#endif
        /*  Configure the result format */
        select_result_format(_adc);
        /*  Configure the voltage reference */
        configure_voltage_reference(_adc);
        /*  Enable the ADC  */
        ADC_CONVERSION_ENABLE();
        ret = E_OK;
    }
    return ret;
}

/**
 * @Summary De-Initializes the ADC
 * @param _adc pointer to the ADC configurations
 * @return Status of the function 
 *         (E_OK)  :  The function done successfully
 *         (E_NOT_OK)  :  The function has issue to perform this action
 */
Std_ReturnType  ADC_DeInit(const adc_conf_t *_adc){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }
    else{
        /*  Disable  the ADC    */
        ADC_CONVERSION_DISABLE();
        /*  Disable the interrupt */
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        ADC_InterruptDisable();
#endif
        ret = E_OK;
    }
    return ret;
}

/**
 * @summary Allows selection of a channel for conversion
 * @Description This routine is used to select desired channel for conversion
 * @param _adc pointer to the ADC configurations
 * @param channel
 * @return Status of the function 
 *         (E_OK)  :  The function done successfully
 *         (E_NOT_OK)  :  The function has issue to perform this action
 */
Std_ReturnType  ADC_SelectChannel(const adc_conf_t *_adc, adc_channel_select_t channel){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }
    else{
        /*  Configure the default channel   */
        ADCON0bits.CHS = channel;
        adc_input_channel_port_configure(channel);
        ret = E_OK;
    }
    return ret;
}

/**
 * @Summary Starts conversion
 * @Description This routine is used to start conversion of desired channel.
 * @param _adc pointer to the ADC configurations
 * @return Status of the function 
 *         (E_OK)  :  The function done successfully
 *         (E_NOT_OK)  :  The function has issue to perform this action
 */
Std_ReturnType  ADC_StartConversion(const adc_conf_t *_adc){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }
    else{
        ADC_START_CONVERSION();
        ret = E_OK;
    }
    return ret;
}

/**
 * @Summary Returns true when the conversion is completed otherwise false.
 * @Description This routine is used to determine if conversion is completed.
 *              When conversion is complete routine returns true. It returns false otherwise.
 * @param _adc pointer to the ADC configurations
 * @param conversion_status The conversion status
 *          True  - If conversion is complete
 *          False - If conversion is not completed
 * @return Status of the function 
 *         (E_OK)  :  The function done successfully
 *         (E_NOT_OK)  :  The function has issue to perform this action
 */
Std_ReturnType  ADC_IsConversionDone(const adc_conf_t *_adc, uint8 *conversion_status){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc || NULL == conversion_status){
        ret = E_NOT_OK;
    }
    else{
        *conversion_status = (uint8)(!(ADCON0bits.GO_nDONE));
        ret = E_OK;
    }
    return ret;
}

/**
 * 
 * @param _adc pointer to the ADC configurations
 * @param conversion_result
 * @return Status of the function 
 *         (E_OK)  :  The function done successfully
 *         (E_NOT_OK)  :  The function has issue to perform this action
 */
Std_ReturnType  ADC_GetConversionResult(const adc_conf_t *_adc, adc_result_t *conversion_result){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc || NULL == conversion_result){
        ret = E_NOT_OK;
    }
    else{
        if(ADC_RESULT_RIGHT == _adc->result_format){
            *conversion_result = (adc_result_t)((ADRESH << 8 ) + ADRESL);
        }
        else if(ADC_RESULT_LEFT == _adc->result_format){
            *conversion_result = (adc_result_t)(((ADRESH << 8 ) + ADRESL) >> 6);
        }
        else{
            *conversion_result = (adc_result_t)((ADRESH << 8 ) + ADRESL);
        }
            ret = E_OK;
        }
    return ret;
}

/**
 * @Description This routine is used to select desired channel for conversion.
 *              This routine is get the analog to digital converted value.
 * @param _adc pointer to the ADC configurations
 * @param channel Defines the channel available for conversion.
 * @param conversion_result The converted value.
 * @return Status of the function 
 *         (E_OK)  :  The function done successfully
 *         (E_NOT_OK)  :  The function has issue to perform this action
 */
Std_ReturnType  ADC_GetConversion_Blocking(const adc_conf_t *_adc, adc_channel_select_t channel
                                  ,adc_result_t *conversion_result){
    Std_ReturnType ret = E_NOT_OK;
    uint8 l_conversion_status = 0;
    if((NULL == _adc) || (NULL == conversion_result)){
        ret = E_NOT_OK;
    }
    else{
        /*  Select the A/D Channel  */
        ret = ADC_SelectChannel(_adc, channel);
        /*  Start the Conversion    */
        ret = ADC_StartConversion(_adc);
        /*  Check if conversion is completed    */
        while(ADCON0bits.GO_nDONE);
        ret = ADC_GetConversionResult(_adc, conversion_result);
        
    }
    return ret;
}


/**
 * 
 * @param _adc pointer to the ADC configurations
 * @param channel Defines the channel available for conversion.
 * @return Status of the function 
 *         (E_OK)  :  The function done successfully
 *         (E_NOT_OK)  :  The function has issue to perform this action
 */
Std_ReturnType  ADC_StartConversion_Interrupt(const adc_conf_t *_adc, adc_channel_select_t channel){
    Std_ReturnType ret = E_NOT_OK;
    uint8 l_conversion_status = 0;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }
    else{
        /*  Select the A/D Channel  */
        ret = ADC_SelectChannel(_adc, channel);
        /*  Start the Conversion    */
        ret = ADC_StartConversion(_adc);
        
    }
    return ret;
}


static inline void adc_input_channel_port_configure(adc_channel_select_t channel){
    switch(channel){
        case ADC_CHANNEL_AN0 : SET_BIT(TRISA, _TRISA_RA0_POSN); break; /* Disable the digital o/p driver */
        case ADC_CHANNEL_AN1 : SET_BIT(TRISA, _TRISA_RA1_POSN); break; /* Disable the digital o/p driver */
        case ADC_CHANNEL_AN2 : SET_BIT(TRISA, _TRISA_RA2_POSN); break; /* Disable the digital o/p driver */
        case ADC_CHANNEL_AN3 : SET_BIT(TRISA, _TRISA_RA3_POSN); break; /* Disable the digital o/p driver */
        case ADC_CHANNEL_AN4 : SET_BIT(TRISA, _TRISA_RA4_POSN); break; /* Disable the digital o/p driver */
        case ADC_CHANNEL_AN5 : SET_BIT(TRISE, _TRISE_RE0_POSN); break; /* Disable the digital o/p driver */
        case ADC_CHANNEL_AN6 : SET_BIT(TRISE, _TRISE_RE1_POSN); break; /* Disable the digital o/p driver */
        case ADC_CHANNEL_AN7 : SET_BIT(TRISE, _TRISE_RE2_POSN); break; /* Disable the digital o/p driver */
        case ADC_CHANNEL_AN8 : SET_BIT(TRISB, _TRISB_RB2_POSN); break; /* Disable the digital o/p driver */
        case ADC_CHANNEL_AN9 : SET_BIT(TRISB, _TRISB_RB3_POSN); break; /* Disable the digital o/p driver */
        case ADC_CHANNEL_AN10 : SET_BIT(TRISB, _TRISB_RB1_POSN); break; /* Disable the digital o/p driver */
        case ADC_CHANNEL_AN11 : SET_BIT(TRISB, _TRISB_RB4_POSN); break; /* Disable the digital o/p driver */
        case ADC_CHANNEL_AN12 : SET_BIT(TRISB, _TRISB_RB0_POSN); break; /* Disable the digital o/p driver */
        
    }
}

static inline void select_result_format(const adc_conf_t *_adc){
    if(ADC_RESULT_RIGHT == _adc->result_format){
        ADC_RESULT_RIGHT_FORMAT();
    }
    else if(ADC_RESULT_LEFT == _adc->result_format){
        ADC_RESULT_LEGT_FORMAT();
    }
    else{
        ADC_RESULT_RIGHT_FORMAT();
    }
}

static inline void configure_voltage_reference(const adc_conf_t *_adc){
    if(ADC_VOLTAGE_REFERENCE_ENABLED == _adc->voltage_reference){
        ADC_ENABLE_VOLTAGE_REFERENCE();
    }
    else if(ADC_VOLTAGE_REFERENCE_DISABLED == _adc->voltage_reference){
        ADC_DISABLE_VOLTAGE_REFERENCE();
    }
    else{
        ADC_DISABLE_VOLTAGE_REFERENCE();
    }
}

void ADC_ISR(void){
    ADC_InterruptFlagClear();
    if(ADC_InterruptHandler){
        ADC_InterruptHandler();
        
    }
}