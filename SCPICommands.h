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
    QString static SetMarkersStatesCommand(const unsigned short &channel,
                                           const unsigned short &markers,
                                           const bool &state);

    //Установить положение маркера по оси стимула в Гц, на канале (1-16)
    QString static SetMarkerStimulusCommand(const unsigned short &channel,
                                            const unsigned short &marker,
                                            const float &frequency);

    //Установить состояние диапазона математической статистики
    QString static SetMathStatisticRangeStateCommand(const unsigned short &channel,
                                                     const bool &state);

    //Получить математическую статистику на канале (1-16)
    QString static GetMathStatisticsCommand(const unsigned short &channel);
};

#endif // SCPICOMMANDS_H
