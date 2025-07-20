#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>
#include "led.h"

// == Telegram bOT ==
const char* botToken = ""; // API токен бота
const String userID = ""; // ID юзера тг
WiFiClientSecure secured_client;
UniversalTelegramBot bot(botToken, secured_client);

void sendTelegramMessage(String message) {
    secured_client.setInsecure(); // Отключаем проверку SSL-сертификата
    bot.sendMessage(userID, message, "Markdown");
    LEDSon();
    delay(300);
    LEDSoff();
    delay(300);
    LEDSon();
    delay(300);
    LEDSoff();
    delay(300);
}
