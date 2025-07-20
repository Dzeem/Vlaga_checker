#include <ESP8266WiFi.h>
#include "led.h"

// == Wi-Fi ==
const char* ssid = "";
const char* password = "";

void WiFiConnect() {
  Serial.print("Подключение к WiFi");
  WiFi.mode(WIFI_STA); // Указываем, что ESP в роли клиента, а не модема
  WiFi.begin(ssid, password); // Указываем логин/пароль к Wi-Fi

  int i = 0; // Переменная для цикла

  while (WiFi.status() != WL_CONNECTED) {
    delay(700);
    Serial.print(".");
    LEDSoff(); // Выключаем все светодиоды
    LEDS[i]->toggle(); // Переключаем состояние светодиода
    if (i == LEDSlength - 1) { // Если дошли до конца массива
      i = 0; // Сбрасываем счетчик
    } else {
      i++; // Иначе просто увеличиваем счетчик
    }
  }

  LEDSoff(); // Выключаем все светодиоды
  Serial.println("\nWiFi подключен!");
  Serial.println("IP: " + WiFi.localIP().toString()); // Вывод полученнного IP
  Serial.println("Маска подсети: " + WiFi.subnetMask().toString()); // Вывод маски подсети
  Serial.println("Шлюз: " + WiFi.gatewayIP().toString()); // Вывод шлюза
}