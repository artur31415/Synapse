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
    In this example the two pwm outputs of the arduino are controlled by the two scrollbars that are on the app ui

[PT-BR]
    Neste exemplo as duas saidas pwm do arduino são controladas pelas duas scrollbars que estão na interface do 
    aplicativo.
**************************************************************************************************************************/
#include <AndroidShield.h>

AndroidShield shield(10, 11); //RX_PIN, TX_PIN

int PwmPins[2] = {5, 6};

void setup()
{
    
}

void loop()
{
    for(int i = 0; i < NUM_OF_SCROLLBARS; ++i)
    {
        int lei = shield.scrollbarRead(i);//0-255
        analogWrite(PwmPins[i], lei);
    }
    
    
    shield.updateLoop(200); //ms 
}