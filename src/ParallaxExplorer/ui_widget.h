/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QTabWidget *MainWidget;
    QWidget *tabExplorer;
    QTreeWidget *structureView;
    QLabel *structureTitle;
    QScrollArea *scrollExplorer;
    QWidget *scrollExplorerArea;
    QListWidget *messageBox;
    QPushButton *RefreshButton;
    QPushButton *SendButton;
    QLineEdit *showTopic;
    QPushButton *topicButton;
    QLineEdit *sendMessageInput;
    QWidget *tabDashboard;
    QLineEdit *dashboardWatch1;
    QPushButton *dashboardButton1;
    QLineEdit *dashboardWatch2;
    QLineEdit *dashboardWatch3;
    QPushButton *dashboardButton2;
    QPushButton *dashboardButton3;
    QListWidget *dashboardView1;
    QListWidget *dashboardView2;
    QListWidget *dashboardView3;
    QPushButton *dashboardButton5;
    QListWidget *dashboardView4;
    QLineEdit *dashboardWatch5;
    QPushButton *dashboardButton4;
    QListWidget *dashboardView5;
    QListWidget *dashboardView6;
    QPushButton *dashboardButton6;
    QLineEdit *dashboardWatch4;
    QLineEdit *dashboardWatch6;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *id1;
    QLineEdit *id3;
    QLineEdit *id4;
    QLineEdit *id6;
    QLineEdit *id2;
    QLineEdit *id5;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(800, 600);
        Widget->setMinimumSize(QSize(800, 600));
        MainWidget = new QTabWidget(Widget);
        MainWidget->setObjectName(QStringLiteral("MainWidget"));
        MainWidget->setGeometry(QRect(0, 0, 800, 600));
        tabExplorer = new QWidget();
        tabExplorer->setObjectName(QStringLiteral("tabExplorer"));
        structureView = new QTreeWidget(tabExplorer);
        structureView->headerItem()->setText(1, QString());
        structureView->setObjectName(QStringLiteral("structureView"));
        structureView->setGeometry(QRect(0, 25, 200, 544));
        structureTitle = new QLabel(tabExplorer);
        structureTitle->setObjectName(QStringLiteral("structureTitle"));
        structureTitle->setGeometry(QRect(0, 0, 200, 25));
        structureTitle->setAlignment(Qt::AlignCenter);
        scrollExplorer = new QScrollArea(tabExplorer);
        scrollExplorer->setObjectName(QStringLiteral("scrollExplorer"));
        scrollExplorer->setGeometry(QRect(200, 25, 596, 516));
        scrollExplorer->setFrameShape(QFrame::StyledPanel);
        scrollExplorer->setWidgetResizable(true);
        scrollExplorerArea = new QWidget();
        scrollExplorerArea->setObjectName(QStringLiteral("scrollExplorerArea"));
        scrollExplorerArea->setGeometry(QRect(0, 0, 594, 514));
        messageBox = new QListWidget(scrollExplorerArea);
        messageBox->setObjectName(QStringLiteral("messageBox"));
        messageBox->setGeometry(QRect(0, 0, 596, 513));
        scrollExplorer->setWidget(scrollExplorerArea);
        RefreshButton = new QPushButton(tabExplorer);
        RefreshButton->setObjectName(QStringLiteral("RefreshButton"));
        RefreshButton->setGeometry(QRect(100, 25, 100, 22));
        SendButton = new QPushButton(tabExplorer);
        SendButton->setObjectName(QStringLiteral("SendButton"));
        SendButton->setGeometry(QRect(696, 540, 100, 29));
        showTopic = new QLineEdit(tabExplorer);
        showTopic->setObjectName(QStringLiteral("showTopic"));
        showTopic->setGeometry(QRect(200, 0, 496, 25));
        topicButton = new QPushButton(tabExplorer);
        topicButton->setObjectName(QStringLiteral("topicButton"));
        topicButton->setGeometry(QRect(696, 0, 100, 25));
        sendMessageInput = new QLineEdit(tabExplorer);
        sendMessageInput->setObjectName(QStringLiteral("sendMessageInput"));
        sendMessageInput->setGeometry(QRect(200, 540, 496, 29));
        MainWidget->addTab(tabExplorer, QString());
        tabDashboard = new QWidget();
        tabDashboard->setObjectName(QStringLiteral("tabDashboard"));
        tabDashboard->setMinimumSize(QSize(796, 569));
        dashboardWatch1 = new QLineEdit(tabDashboard);
        dashboardWatch1->setObjectName(QStringLiteral("dashboardWatch1"));
        dashboardWatch1->setGeometry(QRect(0, 0, 180, 25));
        dashboardButton1 = new QPushButton(tabDashboard);
        dashboardButton1->setObjectName(QStringLiteral("dashboardButton1"));
        dashboardButton1->setGeometry(QRect(180, 0, 80, 25));
        dashboardWatch2 = new QLineEdit(tabDashboard);
        dashboardWatch2->setObjectName(QStringLiteral("dashboardWatch2"));
        dashboardWatch2->setGeometry(QRect(260, 0, 200, 25));
        dashboardWatch3 = new QLineEdit(tabDashboard);
        dashboardWatch3->setObjectName(QStringLiteral("dashboardWatch3"));
        dashboardWatch3->setGeometry(QRect(540, 0, 180, 25));
        dashboardButton2 = new QPushButton(tabDashboard);
        dashboardButton2->setObjectName(QStringLiteral("dashboardButton2"));
        dashboardButton2->setGeometry(QRect(460, 0, 80, 25));
        dashboardButton3 = new QPushButton(tabDashboard);
        dashboardButton3->setObjectName(QStringLiteral("dashboardButton3"));
        dashboardButton3->setGeometry(QRect(720, 0, 80, 25));
        dashboardView1 = new QListWidget(tabDashboard);
        dashboardView1->setObjectName(QStringLiteral("dashboardView1"));
        dashboardView1->setGeometry(QRect(0, 50, 260, 235));
        dashboardView2 = new QListWidget(tabDashboard);
        dashboardView2->setObjectName(QStringLiteral("dashboardView2"));
        dashboardView2->setGeometry(QRect(260, 50, 280, 235));
        dashboardView3 = new QListWidget(tabDashboard);
        dashboardView3->setObjectName(QStringLiteral("dashboardView3"));
        dashboardView3->setGeometry(QRect(540, 50, 260, 235));
        dashboardButton5 = new QPushButton(tabDashboard);
        dashboardButton5->setObjectName(QStringLiteral("dashboardButton5"));
        dashboardButton5->setGeometry(QRect(460, 285, 80, 25));
        dashboardView4 = new QListWidget(tabDashboard);
        dashboardView4->setObjectName(QStringLiteral("dashboardView4"));
        dashboardView4->setGeometry(QRect(0, 335, 260, 235));
        dashboardWatch5 = new QLineEdit(tabDashboard);
        dashboardWatch5->setObjectName(QStringLiteral("dashboardWatch5"));
        dashboardWatch5->setGeometry(QRect(260, 285, 200, 25));
        dashboardButton4 = new QPushButton(tabDashboard);
        dashboardButton4->setObjectName(QStringLiteral("dashboardButton4"));
        dashboardButton4->setGeometry(QRect(180, 285, 80, 25));
        dashboardView5 = new QListWidget(tabDashboard);
        dashboardView5->setObjectName(QStringLiteral("dashboardView5"));
        dashboardView5->setGeometry(QRect(260, 335, 280, 235));
        dashboardView6 = new QListWidget(tabDashboard);
        dashboardView6->setObjectName(QStringLiteral("dashboardView6"));
        dashboardView6->setGeometry(QRect(540, 335, 260, 235));
        dashboardButton6 = new QPushButton(tabDashboard);
        dashboardButton6->setObjectName(QStringLiteral("dashboardButton6"));
        dashboardButton6->setGeometry(QRect(720, 285, 80, 25));
        dashboardWatch4 = new QLineEdit(tabDashboard);
        dashboardWatch4->setObjectName(QStringLiteral("dashboardWatch4"));
        dashboardWatch4->setGeometry(QRect(0, 285, 180, 25));
        dashboardWatch6 = new QLineEdit(tabDashboard);
        dashboardWatch6->setObjectName(QStringLiteral("dashboardWatch6"));
        dashboardWatch6->setGeometry(QRect(540, 285, 180, 25));
        label = new QLabel(tabDashboard);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 25, 50, 25));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(tabDashboard);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(260, 25, 50, 25));
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(tabDashboard);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(540, 25, 50, 25));
        label_3->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(tabDashboard);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(0, 310, 50, 25));
        label_4->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(tabDashboard);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(540, 310, 50, 25));
        label_5->setAlignment(Qt::AlignCenter);
        label_6 = new QLabel(tabDashboard);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(260, 310, 50, 25));
        label_6->setAlignment(Qt::AlignCenter);
        id1 = new QLineEdit(tabDashboard);
        id1->setObjectName(QStringLiteral("id1"));
        id1->setGeometry(QRect(50, 25, 210, 25));
        id3 = new QLineEdit(tabDashboard);
        id3->setObjectName(QStringLiteral("id3"));
        id3->setGeometry(QRect(590, 25, 210, 25));
        id4 = new QLineEdit(tabDashboard);
        id4->setObjectName(QStringLiteral("id4"));
        id4->setGeometry(QRect(50, 310, 210, 25));
        id6 = new QLineEdit(tabDashboard);
        id6->setObjectName(QStringLiteral("id6"));
        id6->setGeometry(QRect(590, 310, 210, 25));
        id2 = new QLineEdit(tabDashboard);
        id2->setObjectName(QStringLiteral("id2"));
        id2->setGeometry(QRect(310, 25, 230, 25));
        id5 = new QLineEdit(tabDashboard);
        id5->setObjectName(QStringLiteral("id5"));
        id5->setGeometry(QRect(310, 310, 230, 25));
        MainWidget->addTab(tabDashboard, QString());

        retranslateUi(Widget);

        MainWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = structureView->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("Widget", "Topic", Q_NULLPTR));
        structureTitle->setText(QApplication::translate("Widget", "Structure", Q_NULLPTR));
        RefreshButton->setText(QApplication::translate("Widget", "Refresh", Q_NULLPTR));
        SendButton->setText(QApplication::translate("Widget", "Send", Q_NULLPTR));
        topicButton->setText(QApplication::translate("Widget", "Show Topic", Q_NULLPTR));
        MainWidget->setTabText(MainWidget->indexOf(tabExplorer), QApplication::translate("Widget", "Explorer", Q_NULLPTR));
        dashboardButton1->setText(QApplication::translate("Widget", "Set", Q_NULLPTR));
        dashboardButton2->setText(QApplication::translate("Widget", "Set", Q_NULLPTR));
        dashboardButton3->setText(QApplication::translate("Widget", "Set", Q_NULLPTR));
        dashboardButton5->setText(QApplication::translate("Widget", "Set", Q_NULLPTR));
        dashboardButton4->setText(QApplication::translate("Widget", "Set", Q_NULLPTR));
        dashboardButton6->setText(QApplication::translate("Widget", "Set", Q_NULLPTR));
        label->setText(QApplication::translate("Widget", "ID:", Q_NULLPTR));
        label_2->setText(QApplication::translate("Widget", "ID:", Q_NULLPTR));
        label_3->setText(QApplication::translate("Widget", "ID:", Q_NULLPTR));
        label_4->setText(QApplication::translate("Widget", "ID:", Q_NULLPTR));
        label_5->setText(QApplication::translate("Widget", "ID:", Q_NULLPTR));
        label_6->setText(QApplication::translate("Widget", "ID:", Q_NULLPTR));
        MainWidget->setTabText(MainWidget->indexOf(tabDashboard), QApplication::translate("Widget", "Dashboard", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
