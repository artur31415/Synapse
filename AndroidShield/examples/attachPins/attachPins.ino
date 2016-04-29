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
    In this example the five leds connected to the arduino are attached to the five buttons on the app ui and the same 
    happens to the two pwm outputs on the arduino, those are attached to the two scrollbars on the app ui.

[PT-BR]
    Neste exemplo os cinco leds conectados no arduino estão linkados com os cinco botões da interface do aplicativo e o 
    mesmo ocorre com as duas saidas pwms do arduino, as mesmas estão linkadas com as duas scrollbars da interface do
    aplicativo.
**************************************************************************************************************************/
#include <AndroidShield.h>

AndroidShield shield(10, 11); //RX_PIN, TX_PIN

int PwmPins[2] = {5, 6};
int LedsPins[5] = {2, 3, 4, 5, 6};//Pins

void setup()
{
    for(int i = 0; i < NUM_OF_BUTTONS; ++i)
    {
        pinMode(LedsPins[i], OUTPUT);
        
        shield.buttonAttach(i, LedsPins[i]);
    }
    
    for(int i = 0; i < NUM_OF_SCROLLBARS; ++i)
    {
        shield.scrollbarAttach(i, PwmPins[i]);
    }
    
}

void loop()
{
    
    shield.updateLoop(200); //ms 
}