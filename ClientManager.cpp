#include <ClientManager.h>

ClientManager::ClientManager(IProtocol *protocol) : _protocol(protocol)
{

}

bool ClientManager::Connect(const QString hostName, quint16 port)
{
    return _protocol->Connect(hostName, port);
}

void ClientManager::SendCommand(QString command)
{
    _protocol->SendCommand(command);
}

QString ClientManager::SendRequest(QString request)
{
    return _protocol->SendRequest(request);
}

ClientManager::~ClientManager()
{
    delete _protocol;
}
