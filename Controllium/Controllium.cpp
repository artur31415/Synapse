#include "Controllium.h"

Controllium::Controllium()
{
  ElementsCount = 0;
  LastReceived = UNDEFINED_FIELD;

}

Controllium::Controllium(String _name)
{
  name = _name;
  ElementsCount = 0;

  LastReceived = UNDEFINED_FIELD;

}

Controllium::~Controllium()
{
  delete [] myDevices;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//                                      DECICE FUNCTIONS                                        //
//////////////////////////////////////////////////////////////////////////////////////////////////
void Controllium::AddDevice(ControlliumDevice dev)
{
    ControlliumDevice  oldDevs[ElementsCount];

  if(ElementsCount > 0)
  {
    for(int i = 0; i < ElementsCount; ++i)
    {
      oldDevs[i] = myDevices[i];
    }
  }

    myDevices = new ControlliumDevice[ElementsCount + 1];

  if(ElementsCount > 0)
  {
    for(int i = 0; i < ElementsCount; ++i)
    {
      myDevices[i] = oldDevs[i];
    }
  }


  myDevices[ElementsCount] = dev;
  ++ElementsCount;

  //delete [] oldDevs;
}

void Controllium::SetDevice(int index, ControlliumDevice dev)
{
  if(index >= ElementsCount)
    return;

  myDevices[index] = dev;
}

bool Controllium::HasDevice(ControlliumDevice dev)
{
  for(int i = 0; i < ElementsCount; ++i)
  {
    if(myDevices[i] == dev)
    {
      return true;
    }
  }
  return false;
}

void Controllium::RemoveDevice(ControlliumDevice dev)
{
  if(!HasDevice(dev) || ElementsCount > 0)
    return;

  ControlliumDevice oldDevs[ElementsCount];
  int newIndex = 0, oldIndex = 0;

  for(int i = 0; i < ElementsCount; ++i)
  {
    oldDevs[i] = myDevices[i];
  }

  myDevices = new ControlliumDevice[ElementsCount - 1];

  while(oldIndex < ElementsCount)
  {
    if(oldDevs[oldIndex] != dev)
    {
      myDevices[newIndex] = oldDevs[oldIndex];
      ++newIndex;
    }
    ++oldIndex;
  }

  --ElementsCount;
}

void Controllium::ClearDevices()
{
  myDevices = new ControlliumDevice[ElementsCount];
}

ControlliumDevice * Controllium::GetDevice(int index)
{
  // ControlliumDevice* dev = new ControlliumDevice();
  // *dev = myDevices[index];
  return &myDevices[index];
}

int Controllium::NumberOfDevices()
{
  return ElementsCount;
}

int Controllium::NumberOfDevicesToSend()
{

}

int Controllium::NumberOfDevicesByType(String _type)
{
  int NumOf = 0;
  for(int i = 0; i < NumberOfDevices(); ++i)
  {
    if(GetDevice(i)->GetType().indexOf(_type) >= 0)
      ++NumOf;
  }
  return NumOf;
}

int Controllium::GetDeviceIndexByName(String _devName)
{
  if(ElementsCount == 0)
    return -1;

  for(int i = 0; i < ElementsCount; ++i)
  {
    if(myDevices[i].GetName() == _devName)
      return i;
  }

  return -1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//                                      CLIENT FUNCTIONS                                        //
//////////////////////////////////////////////////////////////////////////////////////////////////
void Controllium::AddClient(ControlliumClient client)
{
    ControlliumClient  oldClients[ClientsCount];

  if(ClientsCount > 0)
  {
    for(int i = 0; i < ClientsCount; ++i)
    {
      oldClients[i] = myClients[i];
    }
  }

    myClients = new ControlliumClient[ClientsCount + 1];

  if(ClientsCount > 0)
  {
    for(int i = 0; i < ClientsCount; ++i)
    {
      myClients[i] = oldClients[i];
    }
  }


  myClients[ClientsCount] = client;
  ++ClientsCount;
}

void Controllium::SetClient(int index, ControlliumClient client)
{
  if(index >= ClientsCount)
    return;

  myClients[index] = client;
}

bool Controllium::HasClient(ControlliumClient client)
{
  for(int i = 0; i < ClientsCount; ++i)
  {
    if(myClients[i] == client)
    {
      return true;
    }
  }
  return false;
}

void Controllium::RemoveClient(ControlliumClient client)
{
  if(!HasClient(client) || ClientsCount > 0)
    return;

  ControlliumClient oldClients[ClientsCount];
  int newIndex = 0, oldIndex = 0;

  for(int i = 0; i < ClientsCount; ++i)
  {
    oldClients[i] = myClients[i];
  }

  myClients = new ControlliumClient[ClientsCount - 1];

  while(oldIndex < ClientsCount)
  {
    if(oldClients[oldIndex] != client)
    {
      myClients[newIndex] = oldClients[oldIndex];
      ++newIndex;
    }
    ++oldIndex;
  }

  --ClientsCount;
}

void Controllium::ClearClients()
{
  ClientsCount = 0;
  myClients = new ControlliumClient[ClientsCount];
}

ControlliumClient * Controllium::GetClient(int index)
{
  // ControlliumDevice* dev = new ControlliumDevice();
  // *dev = myDevices[index];
  return &myClients[index];
}

ControlliumClient * Controllium::GetClientByIP(IPAddress _clientIP)
{
  return GetClient(GetClientIndexByIP(_clientIP));
}

int Controllium::NumberOfClients()
{
  return ClientsCount;
}

int Controllium::GetClientIndexByIP(IPAddress _clientIP)
{
  if(ClientsCount == 0)
    return -1;

  for(int i = 0; i < ClientsCount; ++i)
  {
    if(myClients[i].GetIp() == _clientIP)
      return i;
  }

  return -1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//                                    MAIN UPDATE FUNCTION                                      //
//////////////////////////////////////////////////////////////////////////////////////////////////
bool Controllium::Update(int updateDelay)
{

  //---------------------------------------------------
  //                    RECEIVE DATA
  //---------------------------------------------------
  bool isNewData = false;
  int packetSize = UdpPort.parsePacket();

  if (packetSize)
  {
    isNewData = true;
    char UdpPacketBuffer[255];
    int PacketLength = UdpPort.read(UdpPacketBuffer, 255);
    if(PacketLength > 0)
      UdpPacketBuffer[PacketLength - 1] = 0;


    ProtocolDecrypt(UdpPort.remoteIP(), UdpPacketBuffer);

  }

  //---------------------------------------------------
  //          SEND DATA TO KNOW (AND ALIVE!) CLIENTS
  //---------------------------------------------------
  if(ClientsCount > 0 && NumberOfDevicesByType(DEVICE_TYPE_LED) > 0)
  {
    char* dataString = ProtocolEncrypt();
    String strToSend(dataString);
    LastSended = strToSend;

    for(int i = 0; i < ClientsCount; ++i)
    {

      if(!GetClient(i)->IsTimeOut())//THEN CLIENT IS STILL ALIVE
      {
        UdpPort.beginPacket(GetClient(i)->GetIp(), UdpPort.localPort());

        // if(GetClient(i)->JustConnected())
        // {
        //   UdpPort.write("CONNECTEDN");
        // }
        // else
        // {
        //   UdpPort.write(dataString);
        // }
        UdpPort.write(dataString);
        UdpPort.endPacket();
        GetClient(i)->IterationStep();
      }


    }
  }

  delay(updateDelay);

  return isNewData;
}

void Controllium::BeginUdpServer(unsigned int _port)
{
  UdpPort.begin(_port);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//                                     PROTOCOL FUNCTIONS                                       //
//////////////////////////////////////////////////////////////////////////////////////////////////
void Controllium::ProtocolDecrypt(IPAddress RemoteIp, char _UdpPacketBuffer[255])
{
  String data(_UdpPacketBuffer);
  LastReceived = data;

  if(data.indexOf("SCAN") >= 0)//SCAN EVENT
  {
    LastSended = "SCAN_TRUEN";
    UdpPort.beginPacket(RemoteIp, UdpPort.localPort());
    UdpPort.write("SCAN_TRUEN");
    UdpPort.endPacket();
  }
  else if(data.indexOf("BEGIN") >= 0)//THIS IS A NEW CLIENT!
  {
    if(GetClientIndexByIP(RemoteIp) < 0)
    {
      ControlliumClient client(RemoteIp);
      client.LastDataReceived = data;
      AddClient(client);
    }
    else//THIS CLIENT ALLREADY IS ON THE LIST
    {
      GetClientByIP(RemoteIp)->SetActive();//IT IS BACK TO ACTIVITY
    }
  }
  else if(data.indexOf("[") >= 0 && data.indexOf("]") >= 0)//NEW DATA PACKET FROM THE APP
  {
    String temp = data.substring(data.indexOf("[") + 1, data.lastIndexOf("]"));
    GetClientByIP(RemoteIp)->LastDataReceived = temp;
    GetClientByIP(RemoteIp)->SetActive();//IT IS BACK TO ACTIVITY

    if(temp.indexOf("|") < 0)//NO VALID DATA TO PROCESS!
      return;

    //DO SOMETHING WITH THE DATA!
    if(temp.indexOf(",") >= 0)//THEN THERE IS MORE THAN ONE OBJECT TO PROCESS
    {
      String devicesString = temp;
      bool isNext = false;
      for(int i = 0; ; ++i)
      {
        String temp2 = devicesString.substring(0, devicesString.indexOf(","));
        temp2 = temp2.substring(temp2.indexOf("[") + 1, temp2.indexOf("]"));

        ControlliumDevice receivedDev = ControlliumDevice::FromString(temp2);
        int receivedIndex = GetDeviceIndexByName(receivedDev.GetName());
        if(receivedIndex >= 0)//KNOWN DEVICE RECEIVED!
        {
          GetDevice(receivedIndex)->ConfigValueType(receivedDev.GetValueToString());
        }

        devicesString = devicesString.substring(devicesString.indexOf(",") + 1, devicesString.length());

        if(isNext)
          break;

        if(devicesString.indexOf(",") < 0)
        {
          isNext = true;
        }

      }
    }
    else
    {
      ControlliumDevice receivedDev = ControlliumDevice::FromString(temp);
      int receivedIndex = GetDeviceIndexByName(receivedDev.GetName());
      if(receivedIndex >= 0)//KNOWN DEVICE RECEIVED!
      {
        GetDevice(receivedIndex)->ConfigValueType(receivedDev.GetValueToString());
      }
    }

  }
}

char* Controllium::ProtocolEncrypt()
{
  int numOfLeds = NumberOfDevicesByType(DEVICE_TYPE_LED);
  String outStr = "[";

  for(int i = 0; i < numOfLeds; ++i)
  {
    if(GetDevice(i)->GetType().indexOf(DEVICE_TYPE_LED) >= 0)
    {
      outStr += "[" +  GetDevice(i)->ToString() + "]";
      if(i < numOfLeds - 1)
        outStr += ",";
    }
  }
  outStr += "]N";

  char* outData = new char[outStr.length()];
  outStr.toCharArray(outData, outStr.length());

  return outData;
}
