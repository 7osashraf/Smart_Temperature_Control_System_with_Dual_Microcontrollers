/* 
 * File:   hal_eeprom.c
 * Author: ENG HOSAM
 *
 * Created on August 8, 2023, 1:49 PM
 */

#include "hal_eeprom.h"

/**
 * 
 * @param bAdd
 * @param bData
 * @return Status of the function 
 *         (E_OK)  :  The function done successfully
 *         (E_NOT_OK)  :  The function has issue to perform this action 
 */
Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData){
    Std_ReturnType ret = E_OK;
    /*  Read the Interrupt Status "Enabled or Disabled" */\
    uint8 Global_Interrupt_Status = INTCONbits.GIE;
    /*  Update the Address Registers */
    EEADRH = (uint8)((bAdd >> 8) & 0x03);
    EEADR = (uint8)(bAdd & 0xFF);                                                    
    /*  Update the Data Registers   */
    EEDATA = bData;
    /*  Select Access data EEPROM memory    */
    EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
    EECON1bits.CFGS = ACCESS_EEPROM_EEPROM_MEMORY;
    /*  Allows write cycles to Flash program/data EEPROM    */
    EECON1bits.WREN = ALLOW_WRITE_CYCLES_FLASH_EEPROM;
    /*  Disable all Interrupt "General Interrupt"   */
    INTERRUPT_GlobalInterruptDisable();
    /*  Write the required sequence : 0x55 -> 0xAA  */
    EECON2 = 0x55;
    EECON2 = 0xAA;
    /*  Initiates a data EEPROM erase/write cycle   */
    EECON1bits.WR = INITIATE_DATA_EEPROM_WRITE_ERASE;
    /*  Wait for write to complete  */
    while(EECON1bits.WR);
    /*  Inhibits write cyclesto Flash program/data EEPROM   */
    EECON1bits.WREN = INHIBTS_WRITE_CYCLES_FLASH_EEPROM;
    /*  Restore the Interrupt Status "Enabled or Disabled"  */
    INTCONbits.GIE = Global_Interrupt_Status;
    return ret;
}
/**
 * 
 * @param bAdd
 * @param bData
 * @return Status of the function 
 *         (E_OK)  :  The function done successfully
 *         (E_NOT_OK)  :  The function has issue to perform this action
 */
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == bData){
        ret = E_NOT_OK;
    }
    else{
        /*  Update the Address Registers    */
        EEADRH = (uint8)((bAdd >> 8) & 0x03);
        EEADR = (uint8)(bAdd & 0xFF);
        /*  Select Access Data EEPROM Memory    */
        EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
        EECON1bits.CFGS = ACCESS_EEPROM_EEPROM_MEMORY;
        /*  Initiates a data EEPROM read cycle  */
        EECON1bits.RD =  INITIATE_DATA_EEPROM_READ;
        NOP();
        NOP();
        /*  Return Data */
        *bData = EEDATA;
        ret = E_OK;
    }
    return ret;
}