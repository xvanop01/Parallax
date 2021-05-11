/**
 * Implementation of Sensor.h
 * @author xjurke02
 * @author xvanop01
 */

#include "Sensor.h"

simulator::Sensor::Sensor(std::string line) {
    this->topic = line.substr(0, line.find(' '));
    std::string parsed = line.substr(0, line.find(' '));
    this->instances = stoi(line.substr(parsed.size() + 1, line.find(' ', parsed.size() + 1)));
    parsed = line.substr(0,line.find(' ', parsed.size() + 1));
    this->rangeMin = std::stof(line.substr(parsed.size() + 1,line.find(' ', parsed.size() + 1)));
    parsed = line.substr(0,line.find(' ', parsed.size() + 1));
    this->rangeMax = std::stof(line.substr(parsed.size() + 1, line.size()));
    this->actualInstance = {};
    for (int i = 0; i < this->instances; i++) {
        this->actualInstance.push_back((float)(rand() % (this->rangeMax - this->rangeMin) + this->rangeMin));
    }
}

simulator::Sensor::~Sensor() {
}

std::string simulator::Sensor::getTopic() {
    return this->topic;
}

std::vector<std::string> simulator::Sensor::getMessages() {
    std::vector<std::string> responses = {};
    for (int i = 0; i < this->instances; i++) {
        responses.push_back("{\"ID\":\"" + this->topic + std::to_string(i) + "\", \"value\":\"" +
        std::to_string(this->actualInstance[i]) + "\"}");
        this->actualInstance[i] += ((float)(rand()) / (float)(RAND_MAX/2)) - 1;
        if (this->actualInstance[i] < this->rangeMin) {
            this->actualInstance[i]++;
        } else if (this->actualInstance[i] > this->rangeMax) {
            this->actualInstance[i]--;
        }
    }
    return responses;
}
