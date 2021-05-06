//
// Created by xvanop01 on 6. 5. 2021.
//
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "mqtt/client.h"

#include "sensors/Sensor.h"

int main(int argc, char* argv[]) {
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
    for (auto & sensor : sensors) {
        std::cout << sensor->getTopic() << "\n";
    }
    //const std::string SERVER_ADDRESS("tcp://localhost:1883");
    for (auto & sensor : sensors) {
        delete sensor;
    }
    sensors.~vector();
}
