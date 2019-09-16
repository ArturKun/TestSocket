

#ifndef IPROTOCOL_H
#define IPROTOCOL_H

#endif // IPROTOCOL_H

#include <QString>
#include <QTcpSocket>

//Интерфейс для создания соединения и отправки команд и запросов
class IProtocol
{
public:
    //Подключение
    //Если подключение установлено return true, иначе false
    virtual bool Connect(const QString hostName, quint16 port) = 0;

    //Отправить команду
    //Принимает строку команды
    virtual void SendCommand(QString command) = 0;

    //Отправить запрос
    //Принимает строку запроса
    //Возвращает ответ запроса
    virtual QString SendRequest(QString request) = 0;

    virtual ~IProtocol() = default;
};

class SocketProtocol : public IProtocol
{
private:

    QTcpSocket* _socket;

public:

    SocketProtocol();

    //Подключение
    //Если подключение установлено return true, иначе false
    bool Connect(const QString hostName, quint16 port) override;

    //Отправить команду
    //Принимает строку команды
    virtual void SendCommand(QString command) override;

    //Отправить запрос
    //Принимает строку запроса
    //Возвращает ответ запроса
    virtual QString SendRequest(QString request) override;

    virtual ~SocketProtocol() override;
};
