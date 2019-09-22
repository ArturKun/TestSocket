#ifndef IPROTOCOL_H
#define IPROTOCOL_H

#include <QString>

//Интерфейс протокола, который отвечает за связь
class IProtocol
{

public:

    //Подключение
    //Если подключение установлено return true, иначе false
    virtual bool Connect(const QString& hostName, const quint16& port) = 0 ;

    //Отправить команду
    //Принимает строку команды
    virtual void SendCommand(const QString& command) = 0;

    //Отправить запрос
    //Принимает строку запроса
    //Возвращает ответ запроса
    virtual QString SendRequest(const QString& request) = 0;

    virtual ~IProtocol() = default;
};

#endif // IPROTOCOL_H
