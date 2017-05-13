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
**************************************************************************************************************************/


#ifndef ControlliumDevice_h
#define ControlliumDevice_h

#include <Arduino.h>

#define DEVICE_TYPE_BUTTON            		  "B"
#define DEVICE_TYPE_LED               		  "L"
#define DEVICE_TYPE_ACCELEROMETER     		  "A"
#define DEVICE_TYPE_SEEKBAR  				        "S"
#define DEVICE_TYPE_PROGRESSBAR  			      "P"
#define DEVICE_TYPE_ACCELEROMETER 			    "A"
#define DEVICE_TYPE_LABEL 					        "E"
#define DEVICE_TYPE_GSM 					          "M"
#define DEVICE_TYPE_GPS 					          "G"
#define DEVICE_TYPE_TEXT_INPUT 					    "T"

#define PROTOCOL_SEPARATOR                  "|"

#define UNDEFINED_FIELD "UNDEFINED"

class ControlliumDevice
{
  private:
    String name;
    String type;

    String valueStr;
    String PreviousValueStr;

    double valueDouble;
    double PreviousValueDouble;

    bool isValueNumber;

    int myPin;


  public:

    /////////////////////////////////////
    ControlliumDevice();
    ControlliumDevice(String _name);
    ControlliumDevice(String _name, String _type);
    ControlliumDevice(String _name, String _type, String _value);

    ~ControlliumDevice();
    //////////////////////////////////
    void SetFromString(String _deviceString);
    static ControlliumDevice FromString(String _deviceString);
    static String Debug(String _deviceString);
    //////////////////////////////////
    String GetName();
    String GetType();
    String GetStringValue();
    String GetValueToString();
    String GetPreviousValueToString();
    String GetPreviousStringValue();
    double GetDoubleValue();
    double GetPreviousDoubleValue();
    /////////////////////////////////
    void SetType(String _type);
    void SetName(String _name);
    void SetValue(String _value);
    void SetValue(double _value);
    /////////////////////////////////
    void ToggleState();
    /////////////////////////////////
    void AttatchToPin(int _pin);
    void DoPinCommand();
    /////////////////////////////////
    bool IsValueNumber();
    void ConfigValueType(String _value);
    /////////////////////////////////
    String ToString();
    //////////////////////////////////
    bool operator == (ControlliumDevice dev);
    bool operator != (ControlliumDevice dev);


    /////////////////////////////////////////////////
    String getValue(String data, char separator, int index);
    String GetValueFromRaw(int index);

};

#endif
