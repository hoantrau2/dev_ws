#include "pyqt5_ros2.h"
#include <QApplication>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    pyQt5_ROS2 w;
    w.show();
    return a.exec();
}
