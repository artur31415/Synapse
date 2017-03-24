#include "DaedalusBiceps.h"

DaedalusBiceps::DaedalusBiceps(int rx, int tx, int baudRate)
{
  //BTSerial.SetSerial(rx, tx);

  str = "";
  LastStr = "";
  BeginMsg = "{";
  EndMsg = "}";



  /////////////////////////////////////////////////////
  BTSerial.SetSerial(rx, tx);
  BTSerial.begin(9600);
  BTSerial.listen();
}

bool DaedalusBiceps::NewValues()
{
  return IsNewData;
}

void DaedalusBiceps::BTListen()
{
  BTSerial.listen();
}
///////////////////////////////////////UI_MASTER_FUNCTIONS/////////////////////////////////////////////
int DaedalusBiceps::GetActuatorValue(int index)
{
  if(IsNewData == true)
    IsNewData = false;


  return actuators[index];
}

void DaedalusBiceps::SetNumberOfActuators(int size)
{
  actuatorsSize = size;

  if (actuators != 0)
  {
      delete [] actuators;
  }
  actuators = new int [actuatorsSize];

  for(int i = 0; i < actuatorsSize; ++i)
  {
    actuators[i] = 0;
  }
}
///////////////////////////////////////UPDATE_LOOP/////////////////////////////////////////////
void DaedalusBiceps::updateLoop()
{
  if(BTSerial.available() > 0)
  {
    char c = BTSerial.read();
    //str = BTSerial.readString();
    str = String(str + c);

    if(DecryptMsg(str))
    {
      IsNewData = true;
      LastStr = str;
      str = "";
    }
  }
}

//void AndroidShield::AndroidShieldInit()
//{
//}
///////////////////////////////////////PROTOCOL/////////////////////////////////////////////
bool DaedalusBiceps::DecryptMsg(String in)
{
  //PROTOCOL:
  //[ + BUTTONS_STATE + #E + BAR_VALUES + ]
  if(in.indexOf("{") >= 0 && in.indexOf("}") > in.indexOf("{"))
  {
    String actuatorIndex, actuatorValue;

    in = in.substring(in.lastIndexOf("{") + 1, in.indexOf("}"));
    actuatorIndex = in.substring(0, in.indexOf(";"));
    actuatorValue = in.substring(in.indexOf(";") + 1, in.length());

    int _index = actuatorIndex.toInt();
    int _value = actuatorValue.toInt();

    if(_index >= 0 && _index < actuatorsSize)
    {
      actuators[_index] = _value;
      return true;
    }
  }

  return false;
}
