//Contains TC5 Controller definition
//The main control loop is executed by the timer interrupt:
// On STM32F401, this is now a generic control loop ISR (attached to a timer).

#include <SPI.h>

#include "State.h"
#include "Utils.h"
#include "Parameters.h"


// --- STM32F401 PORT ---
// Sur SAMD21, cette fonction s'appelait TC5_Handler.
// Sur STM32F401, on garde le même nom pour laisser le reste du code inchangé
// si tu réattaches cette fonction à un timer STM32 (via attachInterrupt(HardwareTimer)).
// Sinon tu peux la renommer en quelque chose comme controlLoopISR() et adapter le file d'init.
// Dans tous les cas, le contenu de la boucle de contrôle reste inchangé.

void TC5_Handler() {
    static int print_counter = 0;  //used by step response

    // Sur STM32, tu n'as plus TC5->COUNT16.INTFLAG, donc cette ligne de test
    // sera remplacée par la gestion d'interruption de timer (via attachInterrupt ou HAL).
    // Ici, on garde la fonction identique, elle est simplement appelée à Ts = 1/Fs.
    // Le flag OVF est géré par le timer, pas par le code STM32 dans ce fichier.

    TEST1_HIGH();

    y = lookup[readEncoder()];
    
    if ((y - y_1) < -180.0) wrap_count += 1;
    else if ((y - y_1) > 180.0) wrap_count -= 1;

    yw = y + 360.0 * wrap_count;

    if (mode == 'h') {
        hybridControl();    //hybrid control is still under development...
    }
    else {
        switch (mode) {
            case 'x':   //position control
                e = r - yw;
                
                ITerm += pKi * e;
                if (ITerm > 150.0)  ITerm = 150.0;
                else if (ITerm < -150.0) ITerm = -150.0;
                
                DTerm = pLPFa*DTerm - pLPFb*pKd*(yw - yw_1);
                
                u = pKp*e + ITerm + DTerm;
                break;

            case 'v':   //velocity control
                v = vLPFa*v + vLPFb*(yw - yw_1);

                e = r - v;

                ITerm += vKi * e;
                if (ITerm > 200.0)  ITerm = 200.0;
                else if (ITerm < -200.0) ITerm = -200.0;

                u = vKp*e + ITerm - vKd*(e - e_1);
                break;

            case 't':   //torque control
                u = 1.0 * r;
                break;

            default:
                u = 0.0;
                break;
        }

        y_1 = y;      // copy current y to previous (before PA)

        if (u > 0.0) {
            y += PA;
            if (u > uMAX) u = uMAX;
        } else {
            y -= PA;
            if (u < -uMAX) u = -uMAX;
        }

        U = abs(u);

        if (abs(e) < 0.1) ledPin_HIGH();
        else ledPin_LOW();

        output(-y, round(U));   // update phase currents
    }

    // Stocke les valeurs passées pour les filtres / contrôle avancé
    e_2 = e_1;
    e_1 = e;
    u_2 = u_1;
    u_1 = u;
    yw_1 = yw;

    if (print_yw == true) {
        print_counter += 1;
        if (print_counter >= 5) {
            // *** STM32F401 PORT ***
            // SerialUSB sera un alias de Serial ou SerialUSB selon la core STM32
            // (voir le commentaire dans Parameters.h)
            SerialUSB.println(int(yw * 1024));
            print_counter = 0;
        }
    }

    TEST1_LOW();
}
