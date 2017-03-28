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
    This example uses the buttons on the app ui to control the leds states

[PT-BR]
    Este exemplo usa o estado dos botões na interface do aplicativo para controlar os estados dos leds
**************************************************************************************************************************/
#include <AndroidShieldPro.h>

AndroidShieldPro shield(10, 11); //RX_PIN, TX_PIN

int LedsPins[5] = {2, 3, 4, 5, 6};//Pins

void setup()
{
    for(int i = 0; i < NUM_OF_LEDS; ++i)
    {
        pinMode(LedsPins[i], OUTPUT);
    }
	
	Serial.begin(9600);
	
	shield.listen();
}

void loop()
{

	if(shield.isConnected())//then is connected!
	{
		for(int i = 0; i < NUM_OF_BUTTONS; ++i)
		{
			digitalWrite(LedsPins[i], shield.buttonRead(i));
		}
	}
	else
	{
		Serial.println("NOT CONNECTED!");
	}
	
    
    
    shield.updateLoop(200); //ms 
}