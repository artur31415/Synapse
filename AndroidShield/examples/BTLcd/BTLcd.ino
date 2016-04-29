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
    In this example data is writen on the lcd screen that is on the app ui

[PT-BR]
    Neste exemplo dados são escritos na tela lcd que está na interface do aplicativo
**************************************************************************************************************************/
#include <AndroidShield.h>

AndroidShield shield(10, 11); //RX_PIN, TX_PIN

String aStr = "Arduino time = ";

void setup()
{
    shield.BTLcdGoTo(0);
    shield.BTLcdPrint("AndroidShield lcd Demo");
    
    shield.BTLcdGoTo(1);
}

void loop()
{
    aStr = aStr + millis();
    shield.BTLcdPrint(aStr);
    
    
    shield.updateLoop(200); //ms 
}