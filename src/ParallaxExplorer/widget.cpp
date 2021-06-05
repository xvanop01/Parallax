/**
 * @brief Parallax application Widget Functions 
 * Functions for handling signals from UI
 * @author xjurke02
 * @author xvanop01
 */
#include "widget.h"
#include "ui_widget.h"

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

void Widget::saveFile(std::string topic, std::string msg) {
    explorer::Messages::saveFile(topic, msg);
}

void Widget::refresh() {
    std::vector<std::vector<std::string>> msgs = messages->getMessages(explorer::Messages::parseTopic(lastTopic));
    for (auto & v : msgs) {
        for (int i = v.size(); i > 1; i--) {
            if (mem->isNew(v[0], v[i-1])) {
                if (mem->isMyMsg(v[0], v[i-1])) {
                    auto newLabel = new QListWidgetItem(QString::fromStdString(v[i-1]));
                    ui->messageBox->addItem(newLabel);
                    ui->messageBox->item(ui->messageBox->count()-1)->setForeground(Qt::red);
                } else {
                    ui->messageBox->addItem(QString::fromStdString(v[i-1]));
                }
                mem->saveNew(v[0], v[i-1]);
            }
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
                if (mem->isMyMsg(v[0], v[i-1])) {
                    auto newLabel = new QListWidgetItem(QString::fromStdString(v[i-1]));
                    lists[buttonNumber]->addItem(newLabel);
                    lists[buttonNumber]->item(lists[buttonNumber]->count()-1)->setForeground(Qt::red);
                } else {
                    lists[buttonNumber]->addItem(QString::fromStdString(v[i-1]));
                }
                dashMem[buttonNumber]->saveNew(v[0], v[i-1]);
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
                        if (mem->isMyMsg(v[0], v[j-1])) {
                            auto newLabel = new QListWidgetItem(QString::fromStdString(v[j-1]));
                            dashboards[i]->addItem(newLabel);
                            dashboards[i]->item(dashboards[i]->count()-1)->setForeground(Qt::red);
                        } else {
                            dashboards[i]->addItem(QString::fromStdString(v[j-1]));
                        }
                    }
                    dashMem[i]->saveNew(v[0], v[j-1]);
                }
            }
        }
        i++;
    }
}

void Widget::sendDashboard()
{
    int buttonNumber = ((QPushButton*)QObject::sender())->property("id").toInt();
    std::vector<QLineEdit*> topics;
    topics.push_back(ui->dashboardWatch1);
    topics.push_back(ui->dashboardWatch2);
    topics.push_back(ui->dashboardWatch3);
    topics.push_back(ui->dashboardWatch4);
    topics.push_back(ui->dashboardWatch5);
    topics.push_back(ui->dashboardWatch6);
    std::vector<QLineEdit*> msgs;
    msgs.push_back(ui->dashboardSend1);
    msgs.push_back(ui->dashboardSend2);
    msgs.push_back(ui->dashboardSend3);
    msgs.push_back(ui->dashboardSend4);
    msgs.push_back(ui->dashboardSend5);
    msgs.push_back(ui->dashboardSend6);
    std::vector<QPushButton*> topicButtons;
    topicButtons.push_back(ui->dashboardButton1);
    topicButtons.push_back(ui->dashboardButton2);
    topicButtons.push_back(ui->dashboardButton3);
    topicButtons.push_back(ui->dashboardButton4);
    topicButtons.push_back(ui->dashboardButton5);
    topicButtons.push_back(ui->dashboardButton6);
    std::string tp = topics[buttonNumber]->text().toStdString();
    for (unsigned int i = 0; i < tp.size(); i++) {
        if (tp[i] == '#') {
            return;
        }
    }
    if (messages->getMessages(explorer::Messages::parseTopic(tp)).size() < 2) {
        std::string msg = msgs[buttonNumber]->text().toStdString();
        mem->saveMyMsg(tp, msg);
        messages->sendMsg(tp, msg, client);
        msgs[buttonNumber]->setText("");
    }
    topicButtons[buttonNumber]->click();
}

void Widget::showTopic() {
    ui->messageBox->clear();
    std::string top = ui->showTopic->text().toStdString();
    std::vector<std::vector<std::string>> msgs = messages->getMessages(explorer::Messages::parseTopic(top));
    for (auto & v : msgs) {
        for (int i = v.size(); i > 1; i--) {
            if (mem->isMyMsg(v[0], v[i-1])) {
                auto newLabel = new QListWidgetItem(QString::fromStdString(v[i-1]));
                ui->messageBox->addItem(newLabel);
                ui->messageBox->item(ui->messageBox->count()-1)->setForeground(Qt::red);
            } else {
                ui->messageBox->addItem(QString::fromStdString(v[i-1]));
            }
            mem->saveNew(v[0], v[i-1]);
        }
    }
    ui->messageBox->scrollToBottom();
    lastTopic = top;
}

void Widget::sendMsg() {
    std::string tp = ui->showTopic->text().toStdString();
    for (unsigned int i = 0; i < tp.size(); i++) {
        if (tp[i] == '#') {
            return;
        }
    }
    if (messages->getMessages(explorer::Messages::parseTopic(ui->showTopic->text().toStdString())).size() < 2) {
        std::string msg = ui->sendMessageInput->text().toStdString();
        mem->saveMyMsg(tp, msg);
        messages->sendMsg(tp, msg, client);
        ui->sendMessageInput->setText("");
    }
    ui->topicButton->click();
}

void Widget::refreshTopicTree() {
    explorer::Messages::deleteChild(ui->structureView->invisibleRootItem());
    explorer::Messages::createChild(messages->topics, nullptr, ui);
}

void Widget::topicTreeItemClicked(QTreeWidgetItem *item, int column)
{
    QTreeWidgetItem *target = item;
    QString fullTopic = item->text(column);
    target = item->parent();
    while (target != NULL) {
        fullTopic = target->text(column) + fullTopic;
        target = target->parent();
    }
    ui->showTopic->setText(fullTopic);
    showTopic();
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    client = new mqtt::async_client(SERVER_ADDRESS, "", mqtt::create_options(MQTTVERSION_5));
    connect(ui->RefreshButton, &QPushButton::released, this, &Widget::refreshTopicTree);
    connect(ui->structureView, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            this, SLOT(topicTreeItemClicked(QTreeWidgetItem*,int)));
    try {
        messages = new explorer::Messages(50, client);
    } catch (const mqtt::exception& e) {
            std::cerr << "Can't connect to broker!\n" << e.what() << "\n";
    }
    mem = new explorer::Memory();
    for (int i = 0; i < 6; i++) {
        dashMem.push_back(new explorer::Memory());
    }
    ui->structureView->setColumnCount(1);
    connect(ui->topicButton, &QPushButton::released, this, &Widget::showTopic);
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
    ui->DSButton1->setProperty("id", 0);
    ui->DSButton2->setProperty("id", 1);
    ui->DSButton3->setProperty("id", 2);
    ui->DSButton4->setProperty("id", 3);
    ui->DSButton5->setProperty("id", 4);
    ui->DSButton6->setProperty("id", 5);
    connect(ui->DSButton1, &QPushButton::released, this, &Widget::sendDashboard);
    connect(ui->DSButton2, &QPushButton::released, this, &Widget::sendDashboard);
    connect(ui->DSButton3, &QPushButton::released, this, &Widget::sendDashboard);
    connect(ui->DSButton4, &QPushButton::released, this, &Widget::sendDashboard);
    connect(ui->DSButton5, &QPushButton::released, this, &Widget::sendDashboard);
    connect(ui->DSButton6, &QPushButton::released, this, &Widget::sendDashboard);
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::updateData);
    timer->start(1000);
}

Widget::~Widget()
{
    delete ui;
    delete messages;
    delete client;
    delete mem;
}
