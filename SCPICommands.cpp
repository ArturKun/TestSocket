#include <QString>
#include <SCPICommands.h>

//Установить состояние маркеров (1-16), на канале (1-16)
QString SCPICommands::SetMarkersStatesCommand(unsigned short channel,
                                              unsigned short markers, bool state)
{
    NumberVerification(channel);
    NumberVerification(markers);

    return "CALCULATE" + QString::number(channel) +
            ":MARKER" + QString::number(markers) + " " +  BoolToQString(state) + "\n";
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

//Установить состояние диапазона математической статистики
QString SCPICommands::SetMathStatisticRangeStateCommand(unsigned short channel,
                                                        bool state)
{
    NumberVerification(channel);

    return "CALC" + QString::number(channel) + ":MST:DOM " + BoolToQString(state) + "\n";
}

//Получить математическую статистику на канале (1-16)
QString SCPICommands::GetMathStatisticsRequest(unsigned short channel)
{
    NumberVerification(channel);

    return "CALC"+ QString::number(channel) + ":MST:DATA?\n";
}

void SCPICommands::NumberVerification(unsigned short number)
{
    const unsigned short minNumber = 1;
    const unsigned short maxNumber = 16;

    if(number > maxNumber || number < minNumber)
    {
        throw std::runtime_error("Channel or marker number entered incorrectly."
                                 "Value must be in the range of 1 to 16.");
    }
}

QString SCPICommands::BoolToQString(bool boolean)
{
    return boolean ? "1" : "0";
}
