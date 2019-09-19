#include <ClientManager.h>

ClientManager::ClientManager(IProtocol *protocol) : _protocol(protocol)
{
}

bool ClientManager::Connect(const QString& hostName, const quint16& port)
{
    return _protocol->Connect(hostName, port);
}

void ClientManager::SendCommand(const QString& command)
{
    _protocol->SendCommand(command);
}

QString ClientManager::SendRequest(const QString& request)
{
    return _protocol->SendRequest(request);
}

ClientManager::~ClientManager()
{
    delete _protocol;
}
