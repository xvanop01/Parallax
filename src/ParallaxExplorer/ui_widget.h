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
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QTabWidget *tabWidget;
    QWidget *tabExplorer;
    QTreeWidget *structureView;
    QLabel *structureTitle;
    QScrollArea *scrollExplorer;
    QWidget *scrollExplorerArea;
    QWidget *tabDashboard;
    QScrollArea *scrollDashboard;
    QWidget *scrollDashboardArea;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(800, 600);
        Widget->setMinimumSize(QSize(800, 600));
        tabWidget = new QTabWidget(Widget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 800, 600));
        tabExplorer = new QWidget();
        tabExplorer->setObjectName(QStringLiteral("tabExplorer"));
        structureView = new QTreeWidget(tabExplorer);
        structureView->setObjectName(QStringLiteral("structureView"));
        structureView->setGeometry(QRect(0, 25, 200, 544));
        structureTitle = new QLabel(tabExplorer);
        structureTitle->setObjectName(QStringLiteral("structureTitle"));
        structureTitle->setGeometry(QRect(0, 0, 200, 25));
        structureTitle->setAlignment(Qt::AlignCenter);
        scrollExplorer = new QScrollArea(tabExplorer);
        scrollExplorer->setObjectName(QStringLiteral("scrollExplorer"));
        scrollExplorer->setGeometry(QRect(200, 0, 596, 569));
        scrollExplorer->setWidgetResizable(true);
        scrollExplorerArea = new QWidget();
        scrollExplorerArea->setObjectName(QStringLiteral("scrollExplorerArea"));
        scrollExplorerArea->setGeometry(QRect(0, 0, 594, 567));
        scrollExplorer->setWidget(scrollExplorerArea);
        tabWidget->addTab(tabExplorer, QString());
        tabDashboard = new QWidget();
        tabDashboard->setObjectName(QStringLiteral("tabDashboard"));
        tabDashboard->setMinimumSize(QSize(796, 569));
        scrollDashboard = new QScrollArea(tabDashboard);
        scrollDashboard->setObjectName(QStringLiteral("scrollDashboard"));
        scrollDashboard->setGeometry(QRect(0, 0, 796, 569));
        scrollDashboard->setWidgetResizable(true);
        scrollDashboardArea = new QWidget();
        scrollDashboardArea->setObjectName(QStringLiteral("scrollDashboardArea"));
        scrollDashboardArea->setGeometry(QRect(0, 0, 794, 567));
        scrollDashboard->setWidget(scrollDashboardArea);
        tabWidget->addTab(tabDashboard, QString());

        retranslateUi(Widget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = structureView->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("Widget", "Topic", Q_NULLPTR));
        structureTitle->setText(QApplication::translate("Widget", "Structure", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabExplorer), QApplication::translate("Widget", "Explorer", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabDashboard), QApplication::translate("Widget", "Dashboard", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
