#include <QString>
#include <SCPICommands.h>

//Установить состояние маркеров (1-16), на канале (1-16)
QString SCPICommands::SetMarkersStatesCommand(unsigned short channel,
                                              unsigned short markers, bool state)
{
    NumberVerification(channel);
    NumberVerification(markers);

    return "CALCULATE" + QString::number(channel) +
            ":MARKER" + QString::number(markers) + " " +  
            BoolToQString(state) + "\n";
}

//Установить положение маркера по оси стимула в МГц, на канале (1-16)
QString SCPICommands::SetMarkerStimulusCommand(unsigned short channel,
                                               unsigned short marker, float frequency)
{
    NumberVerification(channel);
    NumberVerification(marker);

    return "CALCULATE" + QString::number(channel) +":MARKER" +
            QString::number(marker) + ":X " +
            QString::number(frequency) +
            " Mhz\n";
}

//Установить состояние диапазона математической статистики (ON/OFF)
QString SCPICommands::SetMathStatisticRangeStateCommand(unsigned short channel,
                                                        bool state)
{
    NumberVerification(channel);

    return "CALC" + QString::number(channel) + ":MST:DOM " + 
            BoolToQString(state) + "\n";
}

//Получить математическую статистику на канале (1-16)
QString SCPICommands::GetMathStatisticsCommand(unsigned short channel)
{
    NumberVerification(channel);

    return "CALC"+ QString::number(channel) + ":MST:DATA?\n";
}

//Проверка номера маркера и номера канала
void SCPICommands::NumberVerification(unsigned short number)
{
    const unsigned short MIN_NUMBER = 1;
    const unsigned short MAX_NUMBER = 16;

    if(number > MAX_NUMBER || number < MIN_NUMBER)
    {
        throw std::invalid_argument("Channel or marker number entered incorrectly."
                                 "Value must be in the range of 1 to 16.");
    }
}

//Конвертировать bool в QString
QString SCPICommands::BoolToQString(bool boolean)
{
    return boolean ? "1" : "0";
}
