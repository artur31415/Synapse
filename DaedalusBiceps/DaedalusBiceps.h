/*************************************************************************************************************************
    DEVELOPED BY:   ARTUR FERREIRA MOREIRA
    DATE:           MARCH, 20 OF 2017
    EMAIL:          artur31415926@gmail.com
    WEBPAGE:        asgardlab.netne.net/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
v1.0:
    This library was developed to work with the android app "Daedalus Biceps".

    The app features ways to control robot arms using arduio.
    You can create, save and edit profiles of those Arms.
    You can as well manage schedules of poses for the actuators on the robot arm and play them

    Look at the examples to understand how the library works.
**************************************************************************************************************************/


#ifndef DaedalusBiceps_h
#define DaedalusBiceps_h

#include "SoftwareSerial.h"
#include "Arduino.h"


class DaedalusBiceps
{
  private:

  SoftwareSerial BTSerial;


  String BeginMsg;
  String EndMsg;



  int* actuators = 0;
  int actuatorsSize = 0;

  bool IsNewData = false;

  public:
    DaedalusBiceps(int rx, int tx, int baudRate);

    String str;
    String LastStr;

    //
    int GetActuatorValue(int index);
    void SetNumberOfActuators(int size);

    bool NewValues();
    void BTListen();




    //Update Loop Method
    void updateLoop();

    //Protocol Methods
    bool DecryptMsg(String in);
};

#endif
