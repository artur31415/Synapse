/*************************************************************************************************************************
    DEVELOPED BY:   ARTUR FERREIRA MOREIRA
    DATE:           APRIL, 18 OF 2016
    EMAIL:          artur31415926@gmail.com
    WEBPAGE:        asgardlab.netne.net/Synapse
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
[ENG-USA]
    AndroidShield is a library developed to be used with the android app "Android Shield Arduino"
    that can be found on the store.
    
    If you download and are using the app, thanks for the preference.
    For feature requests, any criticism or ideas, mail me or visit my webpage.

[PT-BR]
    AndroidShield é uma biblioteca desenvolvida para ser usada com o aplicativo android "Android Shield Arduino"
    que pode ser encontrado na store.
    
    Se você baixou e esta usando o aplicativo, obrigado pela preferencia.
    Para pedir funções a mais no app, qualquer critica ou ideias, me mande um email ou visite minha webpage.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
[ENG-USA]
    This example uses the buttons on the app ui to control the leds states

[PT-BR]
    Este exemplo usa o estado dos botões na interface do aplicativo para controlar os estados dos leds
**************************************************************************************************************************/
#include <AndroidShield.h>

AndroidShield shield(10, 11); //RX_PIN, TX_PIN

int LedsPins[5] = {2, 3, 4, 5, 6};//Pins

void setup()
{
    for(int i = 0; i < 5; ++i)
    {
        pinMode(LedsPins[i], OUTPUT);
    }
}

void loop()
{
    for(int i = 0; i < NUM_OF_BUTTONS; ++i)
    {
        digitalWrite(LedsPins[i], shield.buttonRead(i));
    }
    
    shield.updateLoop(200); //ms 
}