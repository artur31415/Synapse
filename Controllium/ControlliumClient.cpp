#include "ControlliumClient.h"

bool ControlliumClient::operator == (ControlliumClient client)
{
  if(myIp == client.GetIp())
    return true;
  else
    return false;
}

bool ControlliumClient::operator != (ControlliumClient client)
{
  if(myIp != client.GetIp())
    return true;
  else
    return false;
}
///////////////////////////////////////////////////
ControlliumClient::ControlliumClient()
{
  ClientTimeOut = 0;
  ClientTimeOutMax = 1000;

  LastDataReceived = "";
  String LastDataSended = "";
}

ControlliumClient::ControlliumClient(IPAddress _myIp)
{
  ClientTimeOut = 0;
  ClientTimeOutMax = 1000;

  myIp = _myIp;

  LastDataReceived = "";
  String LastDataSended = "";
}

ControlliumClient::~ControlliumClient()
{

}
//////////////////////////////////////////////
IPAddress ControlliumClient::GetIp()
{
  return myIp;
}

void ControlliumClient::SetIp(IPAddress _myIp)
{
  myIp = _myIp;
}
//////////////////////////////////////////////
bool ControlliumClient::IsTimeOut()
{
  if(ClientTimeOut > ClientTimeOutMax)
    return true;
  else
    return false;
}

bool ControlliumClient::JustConnected()
{
  if(ClientTimeOut == 0)
    return true;
  else
    return false;
}

void ControlliumClient::IterationStep()
{
  ++ClientTimeOut;
}

long ControlliumClient::GetActualStep()
{
  return ClientTimeOut;
}

void ControlliumClient::SetActive()
{
  ClientTimeOut = 0;
}
