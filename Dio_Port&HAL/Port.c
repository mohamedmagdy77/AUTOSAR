/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Mohamed Magdy
 ******************************************************************************/

#include "Port.h"
#include "Port_Regs.h"


#if (PORT_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
    #error "the AR Version of Port module and Det module are not compatible"
#endif
#endif

/*
 * Port module initialization state
*/
STATIC uint8 Port_state = PORT_NOT_INITIALIZED;

/*******************************************************************************
* Service Name: Port_Init
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Setup the configuration of the 43 pins in Tiva c:
*              - Setup the pin as Digital or Analog pin
*              - Setup the direction of the GPIO pin
*              - Provide initial value for o/p pin
*              - Setup the internal resistor for i/p pin
*              - Setup the mode of the pin CAN, PWM....
********************************************************************************/
void Port_Init( const Port_ConfigType* ConfigPtr ){

    uint8 counter;                      /* for loop countre to loop on all pins*/
    GPIO_TypeDef *GPIO_ptr = NULL_PTR;  /* pinter to the base of PORT*/
    
#if (PORT_DEV_ERROR_DETECT == STD_ON)   
    /* check if the input configuration pointer is not a NULL_PTR */
	if (NULL_PTR == ConfigPtr)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
		     PORT_E_PARAM_CONFIG);
	}
	else
#endif
	{
        Port_state = PORT_INITIALIZED;
        
        /* enable clock for all GPIOs*/
        RCGCGPIO = 0X1F;
        
        
        
        /**
         * NO unlock and commit for JTAG pins PC0 -> PC3
         */
        
        /* configure all the pins of the microcontroller*/
        for(counter = 0; counter < MICROCONTROLLER_PINS_NUM; counter++){
            switch(ConfigPtr->Ports[counter].port_num)
            {
                case 0: GPIO_ptr = GPIOA; /* PORTA Base Address */
                        break;
                case 1: GPIO_ptr = GPIOB; /* PORTB Base Address */
                        break;
                case 2: GPIO_ptr = GPIOC; /* PORTC Base Address */
                        break;
                case 3: GPIO_ptr = GPIOD; /* PORTD Base Address */
                        break;
                case 4: GPIO_ptr = GPIOE; /* PORTE Base Address */
                        break;
                case 5: GPIO_ptr = GPIOF; /* PORTF Base Address */
                        break;
            }
            /* write mode to PCTL register*/
            if(ConfigPtr->Ports[counter].mode == ADC){
                /* clear PCTL field*/
                //GPIO_ptr->PCTL = ( GPIO_ptr->PCTL & ~(0X0F<<(ConfigPtr->Ports[counter].pin_num*4)) );
            }
            else{
                /* write mode tp PCTL field*/
                /*GPIO_ptr->PCTL = ( GPIO_ptr->PCTL & ~(0X0F<<(ConfigPtr->Ports[counter].pin_num*4)) )\
                               | ( ConfigPtr->Ports[counter].mode );*/
            }
            
            /* if the pin is a GPIO pin*/
            if(ConfigPtr->Ports[counter].mode == GPIO){
                /* disable alternate function*/
                CLEAR_BIT(GPIO_ptr->AFSEL, ConfigPtr->Ports[counter].pin_num);
                
                /* choose direction*/
                if(ConfigPtr->Ports[counter].direction == INPUT){
                    /* input*/
                    CLEAR_BIT(GPIO_ptr->DIR, ConfigPtr->Ports[counter].pin_num);
                }
                else{
                    /* output*/
                    SET_BIT(GPIO_ptr->DIR, ConfigPtr->Ports[counter].pin_num);
                }
                
                /* internal resistor*/
                if(ConfigPtr->Ports[counter].resistor == PULL_UP){
                    /* pull up resistor*/
                    SET_BIT(GPIO_ptr->PUR, ConfigPtr->Ports[counter].pin_num);
                }
                else if(ConfigPtr->Ports[counter].resistor == PULL_DOWN){
                    /* pull down resistor*/
                    SET_BIT(GPIO_ptr->PDR, ConfigPtr->Ports[counter].pin_num);
                }
                else{
                    /* OFF*/
                    CLEAR_BIT(GPIO_ptr->PUR, ConfigPtr->Ports[counter].pin_num);
                    CLEAR_BIT(GPIO_ptr->PDR, ConfigPtr->Ports[counter].pin_num);
                }
                
                /* initial value*/
                if(ConfigPtr->Ports[counter].initial_value == STD_HIGH){
                    /* logic high*/
                    SET_BIT(GPIO_ptr->DATA, ConfigPtr->Ports[counter].pin_num);
                }
                else{
                    /* logic low*/
                    CLEAR_BIT(GPIO_ptr->DATA, ConfigPtr->Ports[counter].pin_num);
                }
            }
            /* pin is not GPIO*/
            else{
                /* enable alternate function*/
                SET_BIT(GPIO_ptr->AFSEL, ConfigPtr->Ports[counter].pin_num);
            }
            
            /* digital enable or disable*/
            if(ConfigPtr->Ports[counter].mode == ADC){
                /* digital disable*/
                CLEAR_BIT(GPIO_ptr->DEN, ConfigPtr->Ports[counter].pin_num);
            }
            else{
                /* digital enable*/
                SET_BIT(GPIO_ptr->DEN, ConfigPtr->Ports[counter].pin_num);
            }
        }
    }
}

/*******************************************************************************
* Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): pin - pin number
                   Direction - INPUT or OUTPUT
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Set the port pin direction
********************************************************************************/
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction ){
    uint8 error = FALSE;
    GPIO_TypeDef *GPIO_ptr = NULL_PTR;  /* pinter to the base of PORT*/
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    
    /* passing wrong pin number*/
    if(Pin >= MICROCONTROLLER_PINS_NUM){
        error = TRUE;
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SETPINDIRECTION_SID,
                        PORT_E_PARAM_PIN);
    }
    else{
    
    }
    
    /* chaning an unchangeable pin direction*/
    if(pins_config_structure.Ports[Pin].direction_state == DIR_UNCHANGEABLE){
        error = TRUE;
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SETPINDIRECTION_SID,
                        PORT_E_DIRECTION_UNCHANGEABLE);
    }
    else{
    
    }
    
    /* Port_Init is not called yet*/
    if(Port_state == PORT_NOT_INITIALIZED){
        error = TRUE;
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SETPINDIRECTION_SID,
                        PORT_E_UNINIT);
    }
    else{
    
    }
#endif
    if(error == FALSE){
        switch(pins_config_structure.Ports[Pin].port_num)
        {
            case 0: GPIO_ptr = GPIOA; /* PORTA Base Address */
                    break;
            case 1: GPIO_ptr = GPIOB; /* PORTB Base Address */
                    break;
            case 2: GPIO_ptr = GPIOC; /* PORTC Base Address */
                    break;
            case 3: GPIO_ptr = GPIOD; /* PORTD Base Address */
                    break;
            case 4: GPIO_ptr = GPIOE; /* PORTE Base Address */
                    break;
            case 5: GPIO_ptr = GPIOF; /* PORTF Base Address */
                    break;
        }
        if(Direction == INPUT){
            CLEAR_BIT(GPIO_ptr->DIR, pins_config_structure.Ports[Pin].pin_num);
        }
        else{
            SET_BIT(GPIO_ptr->DIR, pins_config_structure.Ports[Pin].pin_num);
        }
    }
}
#endif

/*******************************************************************************
* Service Name: Port_SetPinMode
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): pin - pin number
                   Mode - GPIO, ADC, CAN....
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Set the port pin mode
********************************************************************************/
#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode ){
    uint8 error = FALSE;
    GPIO_TypeDef *GPIO_ptr = NULL_PTR;  /* pinter to the base of PORT*/
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    
    /* passing wrong pin number*/
    if(Pin >= MICROCONTROLLER_PINS_NUM){
        error = TRUE;
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SETMODE_SID,
                        PORT_E_PARAM_PIN);
    }
    else{
    
    }
    
    /* chaning an unchangeable pin mode*/
    if(pins_config_structure.Ports[Pin].mode_state == MODE_UNCHANGEABLE){
        error = TRUE;
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SETMODE_SID,
                        PORT_E_MODE_UNCHANGEABLE);
    }
    else{
    
    }
    
    /* passing invalid mode*/
    if(Mode > 15 || (Mode > 9 && Mode < 14)){
        error = TRUE;
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SETMODE_SID,
                        PORT_E_PARAM_INVALID_MODE);
    }
    else{
    
    }
    
    /* Port_Init is not clled yet*/
    if(Port_state == PORT_NOT_INITIALIZED){
        error = TRUE;
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SETMODE_SID,
                        PORT_E_UNINIT);
    }
    else{
    
    }
#endif
    if(error == FALSE){
        switch(pins_config_structure.Ports[Pin].port_num)
        {
            case 0: GPIO_ptr = GPIOA; /* PORTA Base Address */
                    break;
            case 1: GPIO_ptr = GPIOB; /* PORTB Base Address */
                    break;
            case 2: GPIO_ptr = GPIOC; /* PORTC Base Address */
                    break;
            case 3: GPIO_ptr = GPIOD; /* PORTD Base Address */
                    break;
            case 4: GPIO_ptr = GPIOE; /* PORTE Base Address */
                    break;
            case 5: GPIO_ptr = GPIOF; /* PORTF Base Address */
                    break;
        }
        if(Mode == ADC){
            GPIO_ptr->PCTL = ( GPIO_ptr->PCTL & ~(0X0F<<(pins_config_structure.Ports[Pin].pin_num*4)) );
            }
        else{
            GPIO_ptr->PCTL = ( GPIO_ptr->PCTL & ~(0X0F<<(pins_config_structure.Ports[Pin].pin_num*4)) )\
                           | ( pins_config_structure.Ports[Pin].mode );
        }
    }
}
#endif

/*******************************************************************************
* Service Name: Port_RefreshPortDirection
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to refresh all unchangeable direction pins of Port module
********************************************************************************/
void Port_RefreshPortDirection( void ){
    uint8 counter;
    GPIO_TypeDef *GPIO_ptr = NULL_PTR;  /* pinter to the base of PORT*/
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Port_Init is not clled yet*/
    if(Port_state == PORT_NOT_INITIALIZED){
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESHPORTDIRECTION_SID,
                        PORT_E_UNINIT);
    }
    else
#endif
    {
        for(counter = 0; counter < MICROCONTROLLER_PINS_NUM; counter++){
            /* refresh unchangeable direction pins*/
            if(pins_config_structure.Ports[counter].direction_state == DIR_UNCHANGEABLE){
                switch(pins_config_structure.Ports[counter].port_num)
                {
                    case 0: GPIO_ptr = GPIOA; /* PORTA Base Address */
                            break;
                    case 1: GPIO_ptr = GPIOB; /* PORTB Base Address */
                            break;
                    case 2: GPIO_ptr = GPIOC; /* PORTC Base Address */
                            break;
                    case 3: GPIO_ptr = GPIOD; /* PORTD Base Address */
                            break;
                    case 4: GPIO_ptr = GPIOE; /* PORTE Base Address */
                            break;
                    case 5: GPIO_ptr = GPIOF; /* PORTF Base Address */
                            break;
                }
            
                if(pins_config_structure.Ports[counter].direction == INPUT){
                    CLEAR_BIT(GPIO_ptr->DIR, pins_config_structure.Ports[counter].pin_num);
                }
                else{
                    SET_BIT(GPIO_ptr->DIR, pins_config_structure.Ports[counter].pin_num);
                }
            }
            else{
            
            }
        }
    }  
}

/*******************************************************************************
* Service Name: Port_GetVersionInfo
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): versioninfo - pin number
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to get version of Port module
********************************************************************************/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo ){
    #if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if input pointer is not Null pointer */
	if(NULL_PTR == versioninfo)
	{
		/* Report to DET  */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
	}
	else
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
	{
		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = (uint16)PORT_MODULE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
	}
}
#endif