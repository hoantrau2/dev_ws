/********************************************************************************
** Form generated from reading UI file 'pyqt5_ros2.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PYQT5_ROS2_H
#define UI_PYQT5_ROS2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pyQt5_ROS2
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *pyQt5_ROS2)
    {
        if (pyQt5_ROS2->objectName().isEmpty())
            pyQt5_ROS2->setObjectName(QString::fromUtf8("pyQt5_ROS2"));
        pyQt5_ROS2->resize(800, 600);
        centralwidget = new QWidget(pyQt5_ROS2);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pyQt5_ROS2->setCentralWidget(centralwidget);
        menubar = new QMenuBar(pyQt5_ROS2);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        pyQt5_ROS2->setMenuBar(menubar);
        statusbar = new QStatusBar(pyQt5_ROS2);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        pyQt5_ROS2->setStatusBar(statusbar);

        retranslateUi(pyQt5_ROS2);

        QMetaObject::connectSlotsByName(pyQt5_ROS2);
    } // setupUi

    void retranslateUi(QMainWindow *pyQt5_ROS2)
    {
        pyQt5_ROS2->setWindowTitle(QCoreApplication::translate("pyQt5_ROS2", "pyQt5_ROS2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pyQt5_ROS2: public Ui_pyQt5_ROS2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PYQT5_ROS2_H
