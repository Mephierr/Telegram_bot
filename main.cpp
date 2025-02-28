#include <sqlite3.h>
#include <tgbot/tgbot.h>
#include <iostream>


int SaveMessage(std::string message, int chat_id, sqlite3* DB, char* messageError, int &exit){

    std::string sql;
    sqlite3_free(messageError);
    if(message[0] == '/'){
        
        sql = "INSERT INTO COMMANDS(chat_id, command) VALUES(" + std::to_string(chat_id) + ", " + "'" + message + "'" + ");";
        exit =sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
            if(exit != SQLITE_OK){
        std::cerr << "Error inserted new command in COMMANDS: " << messageError << std::endl;
        sqlite3_free(messageError);
        return -1;
            }else{
        std::cout << "Registed new command." << std::endl;
        return 0;
    }
    }

    
    sql = "INSERT INTO MESSAGES(chat_id, message) VALUES(" + std::to_string(chat_id) + ", " + "'" + message + "'" + ");";
    exit =sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

    if(exit != SQLITE_OK){
        std::cerr << "Error inserted new message in MESSAGES: " << messageError << std::endl;
        sqlite3_free(messageError);
        return -1;
    }else{
        std::cout << "Registed new message." << std::endl;
        return 0;
    }
}



int main()
{
    sqlite3* db;
    char* messageError = NULL;
    int exit = 0;
    exit = sqlite3_open("telegram.db", &db); 
    const char* TOKEN = "WRITE YOUR TOKEN";
    TgBot::Bot bot(TOKEN);

    exit = sqlite3_open("telegram.db", &db); 
    const char* TOKEN = "WRITE YOUR TOKEN";


    bot.getEvents().onCommand("start", [&bot, &db, &messageError, &exit](TgBot::Message::Ptr message) {
        //TgBot::InlineKeyboardMarkup::Ptr keyboard = ;
                bot.getApi().sendMessage(message->chat->id, "Hi", nullptr, 0, nullptr);
                std::cout << "User " << message->chat->id << " started bot\n";
        });

    bot.getEvents().onAnyMessage([&bot, &db, &messageError, &exit](TgBot::Message::Ptr message){
        SaveMessage(message->text.c_str(), message->chat->id, db, messageError, exit);
            if(StringTools::startsWith(message->text, "/start")){
                bot.getApi().deleteMessage(message->chat->id, message->messageId);
                return;
            }
        });

    try {
        std::cout << "Bot username: " << bot.getApi().getMe()->username << std::endl;
        TgBot::TgLongPoll longPoll(bot);
            while (true) {
                longPoll.start();
            }
        } catch (TgBot::TgException& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    sqlite3_close(db);
    return 0;
}