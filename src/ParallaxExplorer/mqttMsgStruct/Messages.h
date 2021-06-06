/**
 * @brief Parallax application Messages Administration Header File
 * Header file declares functions which administrate messages (saving, getting, etc.)
 * @author xvanop01
 */

#ifndef PARALLAX_MESSAGES_H
#define PARALLAX_MESSAGES_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "mqtt/async_client.h"
#include "mqtt/topic.h"
#include <QTreeWidgetItem>
#include <ui_widget.h>
#include <QString>

#define QOS 1
#define SERVER_ADDRESS "tcp://localhost:1883"
#define SEND_MY_MSGS true
#define SAVE_LOCATION (std::string)"save/"


/**
 * @brief Functions which administrate messages (saving, getting, etc.)
 */
namespace explorer {

    /**
    * @struct topic
    * @brief Struct containing name, vector of subtopics and messages
    */
    struct topic {
        std::string name;
        std::vector<struct topic*> subtopic;
        std::vector<std::string> messages;
    };

    /**
    * @class Messages
    * @brief Class for messages administration
    */
    class Messages {
    private:
        int maxMsgs;
        mqtt::async_client* client;
        void deleteTopics(explorer::topic* target);
    public:
        struct topic* topics;
        /**
        * @param bufferSize Number of messages for each topic
        * @param client MQTT Client
        * @brief Constructor
        */
        explicit Messages(int bufferSize, mqtt::async_client* client);
        ~Messages();
        /**
        * @param parsedTopics Topic parsed to subtopics structure
        * @param msg Message to save
        * @brief Save message under topic
        */
        void saveMsg(std::vector<std::string> parsedTopics, std::string msg);
        /**
        * @param topic Whole topic
        * @return Parsed topic by subtopics to vector
        */
        static std::vector<std::string> parseTopic(std::string topic);
        /**
        * @param parsedTopics Topic parsed to subtopics structure
        * @return Messages sent to topic
        */
        std::vector<std::vector<std::string>> getMessages(std::vector<std::string> parsedTopics);
        /**
        * @param ref Reference to struct topic
        * @param target QTreeWidgetItem to expand
        * @param ui Reference to application
        * @brief Create children items for target using subtopics from ref
        */
        static void createChild(struct topic *ref, QTreeWidgetItem *target, Ui::Widget* ui);
        /**
        * @param target QTreeWidgetItem to get rid of children
        * @brief Delete children items from target
        */
        static void deleteChild(QTreeWidgetItem *target);
        /**
        * @param top Topic under which message will be send
        * @param msg Message to send
        * @param client Active MQTT Client
        * @brief Send message to client under topic top
        */
        void sendMsg(std::string top, std::string msg, mqtt::async_client* client);
        void sendMsg(std::string top, QByteArray msg, mqtt::async_client* client);
        /**
         * @brief saveFile Save file in msg
         * @param topic Topic of the file
         * @param msg Message with file data
         */
        static void saveFile(std::string topic, std::string msg);
    };
}


#endif //PARALLAX_MESSAGES_H
