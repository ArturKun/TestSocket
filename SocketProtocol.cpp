#include <IProtocol.h>
#include <QTcpSocket>



SocketProtocol::SocketProtocol()
{
    _socket = new QTcpSocket();
}

//Подключение хосту
//Если подключение установлено return true, иначе false
bool SocketProtocol::Connect(QString hostName, quint16 port)
{
    _socket->connectToHost(hostName, port);
    return _socket->waitForConnected(1000);
}

//Отправить команду
//Принимает строку команды
void SocketProtocol::SendCommand(QString command)
{
    //Здесь генерируем эксепшен и пробрасываем ошибку
    _socket->write(command.toUtf8());
    bool res = _socket->waitForBytesWritten();
    QString str = _socket->errorString();
}

//Отправить запрос
//Принимает строку запроса
//Возвращает ответ запроса
QString SocketProtocol::SendRequest(QString request)
{
    QString result;
    _socket->write(request.toUtf8());
    //waitForReadyRead возвращает бул, если тру то збс, если нет то пробросить эксепшен
    _socket->waitForReadyRead(500);
    //TODO:может переделать?
    return result.append(_socket->readAll());
}

SocketProtocol::~SocketProtocol()
{

}

