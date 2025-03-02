#include <tgbot/tgbot.h>
#include <iostream>

using namespace TgBot;

int main()
{
    std::string token = "";
    Bot bot(token);

    bot.getEvents().onCommand("start", [&bot](Message::Ptr message)
    {
        bot.getApi().sendMessage(message->chat->id,"Привет! Я тестовый бот!");
    });

    bot.getEvents().onNonCommandMessage([&bot](Message::Ptr message)
    {
        bot.getApi().sendMessage(message->chat->id, "Вы написали : " + message->text);
    });

    try {
        std::cout << "Бот запущен...\n";
        bot.getApi().deleteWebhook();
        TgLongPoll longPoll(bot);
        while (true) {
            longPoll.start();
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }

    return 0;

}