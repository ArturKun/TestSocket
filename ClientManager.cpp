#include <ClientManager.h>


ClientManager::ClientManager(IProtocol *protocol)
{
    //TODO: правильно использую указатели ссылки?
    _protocol = protocol;
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
