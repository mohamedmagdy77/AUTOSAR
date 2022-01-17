 /******************************************************************************
 *
 * Module: Dio
 *
 * File Name: Dio.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Dio Driver
 *
 * Author: Mohamed Magdy
 ******************************************************************************/

#include "Dio.h"
#include "Dio_Regs.h"

#if (DIO_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Dio Modules */
#if ((DET_AR_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != DIO_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != DIO_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif

STATIC const Dio_PortType * Dio_Ports = NULL_PTR;
STATIC const Dio_ConfigChannel * Dio_PortChannels = NULL_PTR;
//STATIC const Dio_ChannelGroupType * Dio_Groups = NULL_PTR;
volatile STATIC uint8 Dio_Status = DIO_NOT_INITIALIZED;

/************************************************************************************
* Service Name: Dio_Init
* Service ID[hex]: 0x10
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Dio module.
************************************************************************************/
void Dio_Init(const Dio_ConfigType * ConfigPtr)
{
#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* check if the input configuration pointer is not a NULL_PTR */
	if (NULL_PTR == ConfigPtr)
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID, DIO_INIT_SID,
		     DIO_E_PARAM_CONFIG);
	}
	else
#endif
	{
		/*
		 * Set the module state to initialized and point to the PB configuration structure using a global pointer.
		 * This global pointer is global to be used by other functions to read the PB configuration structures
		 */
		Dio_Status       = DIO_INITIALIZED;
        Dio_Ports        = ConfigPtr->Ports;    /* address of the first Port structure --> Ports[0] */
		Dio_PortChannels = ConfigPtr->Channels; /* address of the first Channel structure --> Channels[0] */
	}
}

/************************************************************************************
* Service Name: Dio_WriteChannel
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - ID of DIO channel.
*                  Level - Value to be written.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set a level of a channel.
************************************************************************************/
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
	volatile uint32 * Port_Ptr = NULL_PTR;
	boolean error = FALSE;

#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (DIO_NOT_INITIALIZED == Dio_Status)
	{
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
				DIO_WRITE_CHANNEL_SID, DIO_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
	/* Check if the used channel is within the valid range */
	if (DIO_CONFIGURED_CHANNLES <= ChannelId)
	{

		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
				DIO_WRITE_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
#endif

	/* In-case there are no errors */
	if(FALSE == error)
	{
		/* Point to the correct PORT register according to the Port Id stored in the Port_Num member */
		switch(Dio_PortChannels[ChannelId].Port_Num)
		{
            case 0:    Port_Ptr = &GPIO_PORTA_DATA_REG;
		               break;
		    case 1:    Port_Ptr = &GPIO_PORTB_DATA_REG;
		               break;
		    case 2:    Port_Ptr = &GPIO_PORTC_DATA_REG;
		               break;
		    case 3:    Port_Ptr = &GPIO_PORTD_DATA_REG;
		               break;
            case 4:    Port_Ptr = &GPIO_PORTE_DATA_REG;
		               break;
            case 5:    Port_Ptr = &GPIO_PORTF_DATA_REG;
		               break;
		}
		if(Level == STD_HIGH)
		{
			/* Write Logic High */
			SET_BIT(*Port_Ptr,Dio_PortChannels[ChannelId].Ch_Num);
		}
		else if(Level == STD_LOW)
		{
			/* Write Logic Low */
			CLEAR_BIT(*Port_Ptr,Dio_PortChannels[ChannelId].Ch_Num);
		}
	}
	else
	{
		/* No Action Required */
	}

}

/************************************************************************************
* Service Name: Dio_ReadChannel
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - ID of DIO channel.
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_LevelType
* Description: Function to return the value of the specified DIO channel.
************************************************************************************/
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
    volatile uint32 *port_ptr = NULL_PTR;
    boolean error = FALSE;
    Dio_LevelType ret_val;
#if (DIO_DEV_ERROR_DETECT == STD_ON)
    if(ChannelId >= DIO_CONFIGURED_CHANNLES){
        Det_ReportError(DIO_MODULE_ID,
                        DIO_INSTANCE_ID,
                        DIO_READ_CHANNEL_SID,
                        DIO_E_PARAM_INVALID_CHANNEL_ID);
        error = TRUE;
    }
    else{
        /* empty*/
    }
    if(Dio_Status == DIO_NOT_INITIALIZED){
        Det_ReportError(DIO_MODULE_ID,
                        DIO_INSTANCE_ID,
                        DIO_READ_CHANNEL_SID,
                        DIO_E_UNINIT);
        error = TRUE;
    }
    else{
        /* empty*/
    }
#endif
    
    if(error == FALSE){
        switch(Dio_PortChannels[ChannelId].Port_Num){
            case 0: port_ptr = &GPIO_PORTA_DATA_REG;
                    break;
            case 1: port_ptr = &GPIO_PORTB_DATA_REG;
                    break;
            case 2: port_ptr = &GPIO_PORTC_DATA_REG;
                    break;
            case 3: port_ptr = &GPIO_PORTD_DATA_REG;
                    break;
            case 4: port_ptr = &GPIO_PORTE_DATA_REG;
                    break;
            case 5: port_ptr = &GPIO_PORTF_DATA_REG;
                    break;
        }
        
        if((*port_ptr&(1<<Dio_PortChannels[ChannelId].Ch_Num)) != 0){
            ret_val = STD_HIGH;
        }
        else{
            ret_val = STD_LOW;
        }
    }
    
    return ret_val;
}

/************************************************************************************
* Service Name: Dio_GetVersionInfo
* Service ID[hex]: 0x12
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): VersionInfo - Pointer to where to store the version information of this module.
* Return value: None
* Description: Function to get the version information of this module.
************************************************************************************/
#if (DIO_VERSION_INFO_API == STD_ON)
void Dio_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if input pointer is not Null pointer */
	if(NULL_PTR == versioninfo)
	{
		/* Report to DET  */
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
				DIO_GET_VERSION_INFO_SID, DIO_E_PARAM_POINTER);
	}
	else
#endif /* (DIO_DEV_ERROR_DETECT == STD_ON) */
	{
		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16)DIO_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = (uint16)DIO_MODULE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)DIO_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)DIO_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)DIO_SW_PATCH_VERSION;
	}
}
#endif

/************************************************************************************
* Service Name: Dio_FlipChannel
* Service ID[hex]: 0x11
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelId - ID of DIO channel.
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_LevelType
* Description: Function to flip the level of a channel and return the level of the channel after flip.
************************************************************************************/
#if (DIO_FLIP_CHANNEL_API == STD_ON)
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{
    volatile uint32 *port_ptr = NULL_PTR;
    boolean error = FALSE;
    Dio_LevelType ret_val;
#if (DIO_DEV_ERROR_DETECT == STD_ON)
    if(ChannelId >= DIO_CONFIGURED_CHANNLES){
        Det_ReportError(DIO_MODULE_ID,
                        DIO_INSTANCE_ID,
                        DIO_FLIP_CHANNEL_SID,
                        DIO_E_PARAM_INVALID_CHANNEL_ID);
        error = TRUE;
    }
    else{
        /* empty*/
    }
    if(Dio_Status == DIO_NOT_INITIALIZED){
        Det_ReportError(DIO_MODULE_ID,
                        DIO_INSTANCE_ID,
                        DIO_FLIP_CHANNEL_SID,
                        DIO_E_UNINIT);
        error = TRUE;
    }
    else{
        /* empty*/
    }
#endif
    
    if(error == FALSE){
        switch(Dio_PortChannels[ChannelId].Port_Num){
            case 0: port_ptr = &GPIO_PORTA_DATA_REG;
                    break;
            case 1: port_ptr = &GPIO_PORTB_DATA_REG;
                    break;
            case 2: port_ptr = &GPIO_PORTC_DATA_REG;
                    break;
            case 3: port_ptr = &GPIO_PORTD_DATA_REG;
                    break;
            case 4: port_ptr = &GPIO_PORTE_DATA_REG;
                    break;
            case 5: port_ptr = &GPIO_PORTF_DATA_REG;
                    break;
        }
        TOGGLE_BIT(*port_ptr, Dio_PortChannels[ChannelId].Ch_Num);
        
        if((*port_ptr&(1<<Dio_PortChannels[ChannelId].Ch_Num)) != 0){
            ret_val = STD_HIGH;
        }
        else{
            ret_val = STD_LOW;
        }
    }
    return ret_val;
}

/************************************************************************************
* Service Name: Dio_ReadPort
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): PortId - ID of DIO Port.
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_PortLevelType
* Description: Returns the level of all channels of that port.
************************************************************************************/
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)
{
    volatile uint32 *port_ptr = NULL_PTR;
    uint8 error = FALSE;
#if (DIO_DEV_ERROR_DETECT == STD_ON)
    if(PortId >= DIO_CONFIGURED_PORTS){
        error = TRUE;
        Det_ReportError( DIO_MODULE_ID,
                         DIO_INSTANCE_ID,
                         DIO_READ_PORT_SID,
                         DIO_E_PARAM_INVALID_PORT_ID );
    }
    else{
        
    }
    if(Dio_Status == DIO_NOT_INITIALIZED){
        error = TRUE;
        Det_ReportError( DIO_MODULE_ID,
                         DIO_INSTANCE_ID,
                         DIO_READ_PORT_SID,
                         DIO_E_UNINIT );
    }
    else{
        
    }
#endif
    
    if(error == FALSE){
        switch(Dio_Ports[PortId]){
            case 0: port_ptr = &GPIO_PORTA_DATA_REG;
                    break;
            case 1: port_ptr = &GPIO_PORTB_DATA_REG;
                    break;
            case 2: port_ptr = &GPIO_PORTC_DATA_REG;
                    break;
            case 3: port_ptr = &GPIO_PORTD_DATA_REG;
                    break;
            case 4: port_ptr = &GPIO_PORTE_DATA_REG;
                    break;
            case 5: port_ptr = &GPIO_PORTF_DATA_REG;
                    break;
        }
    }
    return (Dio_PortLevelType)(*port_ptr);
}

/************************************************************************************
* Service Name: Dio_WritePort
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): PortId - ID of DIO Port.
                   Level - value to be written.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Service to set a value of the port.
************************************************************************************/
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level){
    volatile uint32 *port_ptr = NULL_PTR;
    uint8 error = FALSE;
#if (DIO_DEV_ERROR_DETECT == STD_ON)
    if(PortId >= DIO_CONFIGURED_PORTS){
        error = TRUE;
        Det_ReportError( DIO_MODULE_ID,
                         DIO_INSTANCE_ID,
                         DIO_WRITE_PORT_SID,
                         DIO_E_PARAM_INVALID_PORT_ID );
    }
    else{
        
    }
    if(Dio_Status == DIO_NOT_INITIALIZED){
        error = TRUE;
        Det_ReportError( DIO_MODULE_ID,
                         DIO_INSTANCE_ID,
                         DIO_WRITE_PORT_SID,
                         DIO_E_UNINIT );
    }
    else{
        
    }
#endif
    
    if(error == FALSE){
        switch(Dio_Ports[PortId]){
            case 0: port_ptr = &GPIO_PORTA_DATA_REG;
                    break;
            case 1: port_ptr = &GPIO_PORTB_DATA_REG;
                    break;
            case 2: port_ptr = &GPIO_PORTC_DATA_REG;
                    break;
            case 3: port_ptr = &GPIO_PORTD_DATA_REG;
                    break;
            case 4: port_ptr = &GPIO_PORTE_DATA_REG;
                    break;
            case 5: port_ptr = &GPIO_PORTF_DATA_REG;
                    break;
        }
    }
    *port_ptr = Level;
}

/************************************************************************************
* Service Name: Dio_ReadChannelGroup
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelGroupIdPtr - Pointer to ChannelGroup.
* Parameters (inout): None
* Parameters (out): None
* Return value: Dio_PortLevelType - Level of a subset of the adjoining bits of a port.
* Description: This Service reads a subset of the adjoining bits of a port.
************************************************************************************/
Dio_PortLevelType Dio_ReadChannelGroup ( const Dio_ChannelGroupType* ChannelGroupIdPtr ){
    volatile uint32 *port_ptr = NULL_PTR;
    uint8 error = FALSE;
#if (DIO_DEV_ERROR_DETECT == STD_ON)
    if(Dio_Status == DIO_NOT_INITIALIZED){
        error = TRUE;
        Det_ReportError( DIO_MODULE_ID,
                         DIO_INSTANCE_ID,
                         DIO_READ_CHANNEL_GROUP_SID,
                         DIO_E_UNINIT );
    }
    else{
        
    }
    
    if(ChannelGroupIdPtr == NULL_PTR){
        error = TRUE;
        Det_ReportError(DIO_MODULE_ID,
                         DIO_INSTANCE_ID,
                         DIO_READ_CHANNEL_GROUP_SID,
                         DIO_E_PARAM_POINTER);
    }
    else{
    
    }
#endif
    
    if(error == FALSE){
        switch(ChannelGroupIdPtr->PortIndex){
            case 0: port_ptr = &GPIO_PORTA_DATA_REG;
                    break;
            case 1: port_ptr = &GPIO_PORTB_DATA_REG;
                    break;
            case 2: port_ptr = &GPIO_PORTC_DATA_REG;
                    break;
            case 3: port_ptr = &GPIO_PORTD_DATA_REG;
                    break;
            case 4: port_ptr = &GPIO_PORTE_DATA_REG;
                    break;
            case 5: port_ptr = &GPIO_PORTF_DATA_REG;
                    break;
        }
    }
    return ( ((Dio_PortLevelType)(*port_ptr)&(ChannelGroupIdPtr->mask))>>ChannelGroupIdPtr->offset);
}

/************************************************************************************
* Service Name: Dio_WriteChannelGroup
* Service ID[hex]: 0x05
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ChannelGroupIdPtr - Pointer to ChannelGroup.
                   Level - Value to be written
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Service to set a subset of the adjoining bits of a port to a specified level.
************************************************************************************/
void Dio_WriteChannelGroup ( const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level ){
    volatile uint32 *port_ptr = NULL_PTR;
    uint8 error = FALSE;
#if (DIO_DEV_ERROR_DETECT == STD_ON)
    if(Dio_Status == DIO_NOT_INITIALIZED){
        error = TRUE;
        Det_ReportError( DIO_MODULE_ID,
                         DIO_INSTANCE_ID,
                         DIO_WRITE_CHANNEL_GROUP_SID,
                         DIO_E_UNINIT );
    }
    else{
        
    }
    
    if(ChannelGroupIdPtr == NULL_PTR){
        error = TRUE;
        Det_ReportError(DIO_MODULE_ID,
                         DIO_INSTANCE_ID,
                         DIO_WRITE_CHANNEL_GROUP_SID,
                         DIO_E_PARAM_POINTER);
    }
    else{
    
    }
#endif
    
    if(error == FALSE){
        switch(ChannelGroupIdPtr->PortIndex){
            case 0: port_ptr = &GPIO_PORTA_DATA_REG;
                    break;
            case 1: port_ptr = &GPIO_PORTB_DATA_REG;
                    break;
            case 2: port_ptr = &GPIO_PORTC_DATA_REG;
                    break;
            case 3: port_ptr = &GPIO_PORTD_DATA_REG;
                    break;
            case 4: port_ptr = &GPIO_PORTE_DATA_REG;
                    break;
            case 5: port_ptr = &GPIO_PORTF_DATA_REG;
                    break;
        }
    }
    *port_ptr = ( (*port_ptr&~ChannelGroupIdPtr->mask) | (Level<<ChannelGroupIdPtr->offset) );
}                        

/************************************************************************************
* Service Name: Dio_MaskedWritePort
* Service ID[hex]: 0x13
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): PortId - ID of DIO Port
                   Level - Value to be written
                   Mask - Channels to be masked in the port
                   
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Service to set the value of a given port with required mask.
************************************************************************************/
void Dio_MaskedWritePort ( Dio_PortType PortId, Dio_PortLevelType Level, Dio_PortLevelType Mask ){
    volatile uint32 *port_ptr = NULL_PTR;
    uint8 error = FALSE;
#if (DIO_DEV_ERROR_DETECT == STD_ON)
    if(PortId >= DIO_CONFIGURED_GROUPS){
        error = TRUE;
        Det_ReportError( DIO_MODULE_ID,
                         DIO_INSTANCE_ID,
                         DIO_MASKED_WRITE_PORT_SID,
                         DIO_E_PARAM_INVALID_PORT_ID );
    }
    else{
        
    }
    if(Dio_Status == DIO_NOT_INITIALIZED){
        error = TRUE;
        Det_ReportError( DIO_MODULE_ID,
                         DIO_INSTANCE_ID,
                         DIO_MASKED_WRITE_PORT_SID,
                         DIO_E_UNINIT );
    }
    else{
        
    }
#endif
    
    if(error == FALSE){
        switch(PortId){
            case 0: port_ptr = &GPIO_PORTA_DATA_REG;
                    break;
            case 1: port_ptr = &GPIO_PORTB_DATA_REG;
                    break;
            case 2: port_ptr = &GPIO_PORTC_DATA_REG;
                    break;
            case 3: port_ptr = &GPIO_PORTD_DATA_REG;
                    break;
            case 4: port_ptr = &GPIO_PORTE_DATA_REG;
                    break;
            case 5: port_ptr = &GPIO_PORTF_DATA_REG;
                    break;
        }
    }
    *port_ptr = ( (*port_ptr&~Mask) | (Level) );
}
#endif
