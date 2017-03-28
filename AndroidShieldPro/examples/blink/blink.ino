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
    This example is a simple blink, it toogles the state of the red led (the first) on the android device

[PT-BR]
    Este exemplo é um simples blink, ele inverte o estado do led vermelho (o primeiro) no disposivito android
**************************************************************************************************************************/
#include <AndroidShieldPro.h>

AndroidShieldPro shield(10, 11); //RX_PIN, TX_PIN

void setup()
{
	Serial.begin(9600);
	
	shield.listen();
}

void loop()
{
	if(shield.isConnected())//then is connected!
	{
		shield.ledToggle(0);
	}
	else
	{
		Serial.println("NOT CONNECTED!");
	}
    
    shield.updateLoop(500); //500 ms 
}