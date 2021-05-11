//
// Created by xvanop01 on 8. 5. 2021.
//

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

namespace explorer {
    struct topic {
        std::string name;
        std::vector<struct topic*> subtopic;
        std::vector<std::string> messages;
    };

    class Messages {
    private:
        int maxMsgs;
        mqtt::async_client* client;
        void deleteTopics(explorer::topic* target);
    public:
        struct topic* topics;
        explicit Messages(int bufferSize, mqtt::async_client* client);
        ~Messages();
        void saveMsg(std::vector<std::string> parsedTopics, std::string msg);
        static std::vector<std::string> parseTopic(std::string topic);
        std::vector<std::vector<std::string>> getMessages(std::vector<std::string> parsedTopics);
        static void createChild(struct topic *ref, QTreeWidgetItem *target, Ui::Widget* ui);
        static void deleteChild(QTreeWidgetItem *target);
        void sendMsg(std::string top, std::string msg, mqtt::async_client* client);
        void saveAll(struct topic *target);
    };
}


#endif //PARALLAX_MESSAGES_H
