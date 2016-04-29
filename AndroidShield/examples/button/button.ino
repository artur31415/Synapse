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
    This example reads the state of the first button on the ui of the app and use it to control the led on the 13 pin

[PT-BR]
    Este exemplo lê o estado do primeiro botão da interface no aplicativo e usa esta leitura para controlar o led que está
    no pino 13
**************************************************************************************************************************/
#include <AndroidShield.h>

AndroidShield shield(10, 11); //RX_PIN, TX_PIN

int Led = 13;

void setup()
{
    pinMode(Led, OUTPUT);
}

void loop()
{
    bool ButtonState0 = shield.buttonRead(0);
    
    if(ButtonState0 == true)
        digitalWrite(Led, HIGH);
    else
        digitalWrite(Led, LOW);
    
    shield.updateLoop(200); //ms 
}