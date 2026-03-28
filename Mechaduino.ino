
/*
  -------------------------------------------------------------
  Mechaduino 0.1 & 0.2 Firmware  v0.1.5
  SAM21D18 (Arduino Zero compatible), AS5047 encoder, A4954 driver

  All Mechaduino related materials are released under the
  Creative Commons Attribution Share-Alike 4.0 License
  https://creativecommons.org/licenses/by-sa/4.0/

  Many thanks to all contributors!
  --------------------------------------------------------------
  
  Controlled via a SerialUSB terminal at 115200 baud.

  Implemented serial commands are:

 s  -  step
 d  -  dir
 p  -  print [step number] , [encoder reading]

 c  -  calibration routine
 e  -  check encoder diagnositics
 q  -  parameter query

 x  -  position mode
 v  -  velocity mode
 t  -  torque mode

 y  -  enable control loop
 n  -  disable control loop
 r  -  enter new setpoint

 j  -  step response
 k  -  edit controller gains -- note, these edits are stored in volatile memory and will be reset if power is cycled
 g  -  generate sine commutation table
 m  -  print main menu


  ...see serialCheck() in Utils for more details

*/

/*
  Mechaduino Firmware v0.1.5 - PORTAGE STM32F401CCU6
  Compatible Arduino IDE avec core STM32 officielle (stm32duino)
*/

#include <SPI.h>
#include <Wire.h>

#include "Parameters.h"
#include "State.h"
#include "Utils.h"
#include "Controller.h"
#include "analogFastWrite.h"
 #include "HardwareTimer.h"

// *** STM32F401 PORT ***
// HardwareTimer pour remplacer TC5 SAMD21 (Fs = 6500 Hz)
HardwareTimer *controlTimer = nullptr;


void setup() {
  // *** STM32F401 PORT ***
  // Configuration série : SerialUSB -> Serial sur la plupart des cores STM32F4
  // (ou garde SerialUSB si ta Black Pill supporte USB CDC)
  SerialUSB.begin(115200);
  while (!SerialUSB && millis() < 5000) {}  // Attendre USB si disponible
  
  SerialUSB.println("\n\n----- Mechaduino STM32F401CCU6 -----");
  SerialUSB.print("Firmware: "); SerialUSB.println(firmware_version);
  SerialUSB.print("Identifier: "); SerialUSB.println(identifier);
  SerialUSB.println("*** PORTÉ DE SAMD21 vers STM32F401CCU6 ***\n");

  setupPins();
  setupSPI();
  
  // *** STM32F401 PORT : CONFIG TIMER CONTRÔLE (remplace setupTCInterrupts SAMD21) ***
  SerialUSB.println("Configuring control timer (6500 Hz)...");
  
  // Timer2 (ou TIM3) pour boucle de contrôle Fs=6500Hz
  controlTimer = new HardwareTimer(TIM2);  // *** MODIF STM32F4 ***
  controlTimer->setOverflow(6500, HERTZ_FORMAT);  // Fs = 6500 Hz comme original
  controlTimer->attachInterrupt(TC5_Handler);     // Appelle TC5_Handler() existant !
  controlTimer->pause();  // Démarre en pause (activé par enableTCInterrupts())
  
  SerialUSB.println("Timer configured. Use 'y' to enable closed loop.");
  
  configureStepDir();
  configureEnablePin();
  
  // *** STM32F401 PORT ***
  // Alias SerialUSB si nécessaire (selon ta core STM32)
  SerialUSB.println("Setup complete. Type 'm' for menu.");
}

void loop() {
  serialCheck();  // Menu série (inchangé)
  
  // *** STM32F401 PORT ***
  // Vérification enable_pin pour sécurité (version logicielle)
  if (digitalRead(enable_pin) == HIGH) {
    disableTCInterrupts();
  }
}



