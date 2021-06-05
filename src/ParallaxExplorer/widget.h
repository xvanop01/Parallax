/**
 * @brief Parallax application Widhet header file
 * Header file for functions which are handling signals from UI
 * @author xjurke02
 * @author xvanop01
 */
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTreeWidgetItem>
#include <QTimer>
#include <QListWidget>
#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <fstream>
#include "mqttMsgStruct/Messages.h"
#include "mqttMsgStruct/Memory.h"
#include "mqtt/async_client.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    /**
    * @brief Constructor
    */
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    /**
    * @brief Handler for refresh button from tree view
    */
    void refreshTopicTree();
    /**
    * @brief Show topic
    */
    void showTopic();
    /**
    * @brief Handler for send button
    */
    void sendMsg();
    /**
    * @brief Periodical function for refresh data
    */
    void updateData();
    /**
    * @brief Topic refresh
    */
    void refresh();
    /**
    * @brief Handler for dashboard widgets
    */
    void addDashboardWatch();
    /**
    * @param dashboards QListWidgets showing messages for all dashboards
    * @param ids Id filter
    * @brief Periodical function for dashboard refresh
    */
    void refreshDashboard(std::vector<QListWidget *> dashboards, std::vector<QLineEdit *> ids);
    /**
     * @brief sendDashboard Hanndle sending buttons in dashboard
     */
    void sendDashboard();
    /**
     * @brief Save file into working directory
     * @param topic Where will be file saved
     * @param msg Message with file
     */
    void saveFile(std::string topic, std::string msg);
private:
    Ui::Widget *ui;
    explorer::Messages* messages;
    explorer::Memory* mem;
    mqtt::async_client* client;
    std::string lastTopic;
    std::vector<std::string> watch;
    std::vector<explorer::Memory*> dashMem;
};

#endif // WIDGET_H
