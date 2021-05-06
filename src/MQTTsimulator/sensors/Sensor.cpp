//
// Created by xvanop01 on 6. 5. 2021.
//

#include "Sensor.h"

simulator::Sensor::Sensor(std::string line) {
    this->topic = line.substr(0, line.find(' '));
    std::string parsed = line.substr(0, line.find(' ', this->topic.size() + 1));
    this->instances = stoi(line.substr(parsed.size() + 1, line.find(' ', parsed.size() + 1)));
    this->rangeMin = std::stof(line.substr(parsed.size() + 1,line.find(' ', parsed.size() + 1)));
    parsed = line.substr(0,line.find(' ', parsed.size() + 1));
    this->rangeMax = std::stof(line.substr(parsed.size() + 1, line.size()));
    this->actualInstance = new std::vector();
    for (int i = 0; i < this->instances; i++) {
        this->actualInstance.push_back((float)(rand() % (this->rangeMax - this->rangeMin) + this->rangeMin));
    }
}

simulator::Sensor::~Sensor() {
    delete this->actualInstance;
}

std::string simulator::Sensor::getTopic() {
    return this->topic;
}

std::vector<std::string> simulator::Sensor::getMessages() {
    std::vector<std::string>
    return std::vector<std::string>();
}
