/*************************************************************************************************************************
    DEVELOPED BY:   ARTUR FERREIRA MOREIRA
    DATE:           FEBRUARY, 1 OF 2017
    EMAIL:          artur31415926@gmail.com
    WEBPAGE:        asgardlab.netne.net
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
[ENG-USA]
    AndroidShieldPro is a library developed to be used with the android app "Android Shield Arduino Pro"
    that can be found on the store.
    
    If you download and are using the app, thanks for the preference.
    For feature requests, any criticism or ideas, mail me or comment on the app on appstore.

[PT-BR]
    AndroidShieldPro é uma biblioteca desenvolvida para ser usada com o aplicativo android "Android Shield Arduino Pro"
    que pode ser encontrado na store.
    
    Se você baixou e esta usando o aplicativo, obrigado pela preferencia.
    Para pedir funções a mais no app, qualquer critica ou ideias, me mande um email ou comente no aplicativo na store.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
[ENG-USA]
    In this example the five leds connected to the arduino are attached to the five buttons on the app ui and the same 
    happens to the four pwm outputs on the arduino, those are attached to the four scrollbars on the app ui.

[PT-BR]
    Neste exemplo os cinco leds conectados no arduino estão linkados com os cinco botões da interface do aplicativo e o 
    mesmo ocorre com as quatro saidas pwms do arduino, as mesmas estão linkadas com as quatro scrollbars da interface do
    aplicativo.
**************************************************************************************************************************/
#include <AndroidShieldPro.h>

AndroidShieldPro shield(10, 11); //RX_PIN, TX_PIN

int PwmPins[4] = {3, 5, 6, 9};
int LedsPins[5] = {2, 4, 7, 8, 12};//Pins

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
	
	Serial.begin(9600);
	
	shield.listen();
    
}

void loop()
{
	if(shield.isConnected())//then is connected!
	{
	}
	else
	{
		Serial.println("NOT CONNECTED!");
	}
    shield.updateLoop(200); //ms 
}