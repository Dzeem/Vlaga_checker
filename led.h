#ifndef LED_H
#define LED_H

class LED {
    private:
        int pin; // Задаем номер пина, к которому подключен светодиод
    public:
        LED(int pin);
        void on(); // Включить светодиод
        void off(); // Выключить светодиод
        void toggle(); // Переключить состояние (вкл/выкл)
        void blink(int delayMs = 500); // Моргануть
};

extern LED* LEDS[]; // Массив со всеми светодиодами
extern const int LEDSlength; // Количество светодиодов

void LEDSon(); // Включить все светодиоды
void LEDSoff(); // Выключить все светодиоды

#endif