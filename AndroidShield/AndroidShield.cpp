#include "AndroidShield.h"

AndroidShield::AndroidShield(int rx, int tx)
{
  //BTSerial.SetSerial(rx, tx);

  str = "";
  BeginMsg = "[";
  EndMsg = "]";

  for(int i = 0; i < 5; ++i)
  {
    LedsState[i] = false;
    ButtonsState[i] = false;

    AttachedButtons[i] = -1;
  }

  LcdString = "";
  for(int i = 0; i < 9; ++i)
    LcdLines[i] = "";
    
  ActualLine = 0;

  for(int i = 0; i < 2; ++i)
  {
    ProgressbarVal[i] = 0;
    ScrollbarVal[i] = 0;

    AttachedScrollbars[i] = -1;
  }

  
  IsConnectionOn = false;


  LedStatusPin = 13;
  /////////////////////////////////////////////////////
  BTSerial.begin(9600);
  BTSerial.listen();
  pinMode(LedStatusPin, OUTPUT);

  
}

bool AndroidShield::isConnected()
{
  return IsConnectionOn;
}

///////////////////////////////////////UI_MASTER_FUNCTIONS/////////////////////////////////////////////
void AndroidShield::resetUI()
{
  //Reset the leds
  AndroidShield::ledsReset();
  //Reset the progressbars
  AndroidShield::progressbarsReset();
  //Reset the lcd screen
  AndroidShield::BTLcdClear(-1);
}

void AndroidShield::detachAll()
{
  //Detach buttons
  AndroidShield::buttonDetach();
  //Reset the progressbars
  AndroidShield::scrollbarDetach();
}
///////////////////////////////////////LEDS/////////////////////////////////////////////
void AndroidShield::ledWrite(int LedIndex, bool LedState)
{
  if(LedIndex >=0 && LedIndex < NUM_OF_LEDS)
    LedsState[LedIndex] = LedState;
}

bool AndroidShield::ledRead(int LedIndex)
{
  if(LedIndex >=0 && LedIndex < NUM_OF_LEDS)
    return LedsState[LedIndex];
  else
    return false;
}

void AndroidShield::ledToggle(int LedIndex)
{
  if(LedIndex >=0 && LedIndex < NUM_OF_LEDS)
    LedsState[LedIndex] = !LedsState[LedIndex];
}

void AndroidShield::ledsWrite(bool LedState0, bool LedState1, bool LedState2, bool LedState3, bool LedState4)
{
  LedsState[0] = LedState0;
  LedsState[1] = LedState1;
  LedsState[2] = LedState2;
  LedsState[3] = LedState3;
  LedsState[4] = LedState4;
}

void AndroidShield::ledsReset()
{
  for(int i = 0; i < 5; ++i)
  {
    LedsState[i] = false;
  }
}
///////////////////////////////////////BUTTONS/////////////////////////////////////////////
bool AndroidShield::buttonRead(int ButtonIndex)
{
  if(ButtonIndex >=0 && ButtonIndex < NUM_OF_BUTTONS)
    return ButtonsState[ButtonIndex];
  else
    return false;
}

void AndroidShield::buttonAttach(int ButtonIndex, int DigitalPin)
{
  if(ButtonIndex >=0 && ButtonIndex < NUM_OF_BUTTONS)
  {
    pinMode(DigitalPin, OUTPUT);
    AttachedButtons[ButtonIndex] = DigitalPin;
  }
}

void AndroidShield::buttonDetach(int ButtonIndex)
{
  if(ButtonIndex >=0 && ButtonIndex < NUM_OF_BUTTONS)
  {
    AttachedButtons[ButtonIndex] = -1;
  }
  else if(ButtonIndex == -1)
  {
    for(int i = 0; i < NUM_OF_BUTTONS; ++i)
    {
      AttachedButtons[i] = -1;
    }
  }
}
///////////////////////////////////////SCROLLBARS/////////////////////////////////////////////
int AndroidShield::scrollbarRead(int ScrollbarIndex)
{
  if(ScrollbarIndex >=0 && ScrollbarIndex < NUM_OF_SCROLLBARS)
    return ScrollbarVal[ScrollbarIndex];
  else
    return -1;
}

void AndroidShield::scrollbarAttach(int ScrollbarIndex, int PwmPin)
{
  if(ScrollbarIndex >=0 && ScrollbarIndex < NUM_OF_SCROLLBARS)
  {
    AttachedScrollbars[ScrollbarIndex] = PwmPin;
  }
}

void AndroidShield::scrollbarDetach(int ScrollbarIndex)
{
  if(ScrollbarIndex >=0 && ScrollbarIndex < NUM_OF_SCROLLBARS)
  {
    AttachedScrollbars[ScrollbarIndex] = -1;
  }
  else if(ScrollbarIndex == -1)
  {
    for(int i = 0; i < NUM_OF_SCROLLBARS; ++i)
    {
      AttachedScrollbars[i] = -1;
    }
  }
}
///////////////////////////////////////PROGRESSBAR/////////////////////////////////////////////
int AndroidShield::progressbarRead(int ProgressbarIndex)
{
  if(ProgressbarIndex >=0 && ProgressbarIndex < NUM_OF_PROGRESSBAR)
    return ProgressbarVal[ProgressbarIndex];
  else
    return -1;
}

void AndroidShield::progressbarWrite(int ProgressbarIndex, int _ProgressbarVal)
{
  if(ProgressbarIndex >=0 && ProgressbarIndex < NUM_OF_PROGRESSBAR)
  {
    if(_ProgressbarVal < 0)
    {
      _ProgressbarVal = 0;
    }
    else if(_ProgressbarVal > BAR_MAX_VALUE)
    {
      _ProgressbarVal = BAR_MAX_VALUE;
    }

    ProgressbarVal[ProgressbarIndex] = _ProgressbarVal;
  }
    
}

void AndroidShield::progressbarsWrite(int _ProgressbarVal0, int _ProgressbarVal1)
{
  if(_ProgressbarVal0 < 0)
  {
    _ProgressbarVal0 = 0;
  }
  else if(_ProgressbarVal0 > BAR_MAX_VALUE)
  {
    _ProgressbarVal0 = BAR_MAX_VALUE;
  }

  if(_ProgressbarVal1 < 0)
  {
    _ProgressbarVal1 = 0;
  }
  else if(_ProgressbarVal1 > BAR_MAX_VALUE)
  {
    _ProgressbarVal1 = BAR_MAX_VALUE;
  }
  

  ProgressbarVal[0] = _ProgressbarVal0;
  ProgressbarVal[1] = _ProgressbarVal1;
}

void AndroidShield::progressbarsReset()
{
  ProgressbarVal[0] = 0;
  ProgressbarVal[0] = 0;
}
///////////////////////////////////////LCD/////////////////////////////////////////////
void AndroidShield::BTLcdGoTo(int lineIndex)
{
  if(lineIndex >= 0 && lineIndex < LCD_LINES)
    ActualLine = lineIndex;
}

void AndroidShield::BTLcdPrint(String aString)
{
  if(aString.length() > LCD_CHARACTERS)
  {
    aString = aString.substring(0, LCD_CHARACTERS);
  }

  LcdLines[ActualLine] = aString;
}

void AndroidShield::BTLcdClear(int lineIndex)
{
  if(lineIndex == -1)
  {
    for(int i = 0; i < 9; ++i)
      LcdLines[i] = "";
    
    ActualLine = 0;
  }
  else if(lineIndex >= 0 && lineIndex < LCD_LINES)
  {
      LcdLines[lineIndex] = "";
  }
  
}
///////////////////////////////////////UPDATE_LOOP/////////////////////////////////////////////
void AndroidShield::updateLoop(int delayTime)
{
  if(BTSerial.available() > 0)
  {
    str = BTSerial.readString();
    if(str == "BEGIN")
    {
      IsConnectionOn = true;
      digitalWrite(LedStatusPin, HIGH);
    }
    else if(str == "END")
    {
      IsConnectionOn = false;
      digitalWrite(LedStatusPin, LOW);
    }
    else
    {
      //decrypt the msg from the serial!
      if(DecryptMsg(str))
      {
      }
    }
  }

  if(IsConnectionOn == true)
  {
    BTSerial.println(ProtocolMsg());
    
    delay(delayTime);
  }
}

//void AndroidShield::AndroidShieldInit()
//{
//}
///////////////////////////////////////PROTOCOL/////////////////////////////////////////////
bool AndroidShield::DecryptMsg(String in)
{
  //PROTOCOL:
  //[ + BUTTONS_STATE + #E + BAR_VALUES + ]
  if(in.indexOf("[") >= 0 && in.indexOf("]") > 0)
  {
    String buttonsString, scrollsString;
    int indexPos = 0;
    in = in.substring(in.indexOf("[") + 1, in.indexOf("]"));
    buttonsString = in.substring(0, in.indexOf("#E"));
    scrollsString = in.substring(in.indexOf("#E") + 2, in.length());


    for(int i = 0; i < 5; ++i)
    {
      ButtonsState[i] = buttonsString.substring(0, buttonsString.indexOf(";")).toInt();
      indexPos = buttonsString.indexOf(";");
      buttonsString = buttonsString.substring(indexPos + 1, buttonsString.length());

      if(AttachedButtons[i] != -1)
      {
        digitalWrite(AttachedButtons[i], ButtonsState[i]);
      }
    }

    for(int i = 0; i < 2; ++i)
    {
      ScrollbarVal[i] = scrollsString.substring(0, scrollsString.indexOf(";")).toInt();
      indexPos = scrollsString.indexOf(";");
      scrollsString = scrollsString.substring(indexPos + 1, scrollsString.length());

      if(AttachedScrollbars[i] != -1)
      {
        analogWrite(AttachedScrollbars[i], ScrollbarVal[i]);
      }
    }
  }
  else
    return false;
}

String AndroidShield::ProtocolMsg()
{
  String OutString = BeginMsg;
  
  LcdString = "";
  for(int i = 0; i < LCD_LINES; ++i)
  {
    LcdString += " " + LcdLines[i];
    if(i < LCD_LINES - 1)
      LcdString += "\n";
  }
  

  OutString += LcdString + "#E";
  
  for(int i = 0; i < 5; ++i)
  {
    OutString += LedsState[i];   if(i < 4)
      OutString += ";";
    else
      OutString += "#E";
  }

  for(int i = 0; i < 2; ++i)
  {
    OutString += ProgressbarVal[i];
    if(i < 1)
      OutString += ";";
  }

  OutString += EndMsg;

  return OutString;
}
