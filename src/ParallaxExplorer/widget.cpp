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
                QPixmap img;
                if (img.loadFromData((const uchar*)&(v[i-1][0]), (uint)v[i-1].size())) {
                    int imgExist = -1;
                    for (int k = 0; k < images.size(); k++) {
                        if (images[k] == v[i-1]) {
                            imgExist = k;
                            break;
                        }
                    }
                    QListWidgetItem* newLabel;
                    if (imgExist >= 0) {
                        newLabel = new QListWidgetItem(QString::fromStdString(
                                                                "Show Image " + std::to_string(imgExist)));
                    } else {
                        newLabel = new QListWidgetItem(QString::fromStdString(
                                                                "Show Image " + std::to_string(images.size())));
                        images.push_back(v[i-1]);
                    }
                    ui->messageBox->addItem(newLabel);
                    ui->messageBox->item(ui->messageBox->count()-1)->setForeground(Qt::blue);
                } else {
                    if (mem->isMyMsg(v[0], v[i-1])) {
                        auto newLabel = new QListWidgetItem(QString::fromStdString(v[i-1]));
                        ui->messageBox->addItem(newLabel);
                        ui->messageBox->item(ui->messageBox->count()-1)->setForeground(Qt::red);
                    } else {
                        ui->messageBox->addItem(QString::fromStdString(v[i-1]));
                    }
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
    lists[buttonNumber]->clear();
    for (auto & v : msgs) {
        for (int i = v.size(); i > 1; i--) {
            if (id.empty() || std::regex_match(v[i-1], regex)) {
                QPixmap img;
                if (img.loadFromData((const uchar*)&(v[i-1][0]), (uint)v[i-1].size())) {
                    int imgExist = -1;
                    for (int k = 0; k < images.size(); k++) {
                        if (images[k] == v[i-1]) {
                            imgExist = k;
                            break;
                        }
                    }
                    QListWidgetItem* newLabel;
                    if (imgExist >= 0) {
                        newLabel = new QListWidgetItem(QString::fromStdString(
                                                                "Show Image " + std::to_string(imgExist)));
                    } else {
                        newLabel = new QListWidgetItem(QString::fromStdString(
                                                                "Show Image " + std::to_string(images.size())));
                        images.push_back(v[i-1]);
                    }
                    lists[buttonNumber]->addItem(newLabel);
                    lists[buttonNumber]->item(lists[buttonNumber]->count()-1)->setForeground(Qt::blue);
                } else {
                    if (mem->isMyMsg(v[0], v[i-1])) {
                        auto newLabel = new QListWidgetItem(QString::fromStdString(v[i-1]));
                        lists[buttonNumber]->addItem(newLabel);
                        lists[buttonNumber]->item(lists[buttonNumber]->count()-1)->setForeground(Qt::red);
                    } else {
                        lists[buttonNumber]->addItem(QString::fromStdString(v[i-1]));
                    }
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
            std::vector<std::vector<std::string>> msgs = messages->getMessages(explorer::Messages::parseTopic(watch[i]));
            std::string id = ids[i]->text().toStdString();
            std::regex regex("^.*\"ID\":\"" + id + "\".*$");
            for (auto & v : msgs) {
                for (int j = v.size(); j > 1; j--) {
                    if ((id.empty() || std::regex_match(v[j-1], regex)) && dashMem[i]->isNew(v[0] ,v[j-1])) {
                        QPixmap img;
                        if (img.loadFromData((const uchar*)&(v[j-1][0]), (uint)v[j-1].size())) {
                            int imgExist = -1;
                            for (int k = 0; k < images.size(); k++) {
                                if (images[k] == v[j-1]) {
                                    imgExist = k;
                                    break;
                                }
                            }
                            QListWidgetItem* newLabel;
                            if (imgExist >= 0) {
                                newLabel = new QListWidgetItem(QString::fromStdString(
                                                                        "Show Image " + std::to_string(imgExist)));
                            } else {
                                newLabel = new QListWidgetItem(QString::fromStdString(
                                                                        "Show Image " + std::to_string(images.size())));
                                images.push_back(v[j-1]);
                            }
                            dash->addItem(newLabel);
                            dash->item(dash->count()-1)->setForeground(Qt::blue);
                        } else {
                            if (mem->isMyMsg(v[0], v[j-1])) {
                                auto newLabel = new QListWidgetItem(QString::fromStdString(v[j-1]));
                                dash->addItem(newLabel);
                                dash->item(dash->count()-1)->setForeground(Qt::red);
                            } else {
                                dash->addItem(QString::fromStdString(v[j-1]));
                            }
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
            QPixmap img;
            if (img.loadFromData((const uchar*)&(v[i-1][0]), (uint)v[i-1].size())) {
                int imgExist = -1;
                for (int k = 0; k < images.size(); k++) {
                    if (images[k] == v[i-1]) {
                        imgExist = k;
                        break;
                    }
                }
                QListWidgetItem* newLabel;
                if (imgExist >= 0) {
                    newLabel = new QListWidgetItem(QString::fromStdString(
                                                            "Show Image " + std::to_string(imgExist)));
                } else {
                    newLabel = new QListWidgetItem(QString::fromStdString(
                                                            "Show Image " + std::to_string(images.size())));
                    images.push_back(v[i-1]);
                }
                ui->messageBox->addItem(newLabel);
                ui->messageBox->item(ui->messageBox->count()-1)->setForeground(Qt::blue);
            } else {
                if (mem->isMyMsg(v[0], v[i-1])) {
                    auto newLabel = new QListWidgetItem(QString::fromStdString(v[i-1]));
                    ui->messageBox->addItem(newLabel);
                    ui->messageBox->item(ui->messageBox->count()-1)->setForeground(Qt::red);
                } else {
                    ui->messageBox->addItem(QString::fromStdString(v[i-1]));
                }
            }
            mem->saveNew(v[0], v[i-1]);
        }
    }
    ui->messageBox->scrollToBottom();
    lastTopic = top;
}

void Widget::sendMsg() {
    std::string tp = ui->showTopic->text().toStdString();
    if (tp.length() == 0) {
        return;
    }
    for (unsigned int i = 0; i < tp.size(); i++) {
        if (tp[i] == '#') {
            return;
        }
    }
    if (messages->getMessages(explorer::Messages::parseTopic(ui->showTopic->text().toStdString())).size() < 2) {
        if (fileName.count() > 0) {
            QFile file(fileName);
            file.open(QIODevice::ReadOnly);
            QByteArray fileData = file.readAll();
            file.close();
            messages->sendMsg(tp, fileData, client);
            fileName = "";
        } else {
            std::string msg = ui->sendMessageInput->text().toStdString();
            mem->saveMyMsg(tp, msg);
            messages->sendMsg(tp, msg, client);
        }
        ui->sendMessageInput->setText("");
    }
    refreshTopicTree();
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

void Widget::displayImageClicked(QListWidgetItem *item)
{
    if (item->foreground() == Qt::blue) {
        std::string name = item->text().toStdString();
        name = name.substr(11, name.size());
        showImage(images[std::stoi(name)]);
    }
}

void Widget::showImage(std::string msg)
{
    QLabel* img = new QLabel();
    img->setWindowFlags(Qt::Window);
    QPixmap picture;
    picture.loadFromData((const uchar*)&(msg[0]), (uint)msg.size());
    img->setPixmap(picture);
    img->show();
}

void Widget::appendFile()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "/home", tr("All files (*);;Image files (*.jpg, *.png, *.bmp)"));
    ui->sendMessageInput->setText("File: " + fileName);
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
    connect(ui->messageBox, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(displayImageClicked(QListWidgetItem*)));
    try {
        messages = new explorer::Messages(50, client);
    } catch (const mqtt::exception& e) {
            std::cerr << "Can't connect to broker!\n" << e.what() << "\n";
    }
    mem = new explorer::Memory();
    for (int i = 0; i < 6; i++) {
        dashMem.push_back(new explorer::Memory());
    }
    fileName = "";
    connect(ui->fileButton, &QPushButton::released, this, &Widget::appendFile);
    ui->structureView->setColumnCount(1);
    connect(ui->topicButton, &QPushButton::released, this, &Widget::showTopic);
    connect(ui->SendButton, &QPushButton::released, this, &Widget::sendMsg);
    client->set_message_callback([&](mqtt::const_message_ptr msg) {
        messages->saveMsg(explorer::Messages::parseTopic(msg->get_topic()), msg->get_payload_str());
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
    connect(ui->dashboardView1, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(displayImageClicked(QListWidgetItem*)));
    connect(ui->dashboardView2, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(displayImageClicked(QListWidgetItem*)));
    connect(ui->dashboardView3, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(displayImageClicked(QListWidgetItem*)));
    connect(ui->dashboardView4, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(displayImageClicked(QListWidgetItem*)));
    connect(ui->dashboardView5, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(displayImageClicked(QListWidgetItem*)));
    connect(ui->dashboardView6, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(displayImageClicked(QListWidgetItem*)));
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
    refreshTopicTree();
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
