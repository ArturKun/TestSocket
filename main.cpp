#include <QCoreApplication>
//#include <IProtocol.h>
#include <iostream>
#include <ClientManager.h>


using namespace std;

void MainProgram();
void Connect(const QString hostName, quint16 port);
void SetMarker(int markerNumber, float stimulus);
void GetMathStatistics();

static ClientManager* manager;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MainProgram();

    a.exit();
    //return a.exec();
}

void MainProgram()
{
    float stimulus;
    char symbol;

    bool end = false;

    Connect("127.0.0.1", 5025);

    while (!end)
    {
        cout << "Enter the stimulus of the first marker in MHz, "
                "in the range 0.1 - 9000 MHz" << endl;

        cin >> stimulus;

        manager->SendCommand("CALCULATE1:MARKER2 ON\n");

        manager->SendCommand("CALC1:MST:DOM ON\n");

        SetMarker(1, stimulus);

        cout << "Enter the stimulus of the second marker in MHz, "
                "in the range 0.1 - 9000 MHz" << endl;

        cin >> stimulus;

        SetMarker(2, stimulus);

        GetMathStatistics();

        cout << "Exit in the programm (Y/N)?" << endl;

        cin >> symbol;

        if(symbol == 'N')
        {
            end = false;
        }
        else if(symbol == 'Y')
        {
            end = true;
        }
    }
}

//Установить соединение
void Connect(const QString hostName, quint16 port)
{
    IProtocol* protocol = new SocketProtocol();

    manager = new ClientManager(protocol);

    //обернуть в try catch
    if(manager->Connect(hostName, port))
    {
        cout << "connection installed." << endl;
    }
    else
    {
        //выкинуть сообщение эксепшена
    }
}

//Установить маркер
void SetMarker(int markerNumber, float stimulus)
{
    long long int frequency =
            static_cast<long long int>(stimulus * 1000000);

    manager->SendCommand("CALCULATE1:MARKER" +
                         QString::number(markerNumber) + ":X " +
                         QString::number(static_cast<double>(frequency)) +
                         "\n");
}

void GetMathStatistics()
{
    cout << manager->SendRequest("CALC1:MST:DATA?\n").toStdString();
}




