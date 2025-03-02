cmake_minimum_required(VERSION 3.10)
project(telegram_bot)

set(CMAKE_CXX_STANDARD 17)

# Ищем библиотеку TgBot
find_package(TgBot REQUIRED)

# Ищем Boost и OpenSSL
find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)

# Добавляем исполняемый файл
add_executable(bot main.cpp)

# Подключаем библиотеки
target_link_libraries(bot PRIVATE
    TgBot::TgBot
    ${Boost_LIBRARIES}
    ${OPENSSL_LIBRARIES}
    pthread
)