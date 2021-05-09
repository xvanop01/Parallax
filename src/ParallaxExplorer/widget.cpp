#include "widget.h"
#include "ui_widget.h"
#include "mqttMsgStruct/Messages.h"
#include "mqtt/async_client.h"

explorer::Messages* messages;
mqtt::async_client* client;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    client = new mqtt::async_client(SERVER_ADDRESS, "", mqtt::create_options(MQTTVERSION_5));
    try {
        messages = new explorer::Messages(50, client);
    } catch (const mqtt::exception& e) {
            std::cerr << "Can't connect to broker!\n" << e.what() << "\n";
    }
    ui->structureView->setColumnCount(1);
    while (messages->topics->subtopic.empty()) {

    }
    while (messages->topics->subtopic[0]->subtopic.empty()) {

    }
    explorer::Messages::createChild(messages->topics, nullptr, ui);
}

Widget::~Widget()
{
    delete ui;
    delete messages;
    delete client;
}
