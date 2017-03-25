/*************************************************************************************************************************
    DEVELOPED BY:   ARTUR FERREIRA MOREIRA
    DATE:           FEBRUARY, 14 OF 2017
    EMAIL:          artur31415926@gmail.com
    WEBPAGE:        http://asgardlab.netne.net/
    INSTAGRAM:      https://www.instagram.com/artur31415/
    GOOGLEPLAY:     https://play.google.com/store/apps/developer?id=Synapse
    YOUTUBE:        https://www.youtube.com/channel/UC6blOB30re0J-Oiksqaob1g/videos
**************************************************************************************************************************/

#ifndef ControlliumClient_h
#define ControlliumClient_h

#include <WiFiUdp.h>

class ControlliumClient
{
  private:
    IPAddress myIp;


    long ClientTimeOut;
    long ClientTimeOutMax;
  public:
    String LastDataReceived;
    String LastDataSended;
    //////////////////////////////////////////////
    ControlliumClient();
    ControlliumClient(IPAddress _myIp);
    ~ControlliumClient();
    //////////////////////////////////////////////
    IPAddress GetIp();
    void SetIp(IPAddress _myIp);
    //////////////////////////////////////////////
    bool IsTimeOut();
    bool JustConnected();
    //////////////////////////////////////////////
    void IterationStep();
    long GetActualStep();
    void SetActive();
    /////////////////////////////////////////////
    //////////////////////////////////
    bool operator == (ControlliumClient client);
    bool operator != (ControlliumClient client);

};

#endif
