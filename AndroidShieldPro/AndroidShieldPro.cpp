#include "AndroidShieldPro.h"

AndroidShieldPro::AndroidShieldPro(int rx, int tx)
{
  //BTSerial.SetSerial(rx, tx);

  str = "";
  BeginMsg = "[";
  EndMsg = "]";

  for(int i = 0; i < NUM_OF_BUTTONS; ++i)
  {
    LedsState[i] = false;
    ButtonsState[i] = false;

    AttachedButtons[i] = -1;
  }

  LcdString = "";
  for(int i = 0; i < 9; ++i)
    LcdLines[i] = "";
    
  ActualLine = 0;

  for(int i = 0; i < NUM_OF_PROGRESSBAR; ++i)
  {
    ProgressbarVal[i] = 0;
    ScrollbarVal[i] = 0;

    AttachedScrollbars[i] = -1;
  }
  
  AccVal[0] = 0;
  AccVal[1] = 0;
  AccVal[2] = 0;
  
  ShakeState = 0;

  
  IsConnectionOn = false;


  LedStatusPin = 13;
  /////////////////////////////////////////////////////
  BTSerial.SetSerial(rx, tx);
  BTSerial.begin(9600);
  BTSerial.listen();
  pinMode(LedStatusPin, OUTPUT);

  
}

void AndroidShieldPro::listen()
{
	BTSerial.listen();
}

bool AndroidShieldPro::isConnected()
{
  return IsConnectionOn;
}
//#############################################################//
///////////////////////////////////////UI_MASTER_FUNCTIONS/////////////////////////////////////////////
//#############################################################//
void AndroidShieldPro::resetUI()
{
  //Reset the leds
  AndroidShieldPro::ledsReset();
  //Reset the progressbars
  AndroidShieldPro::progressbarsReset();
  //Reset the lcd screen
  AndroidShieldPro::BTLcdClear(-1);
}

void AndroidShieldPro::detachAll()
{
  //Detach buttons
  AndroidShieldPro::buttonDetach();
  //Reset the progressbars
  AndroidShieldPro::scrollbarDetach();
}
//#################################################//
///////////////////////////////////////LEDS/////////////////////////////////////////////
//################################################//
void AndroidShieldPro::ledWrite(int LedIndex, bool LedState)
{
  if(LedIndex >=0 && LedIndex < NUM_OF_LEDS)
    LedsState[LedIndex] = LedState;
}

bool AndroidShieldPro::ledRead(int LedIndex)
{
  if(LedIndex >=0 && LedIndex < NUM_OF_LEDS)
    return LedsState[LedIndex];
  else
    return false;
}

void AndroidShieldPro::ledToggle(int LedIndex)
{
  if(LedIndex >=0 && LedIndex < NUM_OF_LEDS)
    LedsState[LedIndex] = !LedsState[LedIndex];
}

void AndroidShieldPro::ledsWrite(bool LedState0, bool LedState1, bool LedState2, bool LedState3, bool LedState4)
{
  LedsState[0] = LedState0;
  LedsState[1] = LedState1;
  LedsState[2] = LedState2;
  LedsState[3] = LedState3;
  LedsState[4] = LedState4;
}

void AndroidShieldPro::ledsReset()
{
  for(int i = 0; i < 5; ++i)
  {
    LedsState[i] = false;
  }
}
//###################################################/
///////////////////////////////////////BUTTONS/////////////////////////////////////////////
//##################################################//
bool AndroidShieldPro::buttonRead(int ButtonIndex)
{
  if(ButtonIndex >=0 && ButtonIndex < NUM_OF_BUTTONS)
    return ButtonsState[ButtonIndex];
  else
    return false;
}

void AndroidShieldPro::buttonAttach(int ButtonIndex, int DigitalPin)
{
  if(ButtonIndex >=0 && ButtonIndex < NUM_OF_BUTTONS)
  {
    pinMode(DigitalPin, OUTPUT);
    AttachedButtons[ButtonIndex] = DigitalPin;
  }
}

void AndroidShieldPro::buttonDetach(int ButtonIndex)
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
//#####################################################//
///////////////////////////////////////SCROLLBARS/////////////////////////////////////////////
//#####################################################//
int AndroidShieldPro::scrollbarRead(int ScrollbarIndex)
{
  if(ScrollbarIndex >=0 && ScrollbarIndex < NUM_OF_SCROLLBARS)
    return ScrollbarVal[ScrollbarIndex];
  else
    return -1;
}

void AndroidShieldPro::scrollbarAttach(int ScrollbarIndex, int PwmPin)
{
  if(ScrollbarIndex >=0 && ScrollbarIndex < NUM_OF_SCROLLBARS)
  {
    AttachedScrollbars[ScrollbarIndex] = PwmPin;
  }
}

void AndroidShieldPro::scrollbarDetach(int ScrollbarIndex)
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
//#######################################################//
///////////////////////////////////////PROGRESSBAR/////////////////////////////////////////////
//#######################################################//
int AndroidShieldPro::progressbarRead(int ProgressbarIndex)
{
  if(ProgressbarIndex >=0 && ProgressbarIndex < NUM_OF_PROGRESSBAR)
    return ProgressbarVal[ProgressbarIndex];
  else
    return -1;
}

void AndroidShieldPro::progressbarWrite(int ProgressbarIndex, int _ProgressbarVal)
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

void AndroidShieldPro::progressbarsWrite(int _ProgressbarVal0, int _ProgressbarVal1, int _ProgressbarVal2, int _ProgressbarVal3)
{
	progressbarWrite(0, _ProgressbarVal0);
	progressbarWrite(1, _ProgressbarVal1);
	progressbarWrite(2, _ProgressbarVal2);
	progressbarWrite(3, _ProgressbarVal3);
}

void AndroidShieldPro::progressbarsReset()
{
  for(int i = 0; i < NUM_OF_PROGRESSBAR; ++i)
  {
    ProgressbarVal[i] = 0;
  }
}
//################################################//
///////////////////////////////////////ACC/////////////////////////////////////////////
//################################################//
float AndroidShieldPro::AccReadX()
{
	return AccVal[0];
}

float AndroidShieldPro::AccReadY()
{
	return AccVal[1];
}

float AndroidShieldPro::AccReadZ()
{
	return AccVal[2];
}

bool AndroidShieldPro::AccShake()
{
	if(ShakeState == 1)
		return true;
	else 
		return false;
}
//################################################//
///////////////////////////////////////LCD/////////////////////////////////////////////
//################################################//
void AndroidShieldPro::BTLcdGoTo(int lineIndex)
{
  if(lineIndex >= 0 && lineIndex < LCD_LINES)
    ActualLine = lineIndex;
}

void AndroidShieldPro::BTLcdPrint(String aString)
{
  if(aString.length() > LCD_CHARACTERS)
  {
    aString = aString.substring(0, LCD_CHARACTERS);
  }

  LcdLines[ActualLine] = aString;
}

void AndroidShieldPro::BTLcdClear(int lineIndex)
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
//######################################################//
///////////////////////////////////////UPDATE_LOOP/////////////////////////////////////////////
//######################################################//
void AndroidShieldPro::updateLoop(int delayTime)
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

//void AndroidShieldPro::AndroidShieldProInit()
//{
//}
//####################################################//
///////////////////////////////////////PROTOCOL/////////////////////////////////////////////
//###################################################//
bool AndroidShieldPro::DecryptMsg(String in)
{
  //PROTOCOL:
  //[ + BUTTONS_STATE + #E + BAR_VALUES + #F + ACC_DATA + ]
  if(in.indexOf("[") >= 0 && in.indexOf("]") > 0)
  {
    String buttonsString, scrollsString, accString;
    int indexPos = 0;
    in = in.substring(in.indexOf("[") + 1, in.indexOf("]"));
    buttonsString = in.substring(0, in.indexOf("#E"));
    scrollsString = in.substring(in.indexOf("#E") + 2, in.indexOf("#F"));
	accString = in.substring(in.indexOf("#F") + 2, in.length());
	
	debugStr = accString;


    for(int i = 0; i < NUM_OF_BUTTONS; ++i)
    {
      ButtonsState[i] = buttonsString.substring(0, buttonsString.indexOf(";")).toInt();
      indexPos = buttonsString.indexOf(";");
      buttonsString = buttonsString.substring(indexPos + 1, buttonsString.length());

      if(AttachedButtons[i] != -1)
      {
        digitalWrite(AttachedButtons[i], ButtonsState[i]);
      }
    }

    for(int i = 0; i < NUM_OF_PROGRESSBAR; ++i)
    {
      ScrollbarVal[i] = scrollsString.substring(0, scrollsString.indexOf(";")).toInt();
      indexPos = scrollsString.indexOf(";");
      scrollsString = scrollsString.substring(indexPos + 1, scrollsString.length());

      if(AttachedScrollbars[i] != -1)
      {
        analogWrite(AttachedScrollbars[i], ScrollbarVal[i]);
      }
    }
	
	for(int i = 0; i < 4; ++i)
    {
		if(i < 3)
		{
			AccVal[i] = accString.substring(0, accString.indexOf(";")).toFloat();	
		}
		else
		{
			ShakeState = accString.substring(0, accString.indexOf(";")).toInt();
		}
		
		indexPos = accString.indexOf(";");
		accString = accString.substring(indexPos + 1, accString.length());
    }
  }
  else
    return false;
}

String AndroidShieldPro::ProtocolMsg()
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
  
  for(int i = 0; i < NUM_OF_LEDS; ++i)
  {
    OutString += LedsState[i];   
	if(i < NUM_OF_LEDS - 1)
      OutString += ";";
    else
      OutString += "#E";
  }

  for(int i = 0; i < NUM_OF_SCROLLBARS; ++i)
  {
    OutString += ProgressbarVal[i];
    if(i < NUM_OF_SCROLLBARS - 1)
      OutString += ";";
  }

  OutString += EndMsg;

  return OutString;
}
