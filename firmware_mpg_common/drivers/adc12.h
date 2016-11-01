/**********************************************************************************************************************
File: adc12.h                                                                

----------------------------------------------------------------------------------------------------------------------
To start a new task using this adc12 as a template:
1. Follow the instructions at the top of adc12.c
2. Use ctrl-h to find and replace all instances of "adc12" with "yournewtaskname"
3. Use ctrl-h to find and replace all instances of "adc12" with "YourNewTaskName"
4. Use ctrl-h to find and replace all instances of "adc12" with "YOUR_NEW_TASK_NAME"
5. Add #include yournewtaskname.h" to configuration.h
6. Add/update any special configurations required in configuration.h (e.g. peripheral assignment and setup values)
7. Delete this text (between the dashed lines)
----------------------------------------------------------------------------------------------------------------------

Description:
Header file for yournewtaskname.c

**********************************************************************************************************************/

#ifndef __adc12_H
#define __adc12_H

/**********************************************************************************************************************
Type Definitions
**********************************************************************************************************************/


/**********************************************************************************************************************
Constants / Definitions
**********************************************************************************************************************/
#define TEMPLATE_INIT (u32)0x0f042700
/*
    31 [0] 
    30 [0] 
    29 [0] 
    28 [0] 

    27 [1] 
    26 [1] 
    25 [1] 
    24 [1] 

    23 [0] 
    22 [0] 
    21 [0] 
    20 [0] 

    19 [0] 
    18 [1] 
    17 [0] 
    16 [0] 

    15 [0] PRESCAL is 23 (gives adc 1MHZ)
    14 [0] 
    13 [1] 
    12 [0] 

    11 [0] 
    10 [1] 
    09 [1] 
    08 [1] 

    07 [0] 
    06 [0] 
    05 [0] 
    04 [0] 

    03 [0] 
    02 [0] 
    01 [0] 
    00 [0] 
*/


/**********************************************************************************************************************
Function Declarations
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/
void adc12Initialize(void);
void adc12RunActiveState(void);


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


/***********************************************************************************************************************
State Machine Declarations
***********************************************************************************************************************/
static void adc12SM_Idle(void);    

static void adc12SM_Error(void);         
static void adc12SM_FailedInit(void);        


#endif /* __adc12_H */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
