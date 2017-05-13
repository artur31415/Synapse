/*************************************************************************************************************************
    DEVELOPED BY:   ARTUR FERREIRA MOREIRA
    DATE:           MAY, 13 OF 2017
    EMAIL:          artur31415926@gmail.com
    WEBPAGE:        http://daedalusstone.com/
    INSTAGRAM:      https://www.instagram.com/artur31415/
    GOOGLEPLAY:     https://play.google.com/store/apps/developer?id=Synapse
    YOUTUBE:        https://www.youtube.com/channel/UC6blOB30re0J-Oiksqaob1g/videos
    GITHUB:         https://github.com/artur31415
    TWITTER:        https://twitter.com/artur31415
    LINKEDIN:       https://www.linkedin.com/in/artur31415

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
[ENG-USA]
      This library was developed to work with the Android app "Controllium", with which,
    you can control your ESP8266 projects using your Android device.
      Through the library you can attach any of the UI elements to the Arduino hardware pins
    accordingly to theirs functionalities.
      You can use widgets to send and receive data from the ESP8266 using you Android Device.
      Look at the examples to understand how the library works.

      Any Ideas or criticism, email me.

    Have fun!
[PT-BR]
      Esta biblioteca foi desenvolvida para trabalhar com o aplicativo Android "Controllium", com o qual,
    Você pode controlar seus projetos de ESP8266 usando seu dispositivo Android.
      Através da biblioteca você pode anexar qualquer um dos elementos UI para os pinos de hardware arduino
    De acordo com s  uas funcionalidades.
      Voce pode usar widgets para enviar e receber dados do ESP8266 usando o seu dispositivo Android.
    Veja os exemplos para entender como funciona a biblioteca.

      Quaisquer idéias ou críticas, email me.

    Divirta-se!
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                  LedMatrix                                                           //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
[ENG-USA]
    In this example each off the nine leds on the controller on the android app are toggle, one at a time, at every
    one second. And the switch on the controller toggles on and off a pin on the ESP8266.

[PT-BR]
    Neste exemplo cada um dos nove leds no controle no aplicativo android tem os seus estados logicos invetidos, um de
    cada vez, a cada um segundo. E o switch no controle liga e desliga um pino na ESP8266.
**************************************************************************************************************************/


#include <Controllium.h>

#include <ESP8266WiFi.h>

//Wifi SSID and Pass
const char* ROUTER_SSID = "YOUR_SSID";
const char* ROUTER_PASS = "YOUR_PASS";

//Soft AP SSID and Pass
char* SOFT_AP_SSID = "Controllium";
char* SOFT_AP_PASS = "0123456789";

//ESP8266 DIGITAL PINS
int D[] = {16, 5, 4, 0, 2, 14, 12, 13, 15};

//variable used to control the blinking of the "alive" led
long ledBlinkLastTime = 0;

//variable used to control the controller led blink on the app
long lastTimeUIBlink = 0;

//variable to index the nine leds on the controller on the app
int LedAnimationCounter = 1;

//Controllium object
Controllium controllium("ESP_LedMatrix");//Name of this device, if you have more than one connected, provide a different name to each

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                        UTILS FUNCTIONS BEGIN                                                  /////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Jusy a function to blink a pin
void blink(int pin)
{
  for(int i = 0; i < 2; ++i)
  {
    digitalWrite(pin, LOW);
    delay(50);
    digitalWrite(pin, HIGH);
    delay(50);
  }

  digitalWrite(pin, LOW);
  delay(100);
}

//Setup Soft AP
void setupAP()
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  delay(100);

  randomSeed(analogRead(A0) + analogRead(A0));
  sprintf(SOFT_AP_SSID, "%s_%04d", SOFT_AP_SSID, random(1023));

  WiFi.softAP(SOFT_AP_SSID, SOFT_AP_PASS, 6);
}

//Try to connects to WIFI
//If it fails, returns false
//Otherwise, returns true
bool connectToWifi()
{
  WiFi.begin(ROUTER_SSID, ROUTER_PASS);

  // Wait for connect to AP
  Serial.print("\n\nConnecting to ");

  Serial.println(ROUTER_SSID);

  int tries=0;

  while (WiFi.status() != WL_CONNECTED)
   {
    delay(500);
    Serial.print(".");
    tries++;
    if (tries > 30)
    {
      break;
    }
  }

  Serial.println();

  if (tries > 30)
  {
    Serial.println("Failed To Connect, initializing the Soft AP!\n\n");
    return false;
  }

  return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                        UTILS FUNCTIONS BEGIN                                                  /////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
  //Init the serial for debug
  Serial.begin(115200);

  //Init the ESP pins
  for(int i = 0; i < 9; ++i)
  {
    pinMode(D[i], OUTPUT);
    digitalWrite(D[i], LOW);
  }

  if(connectToWifi())//Try to connect to WIFI
  {
    Serial.println("Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    digitalWrite(D[1], HIGH);// Pin to show that it is connected to wifi
  }
  else//Otherwise, setup a soft AP
  {
    setupAP();

    Serial.println("Soft AP On!");

    Serial.print("\nSSID = ");
    Serial.println(SOFT_AP_SSID);
    Serial.print("PASS = ");
    Serial.println(SOFT_AP_PASS);

    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());

    digitalWrite(D[2], HIGH);// Pin to show that it is NOT connected to wifi
  }

  //Begin server
  Serial.print("\nUdp server started at port ");
  Serial.println(UDP_DEFAULT_PORT);
  controllium.BeginUdpServer(UDP_DEFAULT_PORT);

  //Instantiate Controllium Devices and add them to the controllium object
  ControlliumDevice switch0("SWITCH_0", DEVICE_TYPE_BUTTON, "0");

  ControlliumDevice led0("LED_0", DEVICE_TYPE_LED, "0");
  ControlliumDevice led1("LED_1", DEVICE_TYPE_LED, "0");
  ControlliumDevice led2("LED_2", DEVICE_TYPE_LED, "0");
  ControlliumDevice led3("LED_3", DEVICE_TYPE_LED, "0");
  ControlliumDevice led4("LED_4", DEVICE_TYPE_LED, "0");
  ControlliumDevice led5("LED_5", DEVICE_TYPE_LED, "0");
  ControlliumDevice led6("LED_6", DEVICE_TYPE_LED, "0");
  ControlliumDevice led7("LED_7", DEVICE_TYPE_LED, "0");
  ControlliumDevice led8("LED_8", DEVICE_TYPE_LED, "0");


  controllium.AddDevice(switch0);


  controllium.AddDevice(led0);
  controllium.AddDevice(led1);
  controllium.AddDevice(led2);
  controllium.AddDevice(led3);
  controllium.AddDevice(led4);
  controllium.AddDevice(led5);
  controllium.AddDevice(led6);
  controllium.AddDevice(led7);
  controllium.AddDevice(led8);

  Serial.println("Waiting for clients to connect...");
}

void loop()
{
  //Just a blinking led to show that the device is alive
  if(millis() - ledBlinkLastTime > 2000)
  {
    ledBlinkLastTime = millis();
    blink(D[3]);
  }

  if(controllium.Update(200))//Returns true if a new msg was received
  {
    Serial.println("New MSG!\n\n");

    //SWITCH_0 TO pin
    float val = (float)controllium.GetDevice("SWITCH_0")->GetDoubleValue();
    if(val >= 0)
      digitalWrite(D[4], (int)val);
  }

  //Toggle all nine leds on the app at every 1 second
  if(millis() - lastTimeUIBlink >= 1000)
  {
    lastTimeUIBlink = millis();

    //Toggle the actual led on the controller
    controllium.GetDevice(LedAnimationCounter)->ToggleState();
    if(controllium.GetDevice(LedAnimationCounter)->GetDoubleValue() == 0 && controllium.GetDevice(LedAnimationCounter)->GetPreviousDoubleValue() == 0)
    {
      ++LedAnimationCounter;
      if(LedAnimationCounter >= 9)
        LedAnimationCounter = 1;
    }
  }
}
