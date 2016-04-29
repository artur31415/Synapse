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
    In this example the two analog inputs on the arduino are displyed on the two progressbars that are on the app ui

[PT-BR]
    Neste exemplo as duas entradas analogicas do arduino são mostradas nas duas progressbars que estão na interface do
    aplicativo.
**************************************************************************************************************************/
#include <AndroidShield.h>

AndroidShield shield(10, 11); //RX_PIN, TX_PIN

int AnalogPins[2] = {A0, A1};

void setup()
{
    
}

void loop()
{
    for(int i = 0; i < NUM_OF_PROGRESSBAR; ++i)
    {
        int lei = analogRead(AnalogPins[i]);//0-1023
        int conv = map(lei, 0, 1023, 0, 255);//0-255

        shield.progressbarWrite(i, conv);
    }
    
    
    shield.updateLoop(200); //ms 
}