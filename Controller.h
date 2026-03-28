//Contains the TC5 Handler declaration
// *** STM32F401 PORT ***
// Sur STM32F4, on n'utilise plus TC5 ni WAIT_TC16_REGS_SYNC().
// On garde juste la déclaration de TC5_Handler() pour que le reste du code compile.

#ifndef __CONTROLLER_H__
#define  __CONTROLLER_H__

// *** STM32F401 PORT ***
// Suppression de WAIT_TC16_REGS_SYNC(x) car il n'existe pas sur STM32F4.
// Cette macro n'est plus nécessaire : la synchronisation est gérée par la core Arduino STM32.

void TC5_Handler();  // Déclaration conservée pour compatibilité

#endif