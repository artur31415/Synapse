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
    This example is a advanced blink, it toogles the state of the red led (the first) on the android app and also the led
    on the pin 13 on the arduino, the frequency of the blink is controlled by the first scrollbar on the app.

[PT-BR]
    Este exemplo é um blink mais avançado, ele inverte o estado do led vermelho (primeiro led) na interface do aplicativo
    android e ao mesmo tempo inverte o estado do led no pino 13 do arduino, a frequencia é controlada pela scrollbar do 
    aplicativo.
**************************************************************************************************************************/
#include <AndroidShieldPro.h>

AndroidShieldPro shield(10, 11); //RX_PIN, TX_PIN

int Led = 13;
int UiLed = 0;
bool UiLedState = false;
int LedState = LOW;

void setup()
{
    pinMode(Led, OUTPUT);
	
	Serial.begin(9600);
	
	shield.listen();
}

void loop()
{
	int val = 0;
	
	if(shield.isConnected())//then is connected!
	{
		 val = shield.scrollbarRead(0);//0-255
		
		shield.ledWrite(UiLed, UiLedState);
		digitalWrite(Led, LedState);
		
		UiLedState = !UiLedState;
		LedState = !LedState;
	}
	else
	{
		Serial.println("NOT CONNECTED!");
	}

    
    
    shield.updateLoop(200 + val * 1000 / 255); //ms 
}