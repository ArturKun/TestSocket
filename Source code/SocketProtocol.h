#ifndef SOCKETPROTOCOL_H
#define SOCKETPROTOCOL_H

#include <QString>
#include <QTcpSocket>
#include <IProtocol.h>

//Протокол для связи на основе Socket
class SocketProtocol : public IProtocol
{
private:

    QTcpSocket* _socket;

public:

    //Конструктор по умолчанию
    SocketProtocol();

    //Подключение
    //Если подключение установлено return true, иначе false
    bool Connect(const QString& hostName, const quint16 &port) override;

    //Отправить команду
    //Принимает строку команды
    virtual void SendCommand(const QString& command) override;

    //Отправить запрос
    //Принимает строку запроса
    //Возвращает ответ запроса
    virtual QString SendRequest(const QString& request) override;

    //Деструктор по умолчанию
    virtual ~SocketProtocol() override;
};

#endif // SOCKETPROTOCOL_H
