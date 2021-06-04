/**
 * @brief Parallax application Messages memory Implementation File
 * Functions which administrate messages history
 * @author xvanop01
 */

#include "mqttMsgStruct/Memory.h"

explorer::Memory::Memory()
{

}

explorer::Memory::~Memory()
{

}

bool explorer::Memory::isNew(std::string topic, std::string msg)
{
    for (auto & t : this->msgs) {
        if (t[0] == topic) {
            for (unsigned int i = 1; i < t.size(); i++) {
                if (t[i] == msg) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool explorer::Memory::isMyMsg(std::string topic, std::string msg)
{
    for (auto & t : this->myMsgs) {
        if (t[0] == topic) {
            for (unsigned int i = 1; i < t.size(); i++) {
                if (t[i] == msg) {
                    return true;
                }
            }
        }
    }
    return false;
}

void explorer::Memory::saveNew(std::string topic, std::string msg)
{
    if (this->isNew(topic, msg)) {
        for (auto & t : this->msgs) {
            if (t[0] == topic) {
                t.push_back(msg);
                return;
            }
        }
        std::vector<std::string> newTopic;
        newTopic.push_back(topic);
        newTopic.push_back(msg);
        this->msgs.push_back(newTopic);
    }
}

void explorer::Memory::saveMyMsg(std::string topic, std::string msg)
{
    if (this->isNew(topic, msg)) {
        for (auto & t : this->myMsgs) {
            if (t[0] == topic) {
                t.push_back(msg);
                this->saveNew(topic, msg);
                return;
            }
        }
        std::vector<std::string> newTopic;
        newTopic.push_back(topic);
        newTopic.push_back(msg);
        this->myMsgs.push_back(newTopic);
        this->saveNew(topic, msg);
    }
}
