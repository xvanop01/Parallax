/**
 * @brief Parallax application Data feeder
 * Loads data from config files and simulate MQTT transmissions based on them
 * @author xjurke02
 * @author xvanop01
 */
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <csignal>
#include "mqtt/client.h"

#include "sensors/Sensor.h"

#define QOS 1
#define SERVER_ADDRESS "tcp://localhost:1883"

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

/**
 * Main function launching application
 */
int main(int argc, char* argv[]) {
    signal(SIGINT, signalHandler);
    std::string configPath;
    for (int i = 1; i < argc; i++) {
        if (((std::string)"-c") == argv[i]) {
            if (argc == i + 1) {
                std::cerr << "Missing argument after -c!\n";
                return 1;
            }
            i++;
            configPath = argv[i];
        } else {
            std::cerr << "Invalid argument: " << argv[i] << "\n";
            return 1;
        }
    }
    if (configPath.empty()) {
        configPath = "../config/simDefault.config";
    }
    std::fstream simConfigFile;
    simConfigFile.open(configPath, std::ios::in);
    if (!simConfigFile.is_open()) {
        std::cerr << "Can't open config file!\n";
        return 2;
    }
    std::string line;
    std::vector<simulator::Sensor *> sensors = {};
    while (std::getline(simConfigFile, line)) {
        sensors.push_back(new simulator::Sensor(line));
    }
    simConfigFile.close();

    auto connectOptions = mqtt::connect_options_builder()
            .mqtt_version(5)
            .properties({{mqtt::property::SESSION_EXPIRY_INTERVAL, 100}})
            .keep_alive_interval(std::chrono::minutes(1))
            .finalize();
    mqtt::async_client client(SERVER_ADDRESS, "ParallaxDataFeeder", mqtt::create_options(MQTTVERSION_5));
    try {
        std::cout << "Connecting to server..\n";
        auto connection = client.connect(connectOptions);
        connection->wait();
    } catch (const mqtt::exception& e) {
        std::cerr << "Can't connect to broker!\n" << e.what() << "\n";
        return 3;
    }
    std::cout << "Connection OK\n";

    while (!sigint_received) {
        for (auto & sensor : sensors) {
            mqtt::topic topic {client, sensor->getTopic(), QOS};
            for (auto & msg : sensor->getMessages()) {
                topic.publish(msg);
                std::cout << msg << "\n";
            }
        }
        sleep(1);
    }

    for (auto & sensor : sensors) {
        delete sensor;
    }
}
