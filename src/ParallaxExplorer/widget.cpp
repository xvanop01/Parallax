#include "widget.h"
#include "ui_widget.h"
#include "mqttMsgStruct/Messages.h"
#include "mqtt/async_client.h"

explorer::Messages* messages;
mqtt::async_client* client;
std::string lastTopic;
std::vector<std::string> watch;

void Widget::updateData() {
    if (!lastTopic.empty()) {
        refresh();
    }
    std::vector<QListWidget*> lists;
    lists.push_back(ui->dashboardView1);
    lists.push_back(ui->dashboardView2);
    lists.push_back(ui->dashboardView3);
    lists.push_back(ui->dashboardView4);
    lists.push_back(ui->dashboardView5);
    lists.push_back(ui->dashboardView6);
    std::vector<QLineEdit*> ids;
    ids.push_back(ui->id1);
    ids.push_back(ui->id2);
    ids.push_back(ui->id3);
    ids.push_back(ui->id4);
    ids.push_back(ui->id5);
    ids.push_back(ui->id6);
    refreshDashboard(lists, ids);
}

void Widget::refresh() {
    ui->messageBox->clear();
    std::vector<std::vector<std::string>> msgs = messages->getMessages(explorer::Messages::parseTopic(lastTopic));
    for (auto & v : msgs) {
        ui->messageBox->addItem(QString::fromStdString(v[0]));
        for (int i = v.size(); i > 1; i--) {
            ui->messageBox->addItem(QString::fromStdString(v[i-1]));
        }
    }
}

void Widget::addDashboardWatch() {
    int buttonNumber = ((QPushButton*)QObject::sender())->property("id").toInt();
    std::vector<QListWidget*> lists;
    lists.push_back(ui->dashboardView1);
    lists.push_back(ui->dashboardView2);
    lists.push_back(ui->dashboardView3);
    lists.push_back(ui->dashboardView4);
    lists.push_back(ui->dashboardView5);
    lists.push_back(ui->dashboardView6);
    std::vector<QLineEdit*> ids;
    ids.push_back(ui->id1);
    ids.push_back(ui->id2);
    ids.push_back(ui->id3);
    ids.push_back(ui->id4);
    ids.push_back(ui->id5);
    ids.push_back(ui->id6);
    std::vector<QLineEdit*> topics;
    topics.push_back(ui->dashboardWatch1);
    topics.push_back(ui->dashboardWatch2);
    topics.push_back(ui->dashboardWatch3);
    topics.push_back(ui->dashboardWatch4);
    topics.push_back(ui->dashboardWatch5);
    topics.push_back(ui->dashboardWatch6);
    lists[buttonNumber]->clear();
    std::vector<std::vector<std::string>> msgs = messages->getMessages(explorer::Messages::parseTopic(topics[buttonNumber]->text().toStdString()));
    std::string id = ids[buttonNumber]->text().toStdString();
    std::regex regex("^.*\"ID\":\"" + id + "\".*$");
    for (auto & v : msgs) {
        for (int i = v.size(); i > 1; i--) {
            if (id.empty() || std::regex_match(v[i-1], regex)) {
                lists[buttonNumber]->addItem(QString::fromStdString(v[i-1]));
            }
        }
    }
    watch[buttonNumber] = topics[buttonNumber]->text().toStdString();
}

void Widget::refreshDashboard(std::vector<QListWidget*> dashboards, std::vector<QLineEdit*> ids) {
    int i = 0;
    for (auto & dash : dashboards) {
        if (!(watch[i]).empty()) {
            dash->clear();
            std::vector<std::vector<std::string>> msgs = messages->getMessages(explorer::Messages::parseTopic(watch[i]));
            std::string id = ids[i]->text().toStdString();
            std::regex regex("^.*\"ID\":\"" + id + "\".*$");
            for (auto & v : msgs) {
                for (int j = v.size(); j > 1; j--) {
                    if (id.empty() || std::regex_match(v[j-1], regex)) {
                        dash->addItem(QString::fromStdString(v[j-1]));
                    }
                }
            }
        }
        i++;
    }
}

void Widget::addOnClick() {
    ui->messageBox->clear();
    std::vector<std::vector<std::string>> msgs = messages->getMessages(explorer::Messages::parseTopic(ui->showTopic->text().toStdString()));
    for (auto & v : msgs) {
        ui->messageBox->addItem(QString::fromStdString(v[0]));
        for (int i = v.size(); i > 1; i--) {
            ui->messageBox->addItem(QString::fromStdString(v[i-1]));
        }
    }
    ui->messageBox->scrollToBottom();
    lastTopic = ui->showTopic->text().toStdString();
}

void Widget::sendMsg() {
    std::string tp = ui->showTopic->text().toStdString();
    for (unsigned int i = 0; i < tp.size(); i++) {
        if (tp[i] == '#') {
            return;
        }
    }
    if (messages->getMessages(explorer::Messages::parseTopic(ui->showTopic->text().toStdString())).size() < 2) {
        messages->sendMsg(tp, ui->sendMessageInput->text().toStdString(), client);
        ui->sendMessageInput->setText("");
    }
    ui->topicButton->click();
}

void Widget::handleButton() {
    explorer::Messages::deleteChild(ui->structureView->invisibleRootItem());
    explorer::Messages::createChild(messages->topics, nullptr, ui);
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    client = new mqtt::async_client(SERVER_ADDRESS, "", mqtt::create_options(MQTTVERSION_5));
    connect(ui->RefreshButton, &QPushButton::released, this, &Widget::handleButton);
    try {
        messages = new explorer::Messages(50, client);
    } catch (const mqtt::exception& e) {
            std::cerr << "Can't connect to broker!\n" << e.what() << "\n";
    }
    ui->structureView->setColumnCount(1);
    connect(ui->topicButton, &QPushButton::released, this, &Widget::addOnClick);
    connect(ui->SendButton, &QPushButton::released, this, &Widget::sendMsg);
    client->set_message_callback([&](mqtt::const_message_ptr msg) {
        messages->saveMsg(explorer::Messages::parseTopic(msg->get_topic()), msg->get_payload_str());
        ui->RefreshButton->click();
    });
    for (int i = 0; i < 6; i++) {
        watch.push_back("");
    }
    ui->dashboardButton1->setProperty("id", 0);
    ui->dashboardButton2->setProperty("id", 1);
    ui->dashboardButton3->setProperty("id", 2);
    ui->dashboardButton4->setProperty("id", 3);
    ui->dashboardButton5->setProperty("id", 4);
    ui->dashboardButton6->setProperty("id", 5);
    connect(ui->dashboardButton1, &QPushButton::released, this, &Widget::addDashboardWatch);
    connect(ui->dashboardButton2, &QPushButton::released, this, &Widget::addDashboardWatch);
    connect(ui->dashboardButton3, &QPushButton::released, this, &Widget::addDashboardWatch);
    connect(ui->dashboardButton4, &QPushButton::released, this, &Widget::addDashboardWatch);
    connect(ui->dashboardButton5, &QPushButton::released, this, &Widget::addDashboardWatch);
    connect(ui->dashboardButton6, &QPushButton::released, this, &Widget::addDashboardWatch);
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::updateData);
    timer->start(1000);
}

Widget::~Widget()
{
    delete ui;
    delete messages;
    delete client;
}