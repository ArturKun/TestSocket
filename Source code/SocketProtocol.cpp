#include <SocketProtocol.h>
#include <QTcpSocket>

using namespace std;

//Конструктор
SocketProtocol::SocketProtocol()
{
    _socket = new QTcpSocket();
}

//Подключение хосту
//Если подключение установлено return true, иначе false
bool SocketProtocol::Connect(const QString& hostName, const quint16& port)
{
    _socket->connectToHost(hostName, port);

    if(!_socket->waitForConnected())
    {
        throw std::runtime_error(_socket->errorString().toUtf8());
    }
    else
    {
        return true;
    }
}

//Отправить команду
//Принимает строку команды
void SocketProtocol::SendCommand(const QString& command)
{
    _socket->write(command.toUtf8());

    if(!_socket->waitForBytesWritten())
    {
        throw std::runtime_error(_socket->errorString().toUtf8());
    }
}

//Отправить запрос
//Принимает строку запроса
//Возвращает ответ запроса
QString SocketProtocol::SendRequest(const QString& request)
{
    QString result;

    _socket->write(request.toUtf8());

    if(!_socket->waitForBytesWritten())
    {
        throw std::runtime_error(_socket->errorString().toUtf8());
    }

    if(!_socket->waitForReadyRead())
    {
        throw std::runtime_error(_socket->errorString().toUtf8());
    }
    else
    {
        return result.append(_socket->readAll());
    }

}

//Деструктор
SocketProtocol::~SocketProtocol()
{
    delete _socket;
}

