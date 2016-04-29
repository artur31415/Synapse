/*************************************************************************************************************************
    DEVELOPED BY:   ARTUR FERREIRA MOREIRA
    DATE:           APRIL, 18 OF 2016
    EMAIL:          artur31415926@gmail.com
    WEBPAGE:        asgardlab.netne.net/Synapse
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
[ENG-USA]
    AndroidShield is a library developed to be used with the android app "Android Shield Arduino"
    that can be found on the store.
    
    If you download and are using the app, thanks for the preference.
    For feature requests, any criticism or ideas, mail me or visit my webpage.

[PT-BR]
    AndroidShield é uma biblioteca desenvolvida para ser usada com o aplicativo android "Android Shield Arduino"
    que pode ser encontrado na store.
    
    Se você baixou e esta usando o aplicativo, obrigado pela preferencia.
    Para pedir funções a mais no app, qualquer critica ou ideias, me mande um email ou visite minha webpage.
**************************************************************************************************************************/


#ifndef AndroidShield_h
#define AndroidShield_h

#include "SoftwareSerial.h"
#include "Arduino.h"

#define LCD_LINES  9
#define LCD_CHARACTERS  41
#define NUM_OF_LEDS  5
#define NUM_OF_BUTTONS  5
#define NUM_OF_SCROLLBARS  2
#define NUM_OF_PROGRESSBAR  2
#define BAR_MAX_VALUE  255

class AndroidShield
{
  private:

  SoftwareSerial BTSerial;

  String str;
  String BeginMsg;
  String EndMsg;
  
  bool LedsState[5];
  bool ButtonsState[5];
  String LcdString;
  String LcdLines[9];
  int ActualLine;
  int ProgressbarVal[2];
  int ScrollbarVal[2];
  
  bool IsConnectionOn;

  int LedStatusPin;

  int AttachedButtons[5];
  int AttachedScrollbars[2];

  public:
    AndroidShield(int rx, int tx);

    //Master UI Methods
    void resetUI();
    void detachAll();
    
    //Leds Methods
    void ledWrite(int LedIndex, bool LedState);
    bool ledRead(int LedIndex);
    void ledToggle(int LedIndex);
    void ledsWrite(bool LedState0, bool LedState1, bool LedState2, bool LedState3, bool LedState4);
    void ledsReset();
    
    //Buttons Methods
    bool buttonRead(int ButtonIndex);
    void buttonAttach(int ButtonIndex, int DigitalPin);
    void buttonDetach(int ButtonIndex = -1);
    
    //Scrollbars Methods
    int scrollbarRead(int ScrollbarIndex);
    void scrollbarAttach(int ScrollbarIndex, int PwmPin);
    void scrollbarDetach(int ScrollbarIndex = -1);
    
    //Progressbars Methos
    int progressbarRead(int ProgressbarIndex);
    void progressbarWrite(int ProgressbarIndex, int _ProgressbarVal);
    void progressbarsWrite(int _ProgressbarVal0, int _ProgressbarVal1);
    void progressbarsReset();
    
    //Lcd Methods
    void BTLcdGoTo(int lineIndex);
    void BTLcdPrint(String aString);
    void BTLcdClear(int lineIndex = -1);

    //Update Loop Method
    void updateLoop(int delayTime);

    //Protocol Methods
    bool DecryptMsg(String in);
    String ProtocolMsg();
    bool isConnected();
};

#endif
