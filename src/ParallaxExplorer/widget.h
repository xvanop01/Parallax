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
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void handleButton();
    void addOnClick();
    void sendMsg();
    void updateData();
    void refresh();
    void saveAllButton();
    void addDashboardWatch();
    void refreshDashboard(std::vector<QListWidget *> dashboards, std::vector<QLineEdit *> ids);
private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
