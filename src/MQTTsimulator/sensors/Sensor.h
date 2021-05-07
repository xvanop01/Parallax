//
// Created by xvanop01 on 6. 5. 2021.
//

#ifndef PARALLAX_SENSOR_H
#define PARALLAX_SENSOR_H

#include <string>
#include <vector>

namespace simulator {
    class Sensor {
    private:
        std::string topic;
        std::vector<float> actualInstance;
        int instances;
        int rangeMin;
        int rangeMax;
    public:
        explicit Sensor(std::string line);

        ~Sensor();

        std::string getTopic();
        std::vector<std::string> getMessages();
    };
}


#endif //PARALLAX_SENSOR_H
