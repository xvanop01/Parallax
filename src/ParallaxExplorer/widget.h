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
    void handleButton();
    /**
    * @brief Show topic
    */
    void addOnClick();
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
private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
