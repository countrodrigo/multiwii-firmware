#ifndef DEF_H_
#define DEF_H_

/**************************************************************************************/
/***************             test configurations                   ********************/
/**************************************************************************************/
#if COPTERTEST == 4
  #define QUADX
  #define CRIUS_SE
  #define SPEKTRUM 2048
  #define LED_RING
  #define GPS_SERIAL 2
  #define NMEA
  #define LOG_VALUES 2
  #define LOG_PERMANENT
  #define LOG_PERMANENT_SERVICE_LIFETIME 36000
#elif defined(COPTERTEST)
  #error "*** this test is not yet defined"
#endif


/**************************************************************************************/
/***************             Proc specific definitions             ********************/
/**************************************************************************************/
// Proc auto detection
#define MEGA


/**************************************************************************************/
/***************             motor and servo numbers               ********************/
/**************************************************************************************/
#define SERVO_RATES      {30,30,100,100,100,100,100,100}

#if defined(COPTER_WITH_SERVO) || defined(SERVO_TILT) || defined(GIMBAL) || defined(CAMTRIG) || defined(SERVO_MIX_TILT)
  #define SERVO
#endif

#if defined(DYNBALANCE)
  #define DYNBAL 1
#else
  #define DYNBAL 0
#endif

#if defined(MEGA) && defined(MEGA_HW_PWM_SERVOS)
  #define TRI_SERVO  4
#else
  #define TRI_SERVO  6
#endif

#if defined(GIMBAL)
  #define NUMBER_MOTOR     0
  #define PRI_SERVO_FROM   1 // use servo from 1 to 2
  #define PRI_SERVO_TO     2
#elif defined(QUADX)
  #define NUMBER_MOTOR     4
#endif

#if (defined(SERVO_TILT)|| defined(SERVO_MIX_TILT))&& defined(CAMTRIG)
  #define SEC_SERVO_FROM   1 // use servo from 1 to 3
  #define SEC_SERVO_TO     3
#else
  #if defined(SERVO_TILT)|| defined(SERVO_MIX_TILT)
    // if A0 and A1 is taken by motors, we can use A2 and 12 for Servo tilt
    #if defined(A0_A1_PIN_HEX) && (NUMBER_MOTOR == 6) && defined(PROMINI)
      #define SEC_SERVO_FROM   3 // use servo from 3 to 4
      #define SEC_SERVO_TO     4
    #else
      #define SEC_SERVO_FROM   1 // use servo from 1 to 2
      #define SEC_SERVO_TO     2
    #endif
  #endif
  #if defined(CAMTRIG)
    #define SEC_SERVO_FROM   3 // use servo 3
    #define SEC_SERVO_TO     3
  #endif
#endif

#if defined(SIRIUS_AIR) || defined(SIRIUS_AIR_GPS)
  #define RCAUX2PIND17
#endif

/**************************  all the Mega types  ***********************************/
#if defined(MEGA)
  #define LEDPIN_PINMODE             DDRB  |= (1<<7); DDRC  |= (1<<7); // Arduino pin 13, pin 30
  #define LEDPIN_TOGGLE              PINB  |= (1<<7); PINC  |= (1<<7);
  #define LEDPIN_ON                  PORTB |= (1<<7); PORTC |= (1<<7);
  #define LEDPIN_OFF                 PORTB &= ~(1<<7);PORTC &= ~(1<<7);
  #define BUZZERPIN_PINMODE            DDRC  |= (1<<5); // Arduino pin 32
  #if defined PILOTLAMP
    #define PL_PIN_ON                  PORTC |= 1<<5;
    #define PL_PIN_OFF                 PORTC &= ~(1<<5);
  #else
//    #define BUZZERPIN_ON               PORTC |= 1<<5;
//    #define BUZZERPIN_OFF              PORTC &= ~(1<<5);
	#define BUZZERPIN_ON               PORTF |= 1<<7;
    #define BUZZERPIN_OFF              PORTF &= ~(1<<7);
  #endif 
    
  #if !defined(DISABLE_POWER_PIN)
    #define POWERPIN_PINMODE           DDRC |= 1<<0; // Arduino pin 37
    #define POWERPIN_ON                PORTC |= 1<<0;
    #define POWERPIN_OFF               PORTC &= ~(1<<0);
  #else
    #define POWERPIN_PINMODE           ;
    #define POWERPIN_ON                ;
    #define POWERPIN_OFF               ;
  #endif
  #define I2C_PULLUPS_ENABLE         PORTD |= 1<<0; PORTD |= 1<<1;       // PIN 20&21 (SDA&SCL)
  #define I2C_PULLUPS_DISABLE        PORTD &= ~(1<<0); PORTD &= ~(1<<1);
  #define PINMODE_LCD                DDRE |= 1<<0; // Arduino pin 0
  #define LCDPIN_OFF                 PORTE &= ~1; //switch OFF digital PIN 0
  #define LCDPIN_ON                  PORTE |= 1;
  #define STABLEPIN_PINMODE          DDRC |= 1<<6; // Arduino pin 31
  #define STABLEPIN_ON               PORTC |= 1<<6;
  #define STABLEPIN_OFF              PORTC &= ~(1<<6);
  #if defined(PPM_ON_THROTTLE)
    //configure THROTTLE PIN (A8 pin) as input witch pullup and enabled PCINT interrupt
    #define PPM_PIN_INTERRUPT        DDRK &= ~(1<<0); PORTK |= (1<<0);  PCICR |= (1<<2); PCMSK2 |= (1<<0);
  #else
    #define PPM_PIN_INTERRUPT        attachInterrupt(4, rxInt, RISING);  //PIN 19, also used for Spektrum satellite option
  #endif
  #if !defined(RX_SERIAL_PORT)
    #define RX_SERIAL_PORT           1
  #endif
  //RX PIN assignment inside the port //for PORTK
  #define THROTTLEPIN                0  //PIN 62 =  PIN A8
  #define ROLLPIN                    1  //PIN 63 =  PIN A9
  #define PITCHPIN                   2  //PIN 64 =  PIN A10
  #define YAWPIN                     3  //PIN 65 =  PIN A11
  #define AUX1PIN                    4  //PIN 66 =  PIN A12
  #define AUX2PIN                    5  //PIN 67 =  PIN A13
  #define AUX3PIN                    6  //PIN 68 =  PIN A14
  #define AUX4PIN                    7  //PIN 69 =  PIN A15
  #define V_BATPIN                   A0    // Analog PIN 0
  #define PSENSORPIN                 A2    // Analog PIN 2
  #define PCINT_PIN_COUNT            8
  #define PCINT_RX_BITS              (1<<2),(1<<4),(1<<5),(1<<6),(1<<7),(1<<0),(1<<1),(1<<3)
  #define PCINT_RX_PORT              PORTK
  #define PCINT_RX_MASK              PCMSK2
  #define PCIR_PORT_BIT              (1<<2)
  #define RX_PC_INTERRUPT            PCINT2_vect
  #define RX_PCINT_PIN_PORT          PINK
  
//  #define SERVO_1_PINMODE            DDRC |= 1<<3;DDRL |= 1<<5; // Arduino pin 34 , pin 44 // TILT_PITCH - WING left
//  #define SERVO_1_PIN_HIGH           PORTC |= 1<<3;PORTL |= 1<<5;
//  #define SERVO_1_PIN_LOW            PORTC &= ~(1<<3);PORTL &= ~(1<<5);
//  #define SERVO_2_PINMODE            DDRC |= 1<<2;DDRL |= 1<<4; // Arduino pin 35 , pin 45 // TILT_ROLL  - WING right
//  #define SERVO_2_PIN_HIGH           PORTC |= 1<<2;PORTL |= 1<<4;
//  #define SERVO_2_PIN_LOW            PORTC &= ~(1<<2);PORTL &= ~(1<<4);
//  #define SERVO_3_PINMODE            DDRC |= 1<<4;DDRL |= 1<<3; // Arduino pin 33 , pin 46 // CAM TRIG  - alt TILT_PITCH
//  #define SERVO_3_PIN_HIGH           PORTC |= 1<<4;PORTL |= 1<<3;
//  #define SERVO_3_PIN_LOW            PORTC &= ~(1<<4);PORTL &= ~(1<<3);
  #define SERVO_4_PINMODE            DDRC |= 1<<0; DDRH |= 1<<4; // Arduino pin 37 , pin 7 // new       - alt TILT_ROLL
  #define SERVO_4_PIN_HIGH           PORTC |= 1<<0; PORTH |= 1<<4;
  #define SERVO_4_PIN_LOW            PORTC &= ~(1<<0);PORTH &= ~(1<<4);

  #define SERVO_5_PINMODE            DDRH |= 1<<3; // Arduino pin 6                        // BI LEFT
  #define SERVO_5_PIN_HIGH           PORTH |= 1<<3;
  #define SERVO_5_PIN_LOW            PORTH &= ~(1<<3);
  #define SERVO_6_PINMODE            DDRE |= 1<<4; // Arduino pin 2                        // TRI REAR - BI RIGHT
  #define SERVO_6_PIN_HIGH           PORTE |= 1<<4;
  #define SERVO_6_PIN_LOW            PORTE &= ~(1<<4);
  #define SERVO_7_PINMODE            DDRE |= 1<<3; // Arduino pin 5                        // new
  #define SERVO_7_PIN_HIGH           PORTE |= 1<<3;
  #define SERVO_7_PIN_LOW            PORTE &= ~(1<<3);
  #define SERVO_8_PINMODE            DDRE |= 1<<5; // Arduino pin 3                        // new
  #define SERVO_8_PIN_HIGH           PORTE |= 1<<5;
  #define SERVO_8_PIN_LOW            PORTE &= ~(1<<5);
#endif

/**********************   Sort the Servos for the most ideal SW PWM     ************************/
// this define block sorts the above selected servos to be in a simple order from 1 - (count of total servos)
// its pretty fat but its the best way i found to get less compiled code and max speed in the ISR without loosing its flexibility
#if (PRI_SERVO_FROM == 1) || (SEC_SERVO_FROM == 1)
  #define LAST_LOW SERVO_1_PIN_LOW
  #define SERVO_1_HIGH SERVO_1_PIN_HIGH
  #define SERVO_1_LOW SERVO_1_PIN_LOW
  #define SERVO_1_ARR_POS  0
#endif
#if (PRI_SERVO_FROM <= 2 && PRI_SERVO_TO >= 2) || (SEC_SERVO_FROM <= 2 && SEC_SERVO_TO >= 2) 
  #undef LAST_LOW
  #define LAST_LOW SERVO_2_PIN_LOW
  #if !defined(SERVO_1_HIGH)
    #define SERVO_1_HIGH SERVO_2_PIN_HIGH
    #define SERVO_1_LOW SERVO_2_PIN_LOW  
    #define SERVO_1_ARR_POS 1
  #else
    #define SERVO_2_HIGH SERVO_2_PIN_HIGH
    #define SERVO_2_LOW SERVO_2_PIN_LOW   
    #define SERVO_2_ARR_POS 1
  #endif
#endif
#if (PRI_SERVO_FROM <= 3 && PRI_SERVO_TO >= 3) || (SEC_SERVO_FROM <= 3 && SEC_SERVO_TO >= 3) 
  #undef LAST_LOW
  #define LAST_LOW SERVO_3_PIN_LOW
  #if !defined(SERVO_1_HIGH)
    #define SERVO_1_HIGH SERVO_3_PIN_HIGH
    #define SERVO_1_LOW SERVO_3_PIN_LOW
    #define SERVO_1_ARR_POS 2 
  #elif !defined(SERVO_2_HIGH)
    #define SERVO_2_HIGH SERVO_3_PIN_HIGH
    #define SERVO_2_LOW SERVO_3_PIN_LOW 
    #define SERVO_2_ARR_POS 2 
  #else
    #define SERVO_3_HIGH SERVO_3_PIN_HIGH
    #define SERVO_3_LOW SERVO_3_PIN_LOW  
    #define SERVO_3_ARR_POS 2   
  #endif
#endif
#if (PRI_SERVO_FROM <= 4 && PRI_SERVO_TO >= 4) || (SEC_SERVO_FROM <= 4 && SEC_SERVO_TO >= 4) 
  #undef LAST_LOW
  #define LAST_LOW SERVO_4_PIN_LOW
  #if !defined(SERVO_1_HIGH)
    #define SERVO_1_HIGH SERVO_4_PIN_HIGH
    #define SERVO_1_LOW SERVO_4_PIN_LOW
    #define SERVO_1_ARR_POS 3  
  #elif !defined(SERVO_2_HIGH)
    #define SERVO_2_HIGH SERVO_4_PIN_HIGH
    #define SERVO_2_LOW SERVO_4_PIN_LOW
    #define SERVO_2_ARR_POS 3
  #elif !defined(SERVO_3_HIGH)
    #define SERVO_3_HIGH SERVO_4_PIN_HIGH
    #define SERVO_3_LOW SERVO_4_PIN_LOW
    #define SERVO_3_ARR_POS 3    
  #else
    #define SERVO_4_HIGH SERVO_4_PIN_HIGH
    #define SERVO_4_LOW SERVO_4_PIN_LOW 
    #define SERVO_4_ARR_POS 3     
  #endif
#endif
#if (PRI_SERVO_FROM <= 5 && PRI_SERVO_TO >= 5) || (SEC_SERVO_FROM <= 5 && SEC_SERVO_TO >= 5)
  #undef LAST_LOW
  #define LAST_LOW SERVO_5_PIN_LOW
  #if !defined(SERVO_1_HIGH)
    #define SERVO_1_HIGH SERVO_5_PIN_HIGH
    #define SERVO_1_LOW SERVO_5_PIN_LOW
    #define SERVO_1_ARR_POS 4   
  #elif !defined(SERVO_2_HIGH)
    #define SERVO_2_HIGH SERVO_5_PIN_HIGH
    #define SERVO_2_LOW SERVO_5_PIN_LOW
    #define SERVO_2_ARR_POS 4  
  #elif !defined(SERVO_3_HIGH)
    #define SERVO_3_HIGH SERVO_5_PIN_HIGH
    #define SERVO_3_LOW SERVO_5_PIN_LOW
    #define SERVO_3_ARR_POS 4   
  #elif !defined(SERVO_4_HIGH)
    #define SERVO_4_HIGH SERVO_5_PIN_HIGH
    #define SERVO_4_LOW SERVO_5_PIN_LOW
    #define SERVO_4_ARR_POS 4   
  #else
    #define SERVO_5_HIGH SERVO_5_PIN_HIGH
    #define SERVO_5_LOW SERVO_5_PIN_LOW 
    #define SERVO_5_ARR_POS 4     
  #endif
#endif
#if (PRI_SERVO_FROM <= 6 && PRI_SERVO_TO >= 6) || (SEC_SERVO_FROM <= 6 && SEC_SERVO_TO >= 6)
  #undef LAST_LOW
  #define LAST_LOW SERVO_6_PIN_LOW
  #if !defined(SERVO_1_HIGH)
    #define SERVO_1_HIGH SERVO_6_PIN_HIGH
    #define SERVO_1_LOW SERVO_6_PIN_LOW 
    #define SERVO_1_ARR_POS 5 
  #elif !defined(SERVO_2_HIGH)
    #define SERVO_2_HIGH SERVO_6_PIN_HIGH
    #define SERVO_2_LOW SERVO_6_PIN_LOW
    #define SERVO_2_ARR_POS 5 
  #elif !defined(SERVO_3_HIGH)
    #define SERVO_3_HIGH SERVO_6_PIN_HIGH
    #define SERVO_3_LOW SERVO_6_PIN_LOW
    #define SERVO_3_ARR_POS 5   
  #elif !defined(SERVO_4_HIGH)
    #define SERVO_4_HIGH SERVO_6_PIN_HIGH
    #define SERVO_4_LOW SERVO_6_PIN_LOW 
    #define SERVO_4_ARR_POS 5  
  #elif !defined(SERVO_5_HIGH)
    #define SERVO_5_HIGH SERVO_6_PIN_HIGH
    #define SERVO_5_LOW SERVO_6_PIN_LOW 
    #define SERVO_5_ARR_POS 5  
  #else
    #define SERVO_6_HIGH SERVO_6_PIN_HIGH
    #define SERVO_6_LOW SERVO_6_PIN_LOW  
    #define SERVO_6_ARR_POS 5   
  #endif
#endif
#if (PRI_SERVO_FROM <= 7 && PRI_SERVO_TO >= 7) || (SEC_SERVO_FROM <= 7 && SEC_SERVO_TO >= 7)
  #undef LAST_LOW
  #define LAST_LOW SERVO_7_PIN_LOW
  #if !defined(SERVO_1_HIGH)
    #define SERVO_1_HIGH SERVO_7_PIN_HIGH
    #define SERVO_1_LOW SERVO_7_PIN_LOW 
    #define SERVO_1_ARR_POS 6 
  #elif !defined(SERVO_2_HIGH)
    #define SERVO_2_HIGH SERVO_7_PIN_HIGH
    #define SERVO_2_LOW SERVO_7_PIN_LOW
    #define SERVO_2_ARR_POS 6 
  #elif !defined(SERVO_3_HIGH)
    #define SERVO_3_HIGH SERVO_7_PIN_HIGH
    #define SERVO_3_LOW SERVO_7_PIN_LOW
    #define SERVO_3_ARR_POS 6   
  #elif !defined(SERVO_4_HIGH)
    #define SERVO_4_HIGH SERVO_7_PIN_HIGH
    #define SERVO_4_LOW SERVO_7_PIN_LOW 
    #define SERVO_4_ARR_POS 6  
  #elif !defined(SERVO_5_HIGH)
    #define SERVO_5_HIGH SERVO_7_PIN_HIGH
    #define SERVO_5_LOW SERVO_7_PIN_LOW 
    #define SERVO_5_ARR_POS 6  
  #elif !defined(SERVO_6_HIGH)
    #define SERVO_6_HIGH SERVO_7_PIN_HIGH
    #define SERVO_6_LOW SERVO_7_PIN_LOW 
    #define SERVO_6_ARR_POS 6  
  #else
    #define SERVO_7_HIGH SERVO_7_PIN_HIGH
    #define SERVO_7_LOW SERVO_7_PIN_LOW  
    #define SERVO_7_ARR_POS 6   
  #endif
#endif
#if (PRI_SERVO_FROM <= 8 && PRI_SERVO_TO >= 8) || (SEC_SERVO_FROM <= 8 && SEC_SERVO_TO >= 8) 
  #undef LAST_LOW
  #define LAST_LOW SERVO_8_PIN_LOW
  #if !defined(SERVO_1_HIGH)
    #define SERVO_1_HIGH SERVO_8_PIN_HIGH
    #define SERVO_1_LOW SERVO_8_PIN_LOW 
    #define SERVO_1_ARR_POS 7 
  #elif !defined(SERVO_2_HIGH)
    #define SERVO_2_HIGH SERVO_8_PIN_HIGH
    #define SERVO_2_LOW SERVO_8_PIN_LOW
    #define SERVO_2_ARR_POS 7
  #elif !defined(SERVO_3_HIGH)
    #define SERVO_3_HIGH SERVO_8_PIN_HIGH
    #define SERVO_3_LOW SERVO_8_PIN_LOW
    #define SERVO_3_ARR_POS 7  
  #elif !defined(SERVO_4_HIGH)
    #define SERVO_4_HIGH SERVO_8_PIN_HIGH
    #define SERVO_4_LOW SERVO_8_PIN_LOW
    #define SERVO_4_ARR_POS 7  
  #elif !defined(SERVO_5_HIGH)
    #define SERVO_5_HIGH SERVO_8_PIN_HIGH
    #define SERVO_5_LOW SERVO_8_PIN_LOW 
    #define SERVO_5_ARR_POS 7  
  #elif !defined(SERVO_6_HIGH)
    #define SERVO_6_HIGH SERVO_8_PIN_HIGH
    #define SERVO_6_LOW SERVO_8_PIN_LOW 
    #define SERVO_6_ARR_POS 7 
  #elif !defined(SERVO_7_HIGH)
    #define SERVO_7_HIGH SERVO_8_PIN_HIGH
    #define SERVO_7_LOW SERVO_8_PIN_LOW 
    #define SERVO_7_ARR_POS 7  
  #else
    #define SERVO_8_HIGH SERVO_8_PIN_HIGH
    #define SERVO_8_LOW SERVO_8_PIN_LOW  
    #define SERVO_8_ARR_POS 7   
  #endif
#endif

#if ( defined(MEGA) && defined(MEGA_HW_PWM_SERVOS) ) || (defined(PROMICRO) && defined(A32U4_4_HW_PWM_SERVOS))
  #undef SERVO_1_HIGH                                    // No software PWM's if we use hardware MEGA PWM or promicro hardware pwm
  #define HW_PWM_SERVOS
#endif


/**************************************************************************************/
/***************      IMU Orientations and Sensor definitions      ********************/
/**************************************************************************************/

#if defined(CRIUS_AIO_PRO) 
  #define __AVR_ATmega2560__
  #define MPU6050 
  #define HMC5883 
  #define MS561101BA 
  #define ACC_ORIENTATION(X, Y, Z)  {imu.accADC[ROLL]  = -X; imu.accADC[PITCH]  = -Y; imu.accADC[YAW]  =  Z;} 
  #define GYRO_ORIENTATION(X, Y, Z) {imu.gyroADC[ROLL] =  Y; imu.gyroADC[PITCH] = -X; imu.gyroADC[YAW] = -Z;} 
  #define MAG_ORIENTATION(X, Y, Z)  {imu.magADC[ROLL]  =  X; imu.magADC[PITCH]  =  Y; imu.magADC[YAW]  = -Z;} 
  #define MPU6050_I2C_AUX_MASTER // MAG connected to the AUX I2C bus of MPU6050 
  #undef INTERNAL_I2C_PULLUPS 
  #define I2C_SPEED 400000L         //400kHz fast mode
  //servo pins on AIO board is at pins 44,45,46, then release pins 33,34,35 for other usage
  //eg. pin 33 on AIO can be used for LEDFLASHER output
  #define SERVO_1_PINMODE            pinMode(44,OUTPUT);        // TILT_PITCH
  #define SERVO_1_PIN_HIGH           PORTL |= 1<<5;
  #define SERVO_1_PIN_LOW            PORTL &= ~(1<<5);
  #define SERVO_2_PINMODE            pinMode(45,OUTPUT);        // TILT_ROLL 
  #define SERVO_2_PIN_HIGH           PORTL |= 1<<4;
  #define SERVO_2_PIN_LOW            PORTL &= ~(1<<4);
  #define SERVO_3_PINMODE            pinMode(46,OUTPUT);        // CAM TRIG
  #define SERVO_3_PIN_HIGH           PORTL |= 1<<3;
  #define SERVO_3_PIN_LOW            PORTL &= ~(1<<3);
#endif

#if defined(MultiWii_32U4_SE)
  #define MPU6050
  #define HMC5883
  #define MPU6050_I2C_AUX_MASTER // MAG connected to the AUX I2C bus of MPU6050
  #define MS561101BA
  #define ACC_ORIENTATION(X, Y, Z)  {imu.accADC[ROLL]  = -X; imu.accADC[PITCH]  = -Y; imu.accADC[YAW]  =  Z;}
  #define GYRO_ORIENTATION(X, Y, Z) {imu.gyroADC[ROLL] =  Y; imu.gyroADC[PITCH] = -X; imu.gyroADC[YAW] = -Z;}
  #define MAG_ORIENTATION(X, Y, Z)  {imu.magADC[ROLL]  =  X; imu.magADC[PITCH]  =  Y; imu.magADC[YAW]  = -Z;}
  #undef INTERNAL_I2C_PULLUPS
#endif

#if defined(MultiWii_32U4_SE_no_baro)
  #define MPU6050
  #define HMC5883
  #define MPU6050_I2C_AUX_MASTER // MAG connected to the AUX I2C bus of MPU6050
  #define ACC_ORIENTATION(X, Y, Z)  {imu.accADC[ROLL]  = -X; imu.accADC[PITCH]  = -Y; imu.accADC[YAW]  =  Z;}
  #define GYRO_ORIENTATION(X, Y, Z) {imu.gyroADC[ROLL] =  Y; imu.gyroADC[PITCH] = -X; imu.gyroADC[YAW] = -Z;}
  #define MAG_ORIENTATION(X, Y, Z)  {imu.magADC[ROLL]  =  X; imu.magADC[PITCH]  =  Y; imu.magADC[YAW]  = -Z;}
  #undef INTERNAL_I2C_PULLUPS
#endif

/**************************************************************************************/
/***************              Sensor Type definitions              ********************/
/**************************************************************************************/

#if defined(ADXL345) || defined(BMA020) || defined(BMA180) || defined(BMA280) || defined(MMA7455) || defined(ADCACC) || defined(LIS3LV02) || defined(LSM303DLx_ACC) || defined(MPU6050) || defined(LSM330) || defined(MMA8451Q)
  #define ACC 1
#else
  #define ACC 0
#endif

#if defined(HMC5883) || defined(HMC5843) || defined(AK8975) || defined(MAG3110)
  #define MAG 1
#else
  #define MAG 0
#endif

#if defined(ITG3200) || defined(ITG3050) || defined(L3G4200D) || defined(MPU6050) || defined(LSM330) || defined(MPU3050) || defined(WMP)
  #define GYRO 1
#else
  #define GYRO 0
#endif

#if defined(BMP085) || defined(MS561101BA)
  #define BARO 1
#else
  #define BARO 0
#endif

#if defined(GPS_SERIAL)  || defined(I2C_GPS)
  #define GPS 1
#else
  #define GPS 0
#endif

#if defined(USE_MSP_WP)
  #define NAVCAP 1
#else
  #define NAVCAP 0
#endif

#if defined(SRF02) || defined(SRF08) || defined(SRF10) || defined(SRC235) || defined(I2C_GPS_SONAR)
  #define SONAR 1
#else
  #define SONAR 0
#endif

#if defined(EXTENDED_AUX_STATES)
  #define EXTAUX 1
#else
  #define EXTAUX 0
#endif

#if defined(RX_RSSI_CHAN)
  #define RX_RSSI
#endif

/**************************************************************************************/
/***************      Multitype decleration for the GUI's          ********************/
/**************************************************************************************/
#if defined(QUADX)
  #define MULTITYPE 3
#elif defined(GIMBAL)
  #define MULTITYPE 5
#elif defined(VTAIL4)
  #define MULTITYPE 17
#endif

/**************************************************************************************/
/***************          Some unsorted "chain" defines            ********************/
/**************************************************************************************/

#if defined(POWERMETER_HARD) || defined(POWERMETER_SOFT)
  #define POWERMETER
  #define PLEVELSCALE 50 // step size you can use to set alarm
  #define PLEVELDIVSOFT 100000
  #define PLEVELDIV 36000
#endif

#if defined PILOTLAMP 
  #define    PL_CHANNEL OCR0B  //use B since A can be used by camstab
  #define    PL_ISR TIMER0_COMPB_vect
  #define    PL_INIT   TCCR0A=0;TIMSK0|=(1<<OCIE0B);PL_CHANNEL=PL_IDLE;PilotLamp(PL_GRN_OFF);PilotLamp(PL_BLU_OFF);PilotLamp(PL_RED_OFF);PilotLamp(PL_BZR_OFF);
  #define    BUZZERPIN_ON PilotLamp(PL_BZR_ON);
  #define    BUZZERPIN_OFF PilotLamp(PL_BZR_OFF);
  #define    PL_GRN_ON    25    // 100us
  #define    PL_GRN_OFF   50    // 200us
  #define    PL_BLU_ON    75    // 300us
  #define    PL_BLU_OFF   100    // 400us
  #define    PL_RED_ON    125    // 500us
  #define    PL_RED_OFF   150    // 600us
  #define    PL_BZR_ON    175    // 700us
  #define    PL_BZR_OFF   200    // 800us
  #define    PL_IDLE      125    // 100us
#endif

#if defined(PILOTLAMP)
  #define BUZZER
#endif

//all new Special RX's must be added here
//this is to avoid confusion :)
#if !defined(SERIAL_SUM_PPM) && !defined(SPEKTRUM) && !defined(SBUS) && !defined(SUMD)
  #define STANDARD_RX
#endif

#if defined(SPEKTRUM) || defined(SBUS) || defined(SUMD)
  #define SERIAL_RX
#endif

// Spektrum Satellite
#define BIND_CAPABLE 0  //Used for Spektrum today; can be used in the future for any RX type that needs a bind and has a MultiWii module. 
#if defined(SPEKTRUM)
  #define SPEK_FRAME_SIZE 16
  #if (SPEKTRUM == 1024)
    #define SPEK_CHAN_SHIFT  2       // Assumes 10 bit frames, that is 1024 mode.
    #define SPEK_CHAN_MASK   0x03    // Assumes 10 bit frames, that is 1024 mode.
    #define SPEK_DATA_SHIFT          // Assumes 10 bit frames, that is 1024 mode.
    #define SPEK_BIND_PULSES 3
  #endif
  #if (SPEKTRUM == 2048)
    #define SPEK_CHAN_SHIFT  3       // Assumes 11 bit frames, that is 2048 mode.
    #define SPEK_CHAN_MASK   0x07    // Assumes 11 bit frames, that is 2048 mode.
    #define SPEK_DATA_SHIFT >> 1     // Assumes 11 bit frames, that is 2048 mode.
    #define SPEK_BIND_PULSES 5
  #endif
  #if defined(SPEK_BIND)
    #define BIND_CAPABLE 1
    #if !defined(SPEK_BIND_GROUND)
      #define SPEK_BIND_GROUND 4
    #endif  
    #if !defined(SPEK_BIND_POWER)
      #define SPEK_BIND_POWER  5
    #endif  
    #if !defined(SPEK_BIND_DATA)
      #define SPEK_BIND_DATA   6
    #endif  
  #endif
#endif

#if defined(SBUS)
  #define RC_CHANS 18
#elif defined(SPEKTRUM) || defined(SERIAL_SUM_PPM)
  #define RC_CHANS 12
#else
  #define RC_CHANS 8
#endif

#if !(defined(DISPLAY_2LINES)) && !(defined(DISPLAY_MULTILINE))
  #if (defined(LCD_VT100)) || (defined(OLED_I2C_128x64) || defined(OLED_DIGOLE) )
    #define DISPLAY_MULTILINE
  #else
    #define DISPLAY_2LINES
  #endif
#endif

#if (defined(LCD_VT100))
  #if !(defined(MULTILINE_PRE))
    #define MULTILINE_PRE 6
  #endif
  #if !(defined(MULTILINE_POST))
    #define MULTILINE_POST 9
  #endif
  #if !(defined(DISPLAY_COLUMNS))
    #define DISPLAY_COLUMNS 40
  #endif
#elif (defined(OLED_I2C_128x64) && defined(DISPLAY_FONT_DSIZE))
  #if !(defined(MULTILINE_PRE))
    #define MULTILINE_PRE 1
  #endif
  #if !(defined(MULTILINE_POST))
    #define MULTILINE_POST 3
  #endif
  #if !(defined(DISPLAY_COLUMNS))
    #define DISPLAY_COLUMNS 21
  #endif
#elif (defined(OLED_I2C_128x64))
  #if !(defined(MULTILINE_PRE))
    #define MULTILINE_PRE 3
  #endif
  #if !(defined(MULTILINE_POST))
    #define MULTILINE_POST 5
  #endif
  #if !(defined(DISPLAY_COLUMNS))
    #define DISPLAY_COLUMNS 21
  #endif
#elif (defined(OLED_DIGOLE) && defined(DISPLAY_FONT_DSIZE))
  #if !(defined(MULTILINE_PRE))
    #define MULTILINE_PRE 2
  #endif
  #if !(defined(MULTILINE_POST))
    #define MULTILINE_POST 3
  #endif
#elif (defined(OLED_DIGOLE))
  #if !(defined(MULTILINE_PRE))
    #define MULTILINE_PRE 3
  #endif
  #if !(defined(MULTILINE_POST))
    #define MULTILINE_POST 4
  #endif
  #if !(defined(DISPLAY_COLUMNS))
    #define DISPLAY_COLUMNS 21
  #endif
#endif

#if !(defined(DISPLAY_COLUMNS))
  #define DISPLAY_COLUMNS 16
#endif

#if defined(FRSKY_TELEMETRY) || defined(SPORT_TELEMETRY)
  #define TELEMETRY
#endif

/**************************************************************************************/
/***************               override defaults                   ********************/
/**************************************************************************************/

  /***************               pin assignments ?  ********************/
  #ifdef OVERRIDE_V_BATPIN
    #undef V_BATPIN
    #define V_BATPIN OVERRIDE_V_BATPIN
  #endif
  #ifdef OVERRIDE_PSENSORPIN
    #undef PSENSORPIN
    #define PSENSORPIN OVERRIDE_PSENSORPIN
  #endif
  #ifdef OVERRIDE_LEDPIN_PINMODE
    #undef LEDPIN_PINMODE
    #undef LEDPIN_TOGGLE
    #undef LEDPIN_OFF
    #undef LEDPIN_ON
    #define LEDPIN_PINMODE OVERRIDE_LEDPIN_PINMODE
    #define LEDPIN_TOGGLE  OVERRIDE_LEDPIN_TOGGLE
    #define LEDPIN_OFF     OVERRIDE_LEDPIN_OFF
    #define LEDPIN_ON      OVERRIDE_LEDPIN_ON
  #endif
  #ifdef OVERRIDE_BUZZERPIN_PINMODE
    #undef BUZZERPIN_PINMODE
    #undef BUZZERPIN_ON
    #undef BUZZERPIN_OFF
    #define BUZZERPIN_PINMODE OVERRIDE_BUZZERPIN_PINMODE
    #define BUZZERPIN_ON      OVERRIDE_BUZZERPIN_ON
    #define BUZZERPIN_OFF     OVERRIDE_BUZZERPIN_OFF
  #endif

  /*********  sensors orientation - possibly overriding board defaults  *****/
  #ifdef FORCE_GYRO_ORIENTATION
    #undef GYRO_ORIENTATION
    #define GYRO_ORIENTATION FORCE_GYRO_ORIENTATION
  #endif
  #ifdef FORCE_ACC_ORIENTATION
    #undef ACC_ORIENTATION
    #define ACC_ORIENTATION FORCE_ACC_ORIENTATION
  #endif
  #ifdef FORCE_MAG_ORIENTATION
    #undef MAG_ORIENTATION
    #define MAG_ORIENTATION FORCE_MAG_ORIENTATION
  #endif

  /*********  servo rates                                               *****/
  #ifdef FORCE_SERVO_RATES
    #undef SERVO_RATES
    #define SERVO_RATES FORCE_SERVO_RATES
  #endif
/**************************************************************************************/
/***************               Error Checking Section              ********************/
/**************************************************************************************/

#ifndef NUMBER_MOTOR
        #error "NUMBER_MOTOR is not set, most likely you have not defined any type of multicopter"
#endif

#if (defined(LCD_DUMMY) || defined(LCD_SERIAL3W) || defined(LCD_TEXTSTAR) || defined(LCD_VT100) || defined(LCD_TTY) || defined(LCD_ETPP) || defined(LCD_LCD03) || defined(LCD_LCD03S) || defined(OLED_I2C_128x64) ) || defined(OLED_DIGOLE)
  #define HAS_LCD
#endif

#if (defined(LCD_CONF) || defined(LCD_TELEMETRY)) && !(defined(HAS_LCD) )
  #error "LCD_CONF or LCD_TELEMETRY defined, and choice of LCD not defined.  Uncomment one of LCD_SERIAL3W, LCD_TEXTSTAR, LCD_VT100, LCD_TTY or LCD_ETPP, LCD_LCD03, LCD_LCD03S, OLED_I2C_128x64, OLED_DIGOLE"
#endif

#if defined(POWERMETER_SOFT) && !(defined(VBAT))
  #error "to use powermeter, you must also define and configure VBAT"
#endif

#if defined(WATTS) && !(defined(POWERMETER_HARD)) && !(defined(VBAT))
  #error "to compute WATTS, you must also define and configure both POWERMETER_HARD and VBAT"
#endif

#if defined(LCD_TELEMETRY_AUTO) && !(defined(LCD_TELEMETRY))
  #error "to use automatic telemetry, you MUST also define and configure LCD_TELEMETRY"
#endif

#if defined(LCD_TELEMETRY_STEP) && !(defined(LCD_TELEMETRY))
  #error "to use single step telemetry, you MUST also define and configure LCD_TELEMETRY"
#endif

#if defined(A32U4_4_HW_PWM_SERVOS) && !(defined(HELI_120_CCPM))
  #error "for your protection: A32U4_4_HW_PWM_SERVOS was not tested with your coptertype"
#endif

#if GPS && !defined(NMEA) && !defined(UBLOX) && !defined(MTK_BINARY16) && !defined(MTK_BINARY19) && !defined(INIT_MTK_GPS) && !defined(I2C_GPS) && !defined(VENUS8)
  #error "when using GPS you must specify the protocol NMEA, UBLOX..."
#endif

#if defined(NUNCHUK) || \
    defined( MPU6050_LPF_256HZ) || defined(MPU6050_LPF_188HZ)  || defined( MPU6050_LPF_98HZ) || defined( MPU6050_LPF_42HZ) || \
    defined( MPU6050_LPF_20HZ)  || defined( MPU6050_LPF_10HZ)  || defined( MPU6050_LPF_5HZ)  || \
    defined( ITG3200_LPF_256HZ) || defined( ITG3200_LPF_188HZ) || defined( ITG3200_LPF_98HZ) || defined( ITG3200_LPF_42HZ) || \
    defined( ITG3200_LPF_20HZ)  || defined( ITG3200_LPF_10HZ)
  #error "you use one feature that is no longer supported or has undergone a name change"
#endif

#endif /* DEF_H_ */
