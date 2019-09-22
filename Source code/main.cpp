#include <QCoreApplication>
#include <iostream>
#include <ClientManager.h>
#include <SocketProtocol.h>
#include <SCPICommands.h>

using namespace std;

//Основная программа
void MainProgram();

//Установить соединение
void Connect(const QString hostName, quint16 port);

//Считывание и проверка введенного стимула
float EnterFrequency();

//Конвертировать string в double.
bool StringToFloat(string string, float& result);

static ClientManager* manager;

static IProtocol* protocol;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    try
    {
        MainProgram();
    }
    catch (std::exception &exception)
    {
        cout << ("Error: " + std::string(exception.what()) +
                 ". Reload the program") << endl;
    }

    delete protocol;
    delete manager;

    system("pause");

    a.exit(1);
}

//Основная программа
void MainProgram()
{
    string enterStimulus;
    string symbol;
    float frequency;
    bool end = false;
    bool theEnd;
    unsigned short channelNumber = 1;

    Connect("localhost", 5025);

    while (!end)
    {
        theEnd = false;

        cout << "Enter the stimulus of the first marker in MHz, "
                "in the range 0.1 - 9000 MHz" << endl;

        manager->SendCommand(SCPICommands::
                             SetMarkersStatesCommand(channelNumber, 2, true));

        manager->SendCommand(SCPICommands::
                             SetMathStatisticRangeStateCommand(channelNumber, true));

        frequency =  EnterFrequency();

        manager->SendCommand(SCPICommands::
                             SetMarkerStimulusCommand(channelNumber, 1, frequency));

        cout << "Enter the stimulus of the second marker in MHz, "
                "in the range 0.1 - 9000 MHz" << endl;

        frequency =  EnterFrequency();

        manager->SendCommand(SCPICommands::
                             SetMarkerStimulusCommand(channelNumber, 2, frequency));

        cout << manager->SendRequest(SCPICommands::
                                     GetMathStatisticsCommand(channelNumber)).toStdString();

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
    protocol = new SocketProtocol();

    manager = new ClientManager(protocol);

    cout << "Connecting..." << endl;

    if(manager->Connect(hostName, port))
    {
        cout << "Connection installed." << endl;
    }
}

//Считывание и проверка введенного стимула
float EnterFrequency()
{
    const float MIN_FREQUENCY = 0.1f;
    const float MAX_FREQUENCY = 9000;

    string enterString;

    cin >> enterString;

    float result;
    while(!(StringToFloat(enterString, result)) ||
          (result > MAX_FREQUENCY) || (result < MIN_FREQUENCY))
    {
        cout << "Value entered incorrectly. Repeat frequency entry" << endl;
        cin >> enterString;
    }
    return result;
}

//Конвертировать string в double.
//Если в строке есть недопустимый символ вернуть false
bool StringToFloat(string string, float& result)
{
    char* endPtr;

    result = strtof(string.data(), &endPtr);

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
