/*************************************************************************************************************************
    DEVELOPED BY:   ARTUR FERREIRA MOREIRA
    DATE:           MARCH, 28 OF 2017
    EMAIL:          artur31415926@gmail.com
    WEBPAGE:        http://asgardlab.netne.net/
    INSTAGRAM:      https://www.instagram.com/artur31415/
    GOOGLEPLAY:     https://play.google.com/store/apps/developer?id=Synapse
    YOUTUBE:        https://www.youtube.com/channel/UC6blOB30re0J-Oiksqaob1g/videos
**************************************************************************************************************************/


#ifndef Controllium_h
#define Controllium_h

#include "ControlliumDevice.h"
#include "ControlliumClient.h"


#define UDP_DEFAULT_PORT 2390

class Controllium
{
  private:
    String name;
    ControlliumDevice *myDevices;
    int ElementsCount;

    WiFiUDP UdpPort;

    ControlliumClient *myClients;
    int ClientsCount;

  public:
    String LastReceived;
    String LastSended;
    Controllium();
    Controllium(String _name);

    ~Controllium();
    //////////////////////////////////////////////
    void AddDevice(ControlliumDevice dev);
    void RemoveDevice(ControlliumDevice dev);
    void ClearDevices();
    bool HasDevice(ControlliumDevice dev);
    void SetDevice(int index, ControlliumDevice dev);
    ControlliumDevice * GetDevice(int index);
	ControlliumDevice * GetDevice(String _name);
    int NumberOfDevices();
    int NumberOfDevicesByType(String _type);
    int GetDeviceIndexByName(String _name);

    int NumberOfDevicesToSend();
    //////////////////////////////////////////////
    void AddClient(ControlliumClient client);
    void RemoveClient(ControlliumClient client);
    void ClearClients();
    bool HasClient(ControlliumClient client);
    void SetClient(int index, ControlliumClient client);
    ControlliumClient * GetClient(int index);
    ControlliumClient * GetClientByIP(IPAddress _clientIP);
    int NumberOfClients();
    int GetClientIndexByIP(IPAddress _clientIP);

    //////////////////////////////////////////////
    bool Update(int updateDelay);
    void BeginUdpServer(unsigned int _port);
    //////////////////////////////////////////////
    void ProtocolDecrypt(IPAddress RemoteIp, char _UdpPacketBuffer[255]);
    char* ProtocolEncrypt();




};

#endif
