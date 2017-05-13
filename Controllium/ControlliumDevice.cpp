#include "ControlliumDevice.h"

bool ControlliumDevice::operator == (ControlliumDevice dev)
{
  if(name == dev.GetName())
    return true;
  else return false;
}

bool ControlliumDevice::operator != (ControlliumDevice dev)
{
  if(name != dev.GetName())
    return true;
  else return false;
}

ControlliumDevice::ControlliumDevice()
{
  name = UNDEFINED_FIELD;
  type = UNDEFINED_FIELD;

  valueStr = "";
  PreviousValueStr = "";

  valueDouble = -1;
  PreviousValueDouble = -1;

  isValueNumber = false;
}

ControlliumDevice::ControlliumDevice(String _name)
{
  name = _name;

  type = UNDEFINED_FIELD;

  valueStr = "";
  PreviousValueStr = "";

  valueDouble = -1;
  PreviousValueDouble = -1;

  isValueNumber = false;
}

ControlliumDevice::ControlliumDevice(String _name, String _type)
{
  name = _name;

  type = _type;

  valueStr = "";
  PreviousValueStr = "";

  valueDouble = -1;
  PreviousValueDouble = -1;

  isValueNumber = false;
}

ControlliumDevice::ControlliumDevice(String _name, String _type, String _value)
{
  name = _name;

  type = _type;

  valueStr = "";
  PreviousValueStr = "";

  valueDouble = -1;
  PreviousValueDouble = -1;

  isValueNumber = false;

  if((_type.indexOf(DEVICE_TYPE_LABEL) >= 0) || (_type.indexOf(DEVICE_TYPE_ACCELEROMETER) >= 0) || (_type.indexOf(DEVICE_TYPE_GPS) >= 0) || (_type.indexOf(DEVICE_TYPE_TEXT_INPUT) >= 0))
	  valueStr = _value;
  else
    ConfigValueType(_value);
}



ControlliumDevice::~ControlliumDevice()
{
}

String ControlliumDevice::Debug(String _deviceString)
{
  String _type, _name, _value, temp, out;

  _type = _deviceString.substring(0, _deviceString.indexOf("|"));

  temp = _deviceString.substring(_deviceString.indexOf("|") + 1, _deviceString.length());
  _name = temp.substring(0, temp.indexOf("|"));

  temp = temp.substring(temp.indexOf("|") + 1, temp.length());
  _value = temp.substring(0, temp.indexOf("|"));

  out = "NAME=[" + _name + "]; TYPE=[" + _type + "]; VALUE = [" + _value + "]";

  ControlliumDevice newDev;
  out += "newDevName = " + newDev.GetName() + "; ";
  newDev.SetName(_name);
  out += "newDevName = " + newDev.GetName() + "; ";

  return out;
}

ControlliumDevice ControlliumDevice::FromString(String _deviceString)
{
  String _type, _name, _value, temp;

  _type = _deviceString.substring(0, _deviceString.indexOf("|"));

  temp = _deviceString.substring(_deviceString.indexOf("|") + 1, _deviceString.length());
  _name = temp.substring(0, temp.indexOf("|"));

  temp = temp.substring(temp.indexOf("|") + 1, temp.length());
  _value = temp.substring(0, temp.indexOf("|"));

  return ControlliumDevice(_name, _type, _value);
}

void ControlliumDevice::SetFromString(String _deviceString)//_deviceString = "TYPE|NAME|VALUE"
{
  String _type, _name, _value, temp;

  _type = _deviceString.substring(0, _deviceString.indexOf("|"));

  temp = _deviceString.substring(_deviceString.indexOf("|") + 1, _deviceString.length());
  _name = temp.substring(0, temp.indexOf("|"));

  temp = temp.substring(temp.indexOf("|") + 1, temp.length());
  _value = temp.substring(0, temp.indexOf("|"));
  ///////////////////////////////////////////////
  name = _name;
  type = _type;

  valueStr = "";
  PreviousValueStr = "";

  valueDouble = -1;
  PreviousValueDouble = -1;

  isValueNumber = false;

  ConfigValueType(_value);

  ////////////////
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//                                      GET FUNCTIONS                                           //
//////////////////////////////////////////////////////////////////////////////////////////////////
String ControlliumDevice::GetName()
{
  return name;
}

String ControlliumDevice::GetType()
{
  return type;
}

String ControlliumDevice::GetStringValue()
{
  if(isValueNumber)
    return UNDEFINED_FIELD;
  else
    return valueStr;
}

String ControlliumDevice::GetPreviousStringValue()
{
  if(isValueNumber)
    return UNDEFINED_FIELD;
  else
    return PreviousValueStr;
}

String ControlliumDevice::GetValueToString()
{
  //[  0.00]
  if(isValueNumber)
  {
    char floatV0[10];
    dtostrf((float)valueDouble, 3, 2, floatV0);
    String convertedValue(floatV0);
    return convertedValue;
  }
  else
    return valueStr;
}

String ControlliumDevice::GetPreviousValueToString()
{
  if(isValueNumber)
  {
    char floatV0[10];
    dtostrf((float)PreviousValueDouble, 3, 2, floatV0);
    String convertedValue(floatV0);
    return convertedValue;
  }
  else
    return PreviousValueStr;
}

double ControlliumDevice::GetDoubleValue()
{
  if(!isValueNumber)
    return -1;
  else
    return valueDouble;
}

double ControlliumDevice::GetPreviousDoubleValue()
{
  if(!isValueNumber)
    return -1;
  else
    return PreviousValueDouble;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//                                      SET FUNCTIONS                                           //
//////////////////////////////////////////////////////////////////////////////////////////////////
void ControlliumDevice::SetType(String _type)
{
  type = _type;
}

void ControlliumDevice::SetName(String _name)
{
  name = _name;
}

void ControlliumDevice::SetValue(String _value)
{
  PreviousValueStr = valueStr;
  valueStr = _value;
}

void ControlliumDevice::SetValue(double _value)
{
  PreviousValueDouble = valueDouble;
  valueDouble = _value;
}

void ControlliumDevice::ToggleState()
{
  if(isValueNumber == true)
  {
    if(valueDouble == 0)
      valueDouble = 1;
    else
      valueDouble = 0;
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//                                    UTILITY FUNCTIONS                                         //
//////////////////////////////////////////////////////////////////////////////////////////////////
void ControlliumDevice::ConfigValueType(String _value)
{
  PreviousValueStr = _value;
  if(_value.indexOf(" ") >= 0)//string has space
  {
    isValueNumber = false;
  }
  else if(_value.toFloat() == 0)
  {
    if(_value.indexOf("0") >= 0 || _value.indexOf("0.0") >= 0 || _value.indexOf("0.00") >= 0)
      isValueNumber = true;
    else
      isValueNumber = false;
  }
  else
  {
    isValueNumber = true;
  }

  if(isValueNumber)
  {
    valueDouble = (double)_value.toFloat();
    PreviousValueDouble = valueDouble;

    valueStr = UNDEFINED_FIELD;
    //PreviousValueStr = valueStr;
  }
  else
  {
    valueDouble = -1;
    PreviousValueDouble = -1;

    valueStr = _value;
    PreviousValueStr = valueStr;
  }
}

bool ControlliumDevice::IsValueNumber()
{
  return isValueNumber;
}

String ControlliumDevice::ToString()
{
  String out = type + PROTOCOL_SEPARATOR + name + PROTOCOL_SEPARATOR;
  if(isValueNumber)
  {
    char floatV0[10];
    dtostrf((float)valueDouble, 6, 2, floatV0);
    String convertedValue(floatV0);

    out += convertedValue;
  }
  else
  {
    out += valueStr;
  }
  return out;
}

String ControlliumDevice::getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = {0, -1};
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++)
    {
        if (data.charAt(i) == separator || i == maxIndex)
        {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

String ControlliumDevice::GetValueFromRaw(int index)
{
  return getValue(GetValueToString(), ' ', index);
}
