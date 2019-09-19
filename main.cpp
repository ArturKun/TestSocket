#include <QCoreApplication>
#include <iostream>
#include <ClientManager.h>

using namespace std;

void MainProgram();
void Connect(const QString hostName, quint16 port);
void SetMarker(int markerNumber, double stimulus);
void GetMathStatistics();
bool StringToDouble(string string, double& result);

double EnterFrequency(string string);

static ClientManager* manager;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    try
    {
        MainProgram();
    }
    catch (std::exception &exception)
    {
        cout << ("Error: " + std::string(exception.what()));
    }

    delete manager;

    a.exit(1);
}

//Основная программа
void MainProgram()
{
    string enterStimulus;
    string symbol;
    double frequency;

    bool end = false;

    bool theEnd;

    Connect("127.0.0.1", 5025);

    while (!end)
    {
        theEnd = false;
        cout << "Enter the stimulus of the first marker in MHz, "
                "in the range 0.1 - 9000 MHz" << endl;

        cin >> enterStimulus;

        frequency =  EnterFrequency(enterStimulus);

        manager->SendCommand("CALCULATE1:MARKER2 ON\n");

        manager->SendCommand("CALC1:MST:DOM ON\n");

        SetMarker(1, frequency);

        cout << "Enter the stimulus of the second marker in MHz, "
                "in the range 0.1 - 9000 MHz" << endl;

        cin >> enterStimulus;

        frequency =  EnterFrequency(enterStimulus);

        SetMarker(2, frequency);

        GetMathStatistics();

        while(!theEnd)
        {
            cout << "Exit in the programm (Y/N)?" << endl;
            cin >> symbol;

            if(symbol == "N")
            {
                end = false;
                theEnd = true;
            }
            else if(symbol == "Y")
            {
                end = true;
                theEnd = true;
            }
            else
            {
                theEnd = false;
            }
        }
    }
}

//Установить соединение
void Connect(const QString hostName, quint16 port)
{
    IProtocol* protocol = new SocketProtocol();

    manager = new ClientManager(protocol);
    (manager)->Connect(hostName, port);

    cout << "connection installed." << endl;
}

//Установить маркер
void SetMarker(int markerNumber, double stimulus)
{
    long long int frequency =
            static_cast<long long int>(stimulus * 1000000);

    manager->SendCommand("CALCULATE1:MARKER" +
                         QString::number(markerNumber) + ":X " +
                         QString::number(static_cast<double>(frequency)) +
                         "\n");
}

//Получить математическую статистику
void GetMathStatistics()
{
    cout << manager->SendRequest("CALC1:MST:DATA?\n").toStdString();
}

//Конвертировать string в double.
//Если в строке есть недопустимый символ return false
bool StringToDouble(string string, double& result)
{
    char* endPtr;

    result = strtod(string.data(), &endPtr);

    if(*endPtr)
    {
        result = 0;
        return false;
    }
    else
    {
        return true;
    }
}

double EnterFrequency(string string)
{
    double result;
    while(!(StringToDouble(string, result)) ||
          (result > 9000) || (result < 0.1))
    {
        cout << "Value entered incorrectly. Repeat frequency entry" << endl;
        cin >> string;
    }
    return result;
}





