#include "pyqt5_ros2.h"
#include "./ui_pyqt5_ros2.h"

pyQt5_ROS2::pyQt5_ROS2(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::pyQt5_ROS2)
{
    ui->setupUi(this);
}

pyQt5_ROS2::~pyQt5_ROS2()
{
    delete ui;
}

