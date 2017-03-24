/*************************************************************************************************************************
    DEVELOPED BY:   ARTUR FERREIRA MOREIRA
    DATE:           MARCH, 20 OF 2017
    EMAIL:          artur31415926@gmail.com
    WEBPAGE:        asgardlab.netne.net/
**************************************************************************************************************************/
#include <DaedalusBiceps.h>

DaedalusBiceps daedalusBiceps(10, 11, 9600); //RX_PIN, TX_PIN

long lastTime = 0;

#include <Servo.h>

Servo myservo;
Servo myservo2;

void setup()
{
  myservo.attach(9);
  myservo2.attach(6);

  daedalusBiceps.SetNumberOfActuators(2);

  Serial.begin(9600);
  daedalusBiceps.BTListen();
}

void loop()
{
    if(daedalusBiceps.NewValues())
    {

      myservo.write(daedalusBiceps.GetActuatorValue(0));
      myservo2.write(daedalusBiceps.GetActuatorValue(1));

    }
    daedalusBiceps.updateLoop();
}
