#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#endif // CLIENTMANAGER_H

#include <IProtocol.h>

//Менеджер для подключения и связи
class ClientManager
{

private:

    //Протокол подключения
    IProtocol* _protocol;

public:

    //Конструктор принимающий протокол,
    //по которому будет происходить соединение
    ClientManager(IProtocol* protocol);

    //Установить соединение
    bool Connect(const QString hostName, quint16 port);

    //Отправить команду
    //Принимает строку команды
    void SendCommand(QString command);

    //Отправить запрос
    //Принимает строку запроса
    //Возвращает ответ запроса
    QString SendRequest(QString request);

    //Деструктор
    ~ClientManager();
};
