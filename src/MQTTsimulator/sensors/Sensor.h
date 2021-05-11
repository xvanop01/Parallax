#ifndef PARALLAX_SENSOR_H
#define PARALLAX_SENSOR_H

#include <string>
#include <vector>

/**
 * Class simulating group of sensors
 * @author xjurke02
 * @author xvanop01
 */
namespace simulator {
    class Sensor {
    private:
        std::string topic; /**< Topic where sensors should publish messages */
        std::vector<float> actualInstance; /**< Remember actual values of sensors */
        int instances; /**< Number of sensors in group */
        int rangeMin; /**< Minimal value that sensors can send */
        int rangeMax; /**< Maximal value that sensors can send */
    public:
        /**
         * Constructor
         * @param line string that contains line from config file
         * @warning Undefined behavior when line is in wrong format
         * @note Format: topic number_of_sensors min_value max_value
         */
        explicit Sensor(std::string line);

        /**
         * Destructor
         */
        ~Sensor();

        /**
         * @return topic where sensors should transmit data
         */
        std::string getTopic();

        /**
         * Generate message for each sensor in group
         * @return vector containing message for each sensor
         */
        std::vector<std::string> getMessages();
    };
}

#endif //PARALLAX_SENSOR_H
