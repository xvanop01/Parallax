/**
 * @brief Parallax application Messages memory Header File
 * Header file declares functions which administrate messages history
 * @author xvanop01
 */

#ifndef PARALLAX_MEMORY_H
#define PARALLAX_MEMORY_H

#include <vector>
#include <string>

/**
 * @brief Used to save topics and their messages
 */
namespace explorer {
    class Memory {
    private:
        std::vector<std::vector<std::string>> msgs;
        std::vector<std::vector<std::string>> myMsgs;
    public:
        Memory();
        ~Memory();
        /**
         * @brief isNew Check if the message is alreade saved or if it is a new message
         * @param topic Topic of the message
         * @param msg Message to check
         * @return true if message wasn't previously saved
         */
        bool isNew(std::string topic, std::string msg);
        /**
         * @brief isMyMsg Check if message was send by user
         * @param topic Topic of the message
         * @param msg Message to check
         * @return true if user's message
         */
        bool isMyMsg(std::string topic, std::string msg);
        /**
         * @brief saveNew Save new message to class
         * @param topic Topic of the message
         * @param msg Message to save
         */
        void saveNew(std::string topic, std::string msg);
        /**
         * @brief saveMyMsg Save new message, that user has sent
         * @param topic Topic of the message
         * @param msg Message to save
         */
        void saveMyMsg(std::string topic, std::string msg);
    };
}

#endif //PARALLAX_MEMORY_H
