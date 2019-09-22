#include <ClientManager.h>

//Конструктор принимающий протокол,
//по которому будет происходить соединение
ClientManager::ClientManager(IProtocol *protocol) : _protocol(protocol)
{
}

//Установить соединение
bool ClientManager::Connect(const QString& hostName, const quint16& port)
{
    return _protocol->Connect(hostName, port);
}

//Отправить команду
//Принимает строку команды
void ClientManager::SendCommand(const QString& command)
{
    _protocol->SendCommand(command);
}


//Отправить запрос
//Принимает строку запроса
//Возвращает ответ запроса
QString ClientManager::SendRequest(const QString& request)
{
    return _protocol->SendRequest(request);
}

//Деструктор
ClientManager::~ClientManager()
{
    delete _protocol;
}
