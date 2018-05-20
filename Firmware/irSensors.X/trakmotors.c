
#include <xc.h>
#include "common.h"
#include "trakmotors.h"

TRAK_MOVEMENT_T trakMovement = TRAK_INIT;
TRAK_DIRECTION_T trakDirection;
uint32 trakMoveTimer = 0;
uint32 trakMoveTargetOdo = 0;



void trakMovementStatemachine(void)
{
    switch(trakMovement)
    {
        default:
        case TRAK_INIT:
            trakMotion(TRAK_FULL_STOP, 0x00);
            trakMovement = TRAK_STOPPED;
            break;
            
        case TRAK_STOPPED:
            break;
            
        case TRAK_ODO_MOVE:
            if(cumulativeLeftOdometer >= trakMoveTargetOdo)
            {
                trakMotion(TRAK_FULL_STOP, 0x00);
                trakMovement = TRAK_STOPPED;                
            }
            break;
            
        case TRAK_TIME_MOVE:
            if(trakMoveTimer == 0x00)
            {
                trakMotion(TRAK_FULL_STOP, 0x00);
                trakMovement = TRAK_STOPPED;                
            }
            break;
            
        case TRAK_VELOCITY_MOVE:
            break;                                
    }    
}


void trakMotion(TRAK_DIRECTION_T trakDirection, uint16 trakSpeed)
{
    switch(trakDirection)
    {
        case TRAK_FORWARD:
            rightMotor(MOTOR_FORWARD, trakSpeed);
            leftMotor(MOTOR_FORWARD, trakSpeed);
            break;

        case TRAK_REVERSE:
            rightMotor(MOTOR_REVERSE, trakSpeed);
            leftMotor(MOTOR_REVERSE, trakSpeed);
            break;

        case TRAK_AXIAL_RIGHT_TURN:
            rightMotor(MOTOR_REVERSE, trakSpeed);
            leftMotor(MOTOR_FORWARD, trakSpeed);
            break;

        case TRAK_BRAKE_RIGHT_TURN:
            rightMotor(MOTOR_BRAKE, 0);
            leftMotor(MOTOR_FORWARD, trakSpeed);
            break;

        case TRAK_AXIAL_LEFT_TURN:
            rightMotor(MOTOR_FORWARD, trakSpeed);
            leftMotor(MOTOR_REVERSE, trakSpeed);
            break;

        case TRAK_BRAKE_LEFT_TURN:
            rightMotor(MOTOR_FORWARD, trakSpeed);
            leftMotor(MOTOR_BRAKE, 0);
            break;
            
        case TRAK_COAST:
            rightMotor(MOTOR_COAST, 0);
            leftMotor(MOTOR_COAST, 0);
            break;

        default:
        case TRAK_FULL_STOP:
            rightMotor(MOTOR_BRAKE, 0);
            leftMotor(MOTOR_BRAKE, 0);
            break;
    }
}


void initMotorPWMs(void)
{
    //motor connections:
    //  Right IN1   OC3
    //  Right IN2   OC4
    //  Left IN1    OC1
    //  Left IN2    OC2
    
    //OCxRS is duty cycle

    OC1CON = 0x0000; // Turn off the OC1 when performing the setup    
    OC1R = 0x0064; // Initialize primary Compare register    
    OC1RS = MOTOR_PWM_PERIOD + 1; // Initialize secondary Compare register    
    OC1CON = 0x0006; // Configure for PWM mode without Fault pin enabled
    
    OC2CON = 0x0000; // Turn off the OC1 when performing the setup    
    OC2R = 0x0064; // Initialize primary Compare register    
    OC2RS = MOTOR_PWM_PERIOD + 1; // Initialize secondary Compare register    
    OC2CON = 0x0006; // Configure for PWM mode without Fault pin enabled
    
    OC3CON = 0x0000; // Turn off the OC1 when performing the setup    
    OC3R = 0x0064; // Initialize primary Compare register    
    OC3RS = MOTOR_PWM_PERIOD + 1; // Initialize secondary Compare register    
    OC3CON = 0x0006; // Configure for PWM mode without Fault pin enabled
    
    OC4CON = 0x0000; // Turn off the OC1 when performing the setup    
    OC4R = 0x0064; // Initialize primary Compare register    
    OC4RS = 0x0000; // Initialize secondary Compare register    
    OC4CON = 0x0006; // Configure for PWM mode without Fault pin enabled

    PR2 = MOTOR_PWM_PERIOD; // Set period
    
    IFS0CLR = 0x00000100; // Clear the T2 interrupt flag
//    IEC0SET = 0x00000100; // Enable T2 interrupt
//    IPC2SET = 0x0000001C; // Set T2 interrupt priority to 7

    T2CONSET = 0x8000; // Enable Timer2

    OC1CONSET = 0x8000; // Enable OC1    
    OC2CONSET = 0x8000; // Enable OC1    
    OC3CONSET = 0x8000; // Enable OC1    
    OC4CONSET = 0x8000; // Enable OC1    
    
       
}

void rightMotor(MOTOR_DIRECTION_T motorDirection, uint16 motorSpeed)
{    
    switch(motorDirection)
    {
        case MOTOR_FORWARD:
            OC3RS = motorSpeed; //PWM on IN1
            OC4RS = 0x0000;     //IN2 low
            break;
            
        case MOTOR_REVERSE:
            OC3RS = 0x0000;     //IN1 low
            OC4RS = motorSpeed; //PWM on IN2
            break;
                        
        case MOTOR_COAST:
            //PWM outputs set low
            OC3RS = 0x0000;
            OC4RS = 0x0000;
            break;

        default:
        case MOTOR_BRAKE:
            //PWM outputs set high
            OC3RS = MOTOR_PWM_PERIOD + 1;
            OC4RS = MOTOR_PWM_PERIOD + 1;
            break;        
    }        
}


void leftMotor(MOTOR_DIRECTION_T motorDirection, uint16 motorSpeed)
{
    switch(motorDirection)
    {
        case MOTOR_FORWARD:
            OC1RS = motorSpeed; //PWM on IN1
            OC2RS = 0x0000;     //IN2 low
            break;
            
        case MOTOR_REVERSE:
            OC1RS = 0x0000;     //IN1 low
            OC2RS = motorSpeed; //PWM on IN2
            break;
                        
        case MOTOR_COAST:
            //PWM outputs set low
            OC1RS = 0x0000;
            OC2RS = 0x0000;
            break;

        default:
        case MOTOR_BRAKE:
            //PWM outputs set high
            OC1RS = MOTOR_PWM_PERIOD + 1;
            OC2RS = MOTOR_PWM_PERIOD + 1;
            break;        
    }        
}



void motorPWMtest(uint8 iterations)
{
    while(iterations)
    {
        initMotorPWMs();
        DelayByCounts(1000);
        trakMotion(TRAK_FORWARD, MOTOR_HALF_SPEED);
        DelayByCounts(1000);
        trakMotion(TRAK_AXIAL_RIGHT_TURN, MOTOR_HALF_SPEED);
        DelayByCounts(1000);
        trakMotion(TRAK_AXIAL_LEFT_TURN, MOTOR_HALF_SPEED);
        DelayByCounts(1000);
        trakMotion(TRAK_BRAKE_LEFT_TURN, MOTOR_HALF_SPEED);
        DelayByCounts(1000);
        trakMotion(TRAK_BRAKE_RIGHT_TURN, MOTOR_HALF_SPEED);
        DelayByCounts(1000);
        trakMotion(TRAK_COAST, MOTOR_HALF_SPEED);
        DelayByCounts(1000);
        trakMotion(TRAK_REVERSE, MOTOR_HALF_SPEED);
        DelayByCounts(1000);
        trakMotion(TRAK_FULL_STOP, MOTOR_HALF_SPEED);
        DelayByCounts(1000);

        iterations--;
    }
}