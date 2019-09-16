#include <QCoreApplication>
//#include <IProtocol.h>
#include <iostream>
#include <ClientManager.h>


using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    IProtocol* protocol = new SocketProtocol();

    ClientManager manager = ClientManager(protocol);

    int b;
    if(manager.Connect("127.0.0.1", 5025))
    {
        cout << "connection installed)" << endl;

        cin >> b;

        manager.SendCommand("CALCULATE1:MARKER2 ON\n");

        manager.SendCommand("CALCULATE1:MARKER1:X 2000000000\n");
    }
    else
    {
        cout << "fail connecting(" << endl;
    }



    return a.exec();
}
