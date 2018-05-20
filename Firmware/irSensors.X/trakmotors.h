/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _TRAKMOTORS_H    /* Guard against multiple inclusion */
#define _TRAKMOTORS_H

#include "common.h"


#define MOTOR_PWM_PERIOD 0x00C7
#define MOTOR_HALF_SPEED 0x0064


typedef enum{
    MOTOR_FORWARD,
    MOTOR_REVERSE,
    MOTOR_COAST,
    MOTOR_BRAKE
}MOTOR_DIRECTION_T;

typedef enum{
    TRAK_FORWARD,
    TRAK_REVERSE,
    TRAK_AXIAL_RIGHT_TURN,
    TRAK_BRAKE_RIGHT_TURN,
    TRAK_AXIAL_LEFT_TURN,
    TRAK_BRAKE_LEFT_TURN,
    TRAK_COAST,
    TRAK_FULL_STOP
}TRAK_DIRECTION_T;

typedef enum{
    TRAK_INIT,
    TRAK_STOPPED,
    TRAK_ODO_MOVE,
    TRAK_TIME_MOVE,
    TRAK_VELOCITY_MOVE
}TRAK_MOVEMENT_T;


extern TRAK_MOVEMENT_T trakMovement;
extern TRAK_DIRECTION_T trakDirection;
extern uint32 trakMoveTimer;
extern uint32 trakMoveTargetOdo;

extern void initMotorPWMs(void);
extern void trakMotion(TRAK_DIRECTION_T trakDirection, uint16 trakSpeed);
extern void rightMotor(MOTOR_DIRECTION_T motorDirection, uint16 motorSpeed);
extern void leftMotor(MOTOR_DIRECTION_T motorDirection, uint16 motorSpeed);
extern void trakMovementStatemachine(void);



#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
