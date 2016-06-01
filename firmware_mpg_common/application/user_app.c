/**********************************************************************************************************************
File: user_app.c                                                                

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app as a template:
 1. Copy both user_app.c and user_app.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

Description:
This is a user_app.c file template 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void UserAppInitialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserAppRunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserAppFlags;                       /* Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp_StateMachine;            /* The state machine function pointer */
static u32 UserApp_u32Timeout;                      /* Timeout counter used across states */


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: UserAppInitialize

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void UserAppInitialize(void)
{/*turn on led using the on function*/
 /* All discrete LEDs to off */
  /* Start with red LED on 100%, green and blue off */
  LedPWM(LCD_RED, LED_PWM_100);
  LedPWM(LCD_GREEN, LED_PWM_0);
  LedPWM(LCD_BLUE, LED_PWM_0);
  LedOff(WHITE);
  LedOff(PURPLE);
  LedOff(BLUE);
  LedOff(CYAN);
  LedOff(GREEN);
  LedOff(YELLOW);
  LedOff(ORANGE);
  LedOff(RED);
  
  /* Backlight to white */  
  LedOn(LCD_RED);
  LedOn(LCD_GREEN);
  LedOn(LCD_BLUE);
  
  /* If good initialization, set state to Idle */
  if( 1 )
  {
    UserApp_StateMachine = UserAppSM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp_StateMachine = UserAppSM_FailedInit;
  }

} /* end UserAppInitialize() */


/*----------------------------------------------------------------------------------------------------------------------
Function UserAppRunActiveState()

Description:
Selects and runs one iteration of the current state in the state machine.
All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
  - State machine function pointer points at current state

Promises:
  - Calls the function to pointed by the state machine function pointer
*/
void UserAppRunActiveState(void)
{
  UserApp_StateMachine();

} /* end UserAppRunActiveState */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for a message to be queued */
static void UserAppSM_Idle(void)
{
  #ifdef MPG2
  static LedNumberType aeCurrentLed[]  = {GREEN0, RED0, BLUE0, GREEN0, RED0, BLUE0};
  static LedNumberType aeCurrentLed1[] = {GREEN1, RED1, BLUE1, GREEN1, RED1, BLUE1};
  static LedNumberType aeCurrentLed2[] = {GREEN2, RED2, BLUE2, GREEN2, RED2, BLUE2};
  static LedNumberType aeCurrentLed3[] = {GREEN3, RED3, BLUE3, GREEN3, RED3, BLUE3};
#endif /* MPG2 */

#ifdef MPG1
  static LedNumberType aeCurrentLed[]  = {LCD_GREEN, LCD_RED, LCD_BLUE, LCD_GREEN, LCD_RED, LCD_BLUE};
  
#endif /* MPG 1 */
  static bool abLedRateIncreasing[]   = {TRUE,      FALSE ,TRUE,     FALSE,     TRUE,    FALSE};
  static u8 u8CurrentLedIndex  = 0;
  static u8 u8LedCurrentLevel  = 0;
  static u8 u8DutyCycleCounter = 0;
  static u16 u16Counter = COLOR_CYCLE_TIME;
  u16Counter--;
  /* Check for update color every COLOR_CYCLE_TIME ms */  
  if(u16Counter == 0)
  {
    u16Counter = COLOR_CYCLE_TIME;

    /* Update the current level based on which way it's headed */

    /* Update the value to the current LED */   
    LedPWM( (LedNumberType)aeCurrentLed[u8CurrentLedIndex], (LedRateType)u8LedCurrentLevel);
  
   
  /* Update the current level based on which way it's headed */
    if( abLedRateIncreasing[u8CurrentLedIndex] )
    {
      u8LedCurrentLevel++;
    }
    else
    {
      u8LedCurrentLevel--;
    }

    /* Change direction once we're at the end */
    u8DutyCycleCounter++;
    if(u8DutyCycleCounter == 20)
    {
      u8DutyCycleCounter = 0;
      
      /* Watch for the indexing variable to reset */
      u8CurrentLedIndex++;
      if(u8CurrentLedIndex == 6)
      {
        u8CurrentLedIndex = 0;
      }
      
      /* Set the current level based on what direction we're now going */
      u8LedCurrentLevel = 20;
      if(abLedRateIncreasing[u8CurrentLedIndex])
      {
         u8LedCurrentLevel = 0;
      }
    
    
  }
}
 static u16 u16BlinkCount = 0;
   static u8 u8Counter = 0;

  u16BlinkCount++;
  if(u16BlinkCount == 20)
  {
    u16BlinkCount = 0;
    
    /*Update the counter and roll at 16 */
    u8Counter++;
    if(u8Counter == 8)
    {
      LedOn(RED);
    }
    if(u8Counter == 16)
    {
      LedOn(ORANGE);;
    }
    if(u8Counter == 24)
    {
      LedOn(YELLOW);LedOff(RED);
    }
    if(u8Counter == 32)
    {
      LedOn(GREEN);LedOff(ORANGE);
    }
    if(u8Counter == 38)
    {
      LedOn(CYAN);LedOff(YELLOW);
    }
    if(u8Counter == 46)
    {
      LedOn(BLUE);LedOff(GREEN);
    }
    if(u8Counter == 54)
    {
      LedOn(PURPLE);LedOff(CYAN);
    }
    if(u8Counter == 62)
    {
      LedOn(WHITE);LedOff(BLUE);
    }
    if(u8Counter == 70)
    {
      LedOn(RED);
    }
    if(u8Counter == 78)
    {
      LedOn(ORANGE);;
    }
    if(u8Counter == 86)
    {
      LedOn(YELLOW);LedOff(RED);
    }
    if(u8Counter == 94)
    {
      LedOn(GREEN);LedOff(ORANGE);
    }
    if(u8Counter == 102)
    {
      LedOn(CYAN);LedOff(YELLOW);
    }
    if(u8Counter == 110)
    {
      LedOn(BLUE);LedOff(GREEN);
    }if(u8Counter == 118)
    {
      LedOn(RED);
    }
    if(u8Counter == 126)
    {
      LedOn(ORANGE);
    }
    if(u8Counter == 132)
    {
      LedOn(YELLOW);LedOff(RED);
    }
    if(u8Counter == 140)
    {
      LedOn(GREEN);LedOff(ORANGE);
    }
    if(u8Counter == 148)
    {
      LedOn(RED);
    }
    if(u8Counter == 156)
    {
      LedOn(ORANGE);
    }
    if(u8Counter == 164)
    {
     
      LedOff(RED);
      LedOff(WHITE);
    }
    if(u8Counter == 172)
    {
     
      LedOff(ORANGE);
      LedOff(PURPLE);
    }
    if(u8Counter == 180)
    {
     
      LedOff(YELLOW);
      LedOff(BLUE);
    }
    if(u8Counter == 188)
    {
     
      LedOff(GREEN);
      LedOff(CYAN);
    }
    if(u8Counter == 188)u8Counter =0;
    
    
  
  
  }
} /* end if(u16BlinkCount == 500) */
     

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserAppSM_Error(void)          
{
  
} /* end UserAppSM_Error() */


/*-------------------------------------------------------------------------------------------------------------------*/
/* State to sit in if init failed */
static void UserAppSM_FailedInit(void)          
{
    
} /* end UserAppSM_FailedInit() */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
