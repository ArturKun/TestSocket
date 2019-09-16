#include <QCoreApplication>
#include <IProtocol.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    IProtocol* protocol = new SocketProtocol();

    if(protocol->Connect("127.0.0.1", 5025))
    {
        cout << "connection installed)" << endl;
        protocol->SendCommand("CALCULATE1:MARKER2 ON\n");

        protocol->SendCommand("CALCULATE1:MARKER1:X 2000000000\n");
    }
    else
    {
        cout << "fail connecting(" << endl;
    }



    return a.exec();
}
