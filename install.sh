#!/bin/bash

# Installing sqlite3
apt install sqlite3 libsqlite3-dev -y

# Installing boost packages and cmake
apt install g++ make binutils cmake libboost-system-dev libssl-dev zlib1g-dev libcurl4-openssl-dev -y

# Clone TgBot from repository, build and install
git clone https://github.com/reo7sp/tgbot-cpp.git
cd tgbot-cpp
cmake .
make -j4
make install
echo Libraries successfully installed and built