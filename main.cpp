#include <QCoreApplication>
#include <iostream>
#include <ClientManager.h>
#include <SocketProtocol.h>

using namespace std;

void MainProgram();
void Connect(const QString hostName, quint16 port);
double EnterFrequency();
void SetMarker(int markerNumber, double stimulus);
void GetMathStatistics();
bool StringToDouble(string string, double& result);

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
        cout << ("Error: " + std::string(exception.what()) + ". Reload the program");
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

    while (!end)
    {
        theEnd = false;
        Connect("127.0.0.1", 5025);

        cout << "Enter the stimulus of the first marker in MHz, "
                "in the range 0.1 - 9000 MHz" << endl;

        frequency =  EnterFrequency();

        manager->SendCommand("CALCULATE1:MARKER2 ON\n");

        manager->SendCommand("CALC1:MST:DOM ON\n");

        SetMarker(1, frequency);

        cout << "Enter the stimulus of the second marker in MHz, "
                "in the range 0.1 - 9000 MHz" << endl;

        frequency =  EnterFrequency();

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

    cout << "Connection installed." << endl;
}

//Считывание и проверка введенного стимула
double EnterFrequency()
{
    const double minFrequency = 0.1;
    const double maxFrequency = 9000;

    std::string enterString;

    cin >> enterString;

    double result;
    while(!(StringToDouble(enterString, result)) ||
          (result > maxFrequency) || (result < minFrequency))
    {
        cout << "Value entered incorrectly. Repeat frequency entry" << endl;
        cin >> enterString;
    }
    return result;
}


//Установить маркер
void SetMarker(int markerNumber, double stimulus)
{
    const int multiplier = 1000000;

    long long int frequency =
            static_cast<long long int>(stimulus * multiplier);

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
