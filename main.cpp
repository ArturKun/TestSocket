#include <QCoreApplication>
#include <iostream>
#include <ClientManager.h>
#include <SocketProtocol.h>
#include <SCPICommands.h>

using namespace std;

void MainProgram();
void Connect(const QString hostName, quint16 port);
float EnterFrequency();
void SetMarker(int markerNumber, double stimulus);
void GetMathStatistics();
bool StringToFloat(string string, float& result);

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
    float frequency;
    bool end = false;
    bool theEnd;
    unsigned short channelNumber = 1;
    while (!end)
    {
        theEnd = false;
        Connect("127.0.0.1", 5025);

        cout << "Enter the stimulus of the first marker in MHz, "
                "in the range 0.1 - 9000 MHz" << endl;

        manager->SendCommand(SCPICommands::
                             SetMarkersStatesCommand(channelNumber, 0, true));

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
                                     GetMathStatisticsRequest(channelNumber)).toStdString();

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
float EnterFrequency()
{
    const float minFrequency = 0.1f;
    const float maxFrequency = 9000;

    std::string enterString;

    cin >> enterString;

    float result;
    while(!(StringToFloat(enterString, result)) ||
          (result > maxFrequency) || (result < minFrequency))
    {
        cout << "Value entered incorrectly. Repeat frequency entry" << endl;
        cin >> enterString;
    }
    return result;
}

//Конвертировать string в double.
//Если в строке есть недопустимый символ return false
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
