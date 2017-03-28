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
    This example reads the state of the first button on the ui of the app and use it to control the led on the 13 pin

[PT-BR]
    Este exemplo lê o estado do primeiro botão da interface no aplicativo e usa esta leitura para controlar o led que está
    no pino 13
**************************************************************************************************************************/
#include <AndroidShieldPro.h>

AndroidShieldPro shield(10, 11); //RX_PIN, TX_PIN

int Led = 13;

void setup()
{
    pinMode(Led, OUTPUT);
	
	Serial.begin(9600);
	
	shield.listen();
}

void loop()
{

	if(shield.isConnected())//then is connected!
	{
		bool ButtonState0 = shield.buttonRead(0);
    
		if(ButtonState0 == true)
			digitalWrite(Led, HIGH);
		else
			digitalWrite(Led, LOW);
	}
	else
	{
		Serial.println("NOT CONNECTED!");
	}
    
    
    shield.updateLoop(200); //ms 
}