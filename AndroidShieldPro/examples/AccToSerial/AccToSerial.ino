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
    In this example the accelerometer data is read from the ui and shown on serial output

[PT-BR]
    Neste exemplo os dados do acelerometro são lidos da interface e mostrados na saida serial
    aplicativo.
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
		 Serial.print("Acc = {X: ");
		 Serial.print(shield.AccReadX());
		 Serial.print(", Y: ");
		 Serial.print(shield.AccReadY());
		 Serial.print(", Z: ");
		 Serial.print(shield.AccReadZ());
		 Serial.println("}");
	}
	else
	{
		Serial.println("NOT CONNECTED!");
	}
	
    
    
    
    shield.updateLoop(200); //ms 
}