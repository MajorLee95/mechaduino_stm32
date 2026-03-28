//187kHz PWM implementation.  Stock analogWrite is much slower and is very audible!
// *** STM32F401 PORT ***
// Sur STM32F4 avec le core Arduino, on n'utilise plus les registres SAMD21 (ADC/DAC/TCC/TC).
// On implémente analogFastWrite comme un simple wrapper autour de analogWrite(),
// en configurant la résolution PWM à 10 bits pour rester cohérent avec uMAX et sin_1.

#include <Arduino.h>
#include "analogFastWrite.h"

#ifdef __cplusplus
extern "C" {
#endif

// *** STM32F401 PORT ***
// Résolution d'écriture courante (10 bits pour 0..1023)
static int _writeResolution = 10;
static bool pwmInitDone = false;

// Optionnel : helper de mapping de résolution, conservé pour compatibilité
static inline uint32_t mapResolution(uint32_t value, uint32_t from, uint32_t to)
{
    if (from == to) {
        return value;
    }
    if (from > to) {
        return value >> (from - to);
    }
    return value << (to - from);
}

// Initialisation de la résolution PWM STM32
static void initPwm()
{
    if (!pwmInitDone)
    {
        analogWriteResolution(_writeResolution);   // *** STM32F401 PORT ***
        pwmInitDone = true;
    }
}

// Right now, PWM output only works on the pins with
// hardware support. For the rest of the pins, we default
// to digital output (même comportement logique que l'original).
void analogFastWrite(uint32_t pin, uint32_t value)
{
    initPwm(); // *** STM32F401 PORT ***

    // Clamp à la pleine échelle 10 bits
    if (value > 1023) value = 1023;

    // On tente d'utiliser PWM si possible
    // (la core STM32 gère elle-même si la pin supporte le PWM).
    analogWrite(pin, value); // *** STM32F401 PORT ***
}

#ifdef __cplusplus
}
#endif
