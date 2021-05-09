#include <iostream>
#include <chrono>
#include <csignal>
#include <string>

#include "mqttMsgStruct/Messages.h"

bool sigint_received = false;

/**
 * Register SIGINT and tell the program to end
 * @param signum signal number
 */
void signalHandler( int signum ) {
    std::cout << "Received signal " << signum << "\n";
    if (signum == SIGINT) {
        std::cout << "Closing application\n";
        sigint_received = true;
    }
}

int main(int argc, char* argv[]) {
    signal(SIGINT, signalHandler);
    int maxMsg = 50;
    for (int i = 1; i < argc; i++) {
        if (((std::string)"-n") == argv[i]) {
            if (argc == i + 1) {
                std::cerr << "Missing argument after -n!\n";
                return 1;
            }
            i++;
            maxMsg = std::stoi(argv[i]);
        } else {
            std::cerr << "Invalid argument: " << argv[i] << "\n";
            return 1;
        }
    }
    auto client = new mqtt::async_client(SERVER_ADDRESS, "", mqtt::create_options(MQTTVERSION_5));
    explorer::Messages* msgs;
    try {
        msgs = new explorer::Messages(50, client);
    } catch (const mqtt::exception& e) {
        std::cerr << "Can't connect to broker!\n" << e.what() << "\n";
        return 3;
    }
    while (!sigint_received) {

    }
    std::vector<std::vector<std::string>> vec = msgs->getMessages(msgs->parseTopic("/#"));
    for (auto & item : vec) {
        for (auto & msg : item) {
            std::cout << msg << "\n";
        }
    }
    delete msgs;
    delete client;
}