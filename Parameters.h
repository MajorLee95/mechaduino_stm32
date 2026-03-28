//Contains the Mechaduino parameter declarations

#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

#define firmware_version "0.1.5"    //firmware version
#define identifier "x"              // change this to help keep track of multiple mechaduinos (printed on startup)

// *** STM32F401 PORT ***
// #define SerialUSB Serial1  //Cette version compile
#define SerialUSB Serial


#define LOOKUP_SIZE 8192

//----Current Parameters-----

extern volatile float Ts;
extern volatile float Fs;

extern volatile float pKp;
extern volatile float pKi;
extern volatile float pKd;
extern volatile float pLPF;


extern volatile float vKp;
extern volatile float vKi;
extern volatile float vKd;
extern volatile float vLPF;

// extern const float lookup[];
// *** STM32F401 PORT ***
extern float lookup[LOOKUP_SIZE];
// *** STM32F401 PORT ***


extern volatile float pLPFa;
extern volatile float pLPFb;
extern volatile float vLPFa;
extern volatile float vLPFb;


extern const int spr; //  200 steps per revolution
extern const float aps; // angle per step
extern int cpr; //counts per rev
extern const float stepangle;

extern volatile float PA;  //

extern const float iMAX;
extern const float rSense;
extern volatile int uMAX;


extern const int sin_1[];


// ======================
//   PIN DEFINITIONS
// ======================
// NOTE: les numéros ci-dessous sont des numéros de pins Arduino tels que
// définis par le core STM32F4 (à adapter à ton variant WeAct/BlackPill). [web:6][web:12]
// L'objectif est de garder les mêmes noms de macros que sur SAMD21.

#define IN_4      PB0   // *** STM32F401 PORT ***: choisir une pin GPIO pour IN_4 (ex: PB0)
#define IN_3      PB1   // *** STM32F401 PORT ***: choisir une pin GPIO pour IN_3
#define VREF_2    PA8   // *** STM32F401 PORT ***: pin PWM pour VREF_2 (ex: PA8 TIM1_CH1)
#define VREF_1    PA9   // *** STM32F401 PORT ***: pin PWM pour VREF_1 (ex: PA9 TIM1_CH2)
#define IN_2      PB6   // *** STM32F401 PORT ***: choisir une pin GPIO pour IN_2
#define IN_1      PB7   // *** STM32F401 PORT ***: choisir une pin GPIO pour IN_1
#define ledPin    PC13  // *** STM32F401 PORT ***: LED embarquée sur beaucoup de Black Pill
#define chipSelectPin PA4 // *** STM32F401 PORT ***: SPI CS (ex: PA4, SPI1_NSS)

#define step_pin    PA0 // *** STM32F401 PORT ***: pin step (interruption possible)
#define dir_pin     PA1 // *** STM32F401 PORT ***: pin dir
#define enable_pin  PA2 // *** STM32F401 PORT ***: pin enable

// ======================
//   FAST IO MACROS
// ======================
// Sur SAMD21, ces macros utilisaient REG_PORT_OUTx & PORT_PAx pour des accès rapides. [web:1]
// Sur STM32F4 Arduino, on les remplace par digitalWrite() pour garder l'API
// et limiter les changements ailleurs dans le code.
// Si besoin de vitesse, ces macros pourront être optimisées avec les registres GPIO STM32. [web:6]

#include <Arduino.h>  // *** STM32F401 PORT ***: requis pour digitalWrite()

//for faster digitalWrite (compatible):  -----------------
// *** STM32F401 PORT ***: remplace REG_PORT_OUTSET0 / OUTCLR0 par digitalWrite().

#define IN_1_HIGH()       digitalWrite(IN_1, HIGH)   // *** STM32F401 PORT ***
#define IN_1_LOW()        digitalWrite(IN_1, LOW)    // *** STM32F401 PORT ***
#define IN_2_HIGH()       digitalWrite(IN_2, HIGH)   // *** STM32F401 PORT ***
#define IN_2_LOW()        digitalWrite(IN_2, LOW)    // *** STM32F401 PORT ***
#define IN_3_HIGH()       digitalWrite(IN_3, HIGH)   // *** STM32F401 PORT ***
#define IN_3_LOW()        digitalWrite(IN_3, LOW)    // *** STM32F401 PORT ***
#define IN_4_HIGH()       digitalWrite(IN_4, HIGH)   // *** STM32F401 PORT ***
#define IN_4_LOW()        digitalWrite(IN_4, LOW)    // *** STM32F401 PORT ***
#define ledPin_HIGH()     digitalWrite(ledPin, HIGH) // *** STM32F401 PORT ***
#define ledPin_LOW()      digitalWrite(ledPin, LOW)  // *** STM32F401 PORT ***
#define CHIPSELECT_HIGH() digitalWrite(chipSelectPin, HIGH) // *** STM32F401 PORT ***
#define CHIPSELECT_LOW()  digitalWrite(chipSelectPin, LOW)  // *** STM32F401 PORT ***

#define ENABLE_PROFILE_IO    // Define to enable profiling I/O pins

#ifdef ENABLE_PROFILE_IO  
  #define TEST1   PA3   // *** STM32F401 PORT ***: choisir une pin libre pour TEST1

  #define TEST1_HIGH()  digitalWrite(TEST1, HIGH) // *** STM32F401 PORT ***
  #define TEST1_LOW()   digitalWrite(TEST1, LOW)  // *** STM32F401 PORT ***

#else
  #define TEST1_HIGH()
  #define TEST1_LOW() 
#endif

#endif
