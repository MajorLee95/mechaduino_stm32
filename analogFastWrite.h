//187kHz PWM implementation.  Stock analogWrite is much slower and is very audible!

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * \brief SAMD products have only one reference for ADC
 *
 * *** STM32F401 PORT ***
 * Sur STM32F4 avec le core Arduino, on ne manipule plus les registres SAMD21
 * dans analogFastWrite(). L'implémentation côté .cpp utilise analogWrite()
 * configuré en 10 bits (via analogWriteResolution(10)) sur une pin PWM.
 */

extern void analogFastWrite( uint32_t ulPin, uint32_t ulValue ) ; // *** STM32F401 PORT ***

#ifdef __cplusplus
}
#endif








