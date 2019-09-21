#ifndef SCPICOMMANDS_H
#define SCPICOMMANDS_H

#include <QString>

using namespace std;

//Класс предоставляющий SCPI команды и запросы в виде строк
class SCPICommands
{
private:

    //проверяет номер канала и маркера
    void static NumberVerification(unsigned short number);

    //переводит bool в int
    QString static BoolToQString(bool boolean);

public:

    //Установить состояние маркеров (1-16), на канале (1-16)
    QString static SetMarkersStatesCommand(unsigned short channel,
                                           unsigned short markers, bool state);

    //Установить положение маркера по оси стимула в Гц, на канале (1-16)
    QString static SetMarkerStimulusCommand(unsigned short channel,
                                            unsigned short marker, float frequency);

    //Установить состояние диапазона математической статистики
    QString static SetMathStatisticRangeStateCommand(unsigned short channel,
                                                     bool state);

    //Получить математическую статистику на канале (1-16)
    QString static GetMathStatisticsCommand(unsigned short channel);
};

#endif // SCPICOMMANDS_H
