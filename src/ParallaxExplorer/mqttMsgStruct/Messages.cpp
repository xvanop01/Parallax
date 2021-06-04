/**
 * @brief Parallax application Messages Administration
 * Functions which administrate messages (saving, getting, etc.)
 * @author xvanop01
 */

#include "mqttMsgStruct/Messages.h"

explorer::Messages::Messages(int bufferSize, mqtt::async_client* client) {
    this->maxMsgs = bufferSize;
    this->client = client;
    auto connectOptions = mqtt::connect_options_builder()
            .mqtt_version(5)
            .properties({{mqtt::property::SESSION_EXPIRY_INTERVAL, 100}})
            .keep_alive_interval(std::chrono::minutes(1))
            .finalize();
    this->client->set_message_callback([&](mqtt::const_message_ptr msg) {
        this->saveMsg(this->parseTopic(msg->get_topic()), msg->get_payload_str());
    });
    mqtt::topic topic {*(this->client), "#", QOS};
    auto connection = this->client->connect(connectOptions);
    connection->wait();
    auto subscribeOptions = mqtt::subscribe_options(!SEND_MY_MSGS);
    topic.subscribe(subscribeOptions)->wait();
    this->topics = new struct topic();
}

explorer::Messages::~Messages() {
    this->client->disconnect()->wait();
    this->deleteTopics(this->topics);
}

void explorer::Messages::saveMsg(std::vector<std::string> parsedTopics, std::string msg) {
    explorer::topic* targetTopic = this->topics;
    bool found;
    while (!parsedTopics.empty()) {
        found = false;
        for (auto & t : targetTopic->subtopic) {
            if (t->name == targetTopic->name + parsedTopics[0]) {
                found = true;
                targetTopic = t;
                parsedTopics.erase(parsedTopics.begin());
                break;
            }
        }
        if (!found) {
            auto tmp = new struct topic();
            tmp->name = targetTopic->name + parsedTopics[0];
            parsedTopics.erase(parsedTopics.begin());
            targetTopic->subtopic.push_back(tmp);
            targetTopic = tmp;
        }
    }
    targetTopic->messages.insert(targetTopic->messages.begin(), msg);
    if (targetTopic->messages.size() > (unsigned)this->maxMsgs) {
        targetTopic->messages.pop_back();
    }
}

void explorer::Messages::deleteTopics(explorer::topic* target) {
    if (target != nullptr) {
        for (auto & topic : target->subtopic) {
            this->deleteTopics(topic);
        }
        delete target;
    }
}

std::vector<std::string> explorer::Messages::parseTopic(std::string topic) {
    std::vector<std::string> parsedTopics;
    std::string parsed = "";
    parsed = topic.substr(0, topic.find("/", 1));
    if (parsed.empty()) {
        parsedTopics.push_back(topic);
    } else {
        parsedTopics.push_back(parsed);
    }
    while (!topic.empty()) {
        parsed = topic.substr(0, topic.find("/", 1));
        topic.erase(0, parsed.length());
        parsed = topic.substr(0, topic.find("/", 1));
        if (parsed.empty()) {
            break;
        }
        parsedTopics.push_back(parsed);
    }
    return parsedTopics;
}

std::vector<std::vector<std::string>> explorer::Messages::getMessages(std::vector<std::string> parsedTopics) {
    std::vector<std::vector<std::string>> returnVector = {};
    explorer::topic* targetTopic = this->topics;
    bool found;
    while (!parsedTopics.empty()) {
        found = false;
        if (parsedTopics[0] == "#" || parsedTopics[0] == "/#") {
            break;
        }
        for (auto & t : targetTopic->subtopic) {
            if (t->name == targetTopic->name + parsedTopics[0]) {
                found = true;
                targetTopic = t;
                parsedTopics.erase(parsedTopics.begin());
                break;
            }
        }
        if (!found) {
            auto tmp = new struct topic();
            tmp->name = targetTopic->name + parsedTopics[0];
            tmp->subtopic = {};
            parsedTopics.erase(parsedTopics.begin());
            targetTopic->subtopic.push_back(tmp);
            targetTopic = tmp;
        }
    }
    std::vector<std::string> empty = {};
    if (parsedTopics[0] == "#" || parsedTopics[0] == "/#") {
        std::vector<explorer::topic*> buffer = {};
        buffer.push_back(targetTopic);
        while (!buffer.empty()) {
            targetTopic = buffer[0];
            if (!targetTopic->messages.empty()) {
                empty.push_back(targetTopic->name);
                for (auto & msg : targetTopic->messages) {
                    empty.push_back(msg);
                }
                returnVector.push_back(empty);
                empty = {};
            }
            if (targetTopic->subtopic.size() != 0) {
                for (auto & t : targetTopic->subtopic) {
                    buffer.push_back(t);
                }
            }
            buffer.erase(buffer.begin());
        }
    } else {
        if (!targetTopic->messages.empty()) {
            empty.push_back(targetTopic->name);
            for (auto & msg : targetTopic->messages) {
                empty.push_back(msg);
            }
            returnVector.push_back(empty);
        }
    }
    return returnVector;
}

void explorer::Messages::createChild(struct topic *ref, QTreeWidgetItem *target, Ui::Widget *ui) {
    QTreeWidgetItem *newItem;
    for (auto & top : ref->subtopic) {
        if (target == nullptr) {
            newItem = new QTreeWidgetItem(ui->structureView);
            ui->structureView->addTopLevelItem(newItem);
        } else {
            newItem = new QTreeWidgetItem(target);
            target->addChild(newItem);
        }
        std::vector<std::string> topicName = explorer::Messages::parseTopic(top->name);
        newItem->setText(0, QString::fromStdString(topicName[topicName.size()-1]));
        newItem->setExpanded(true);
        createChild(top, newItem, ui);
    }
}

void explorer::Messages::deleteChild(QTreeWidgetItem *target){
    int childCount = target->childCount();
    for (int i = 0; childCount > i; i++) {
        QTreeWidgetItem *child = target->child(i);
        target->removeChild(child);
        deleteChild(target);
    }
}

void explorer::Messages::sendMsg(std::string top, std::string msg, mqtt::async_client *client) {
    mqtt::topic topic{*client, top, QOS};
    topic.publish(msg)->wait();
}

bool explorer::Messages::isPlainText(std::string msg) {
    for (auto & ch : msg) {
        if (ch < ' ' || ch > '~') {
            return false;
        }
    }
    return true;
}

void explorer::Messages::saveFile(std::string topic, std::string msg) {
    std::ofstream f;
    f.open(topic + "output");
    f << msg;
    f.close();
}

