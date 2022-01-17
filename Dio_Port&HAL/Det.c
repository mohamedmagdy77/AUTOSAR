 /******************************************************************************
 *
 * Module: Det
 *
 * File Name: Det.c
 *
 * Description:  Det stores the development errors reported by other modules.
 *
 * Author: Mohamed Magdy
 ******************************************************************************/

#include "Det.h"

uint16 GlobalModuleId = 0;
uint8 GlobalInstanceId = 0;
uint8 GlobalApiId = 0;
uint8 GlobalErrorId = 0;

Std_ReturnType Det_ReportError( uint16 ModuleId,
                                uint8 InstanceId,
                                uint8 ApiId,
                                uint8 ErrorId )
{
    GlobalModuleId =   ModuleId ;
    GlobalInstanceId = InstanceId;
    GlobalApiId =      ApiId;
    GlobalErrorId =    ErrorId; 
    return E_OK;
}

