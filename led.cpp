#include <Arduino.h>
#include "led.h"

LED::LED(int pin) {
    this -> pin = pin; // Указываем, что переменная внутри класса (this) = то, что пришло в параметре
    pinMode(pin, OUTPUT); // Устанавливаем пин как выход
    digitalWrite(pin, LOW); // Выключаем светодиод
}

void LED::on() {
    digitalWrite(pin, HIGH); // Включаем светодиод
}
void LED::off() {
    digitalWrite(pin, LOW); // Выключаем светодиод
}
void LED::toggle() {
    digitalWrite(pin, !digitalRead(pin)); // Переключаем состояние (вкл/выкл)
}
void LED::blink(int delayMs) {
    on(); // Включаем светодиод
    delay(delayMs); // Ждем указанное время
    off(); // Выключаем светодиод
    delay(delayMs); // Ждем указанное время
}

void LEDSon() {
  for (int i = 0; i < LEDSlength; i++) {
    LEDS[i]->on();
  }
}
void LEDSoff() {
  for (int i = 0; i < LEDSlength; i++) {
    LEDS[i]->off();
  }
}