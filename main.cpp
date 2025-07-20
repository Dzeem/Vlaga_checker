#include <Arduino.h>
#include "led.h"
#include "wi_fi.h"
#include "tg.h"

//Создаем светодиоды:
LED blue(D1);   // Синий
LED green(D2);  // Зеленый
LED yellow(D5); // Желтый
LED orange(D6); // Оранжевый
LED red(D7);    // Красный
LED* LEDS[] = {&blue, &green, &yellow, &orange, &red}; // Массив со всеми светодиодами
const int LEDSlength = sizeof(LEDS) / sizeof(LEDS[0]);

bool messageForwarded = false; // Переменная чтоб не отправлять тыщу раз уведы в тг
unsigned long checkTime = 0; // Вспомогательная переменная
unsigned long nowTime; // Переменная для указания времени с начала работы ESP


void setup() {
  Serial.begin(9600); // Запускаем Serial (порт для вывода в монитор порта)
  WiFiConnect(); // Подключаемся к Wi-Fi + индикация подключения
  sendTelegramMessage("Запускаю сканер почвы..."); // Отправляем сообщение в Telegram
}

void loop() {
  nowTime = millis();
  if (nowTime - checkTime >= 2000) {
    checkTime = nowTime;
    int vlaga = analogRead(A0);  // Читаем влажность с аналогового входа A0 (0–1023)
    Serial.print("Влажность: ");    // Печатаем в монитор порта текст
    Serial.println(vlaga);       // Печатаем значение + переход строки на новую

    if (vlaga < 300) {
      LEDSoff();   // Выключаем все светодиоды
      blue.on();     // Включаем светодиод на перелив
      messageForwarded = false;    
    } else if (vlaga < 600) {
      LEDSoff();   // Выключаем все светодиоды
      green.on();    // Иначе → переключаем светодиод на норм
      messageForwarded = false;
    } else if (vlaga < 650) {
      LEDSoff();   // Выключаем все светодиоды
      yellow.on();   // Иначе → переключаем светодиод на подсох
      messageForwarded = false;
    } else if (vlaga < 700) {

      orange.on();   // Иначе → переключаем светодиод на засыхает
      messageForwarded = false;
    } else {
      LEDSoff();   // Выключаем все светодиоды
      red.on();      // Иначе → переключаем светодиод на засох
      if (messageForwarded == false) {
        String msg = "🚨 Цветочек помирает! Влажность: " + String(vlaga) + ". Пора поливать!";
        sendTelegramMessage(msg);
        messageForwarded = true;
      }    
    }
  }
}