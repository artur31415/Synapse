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
