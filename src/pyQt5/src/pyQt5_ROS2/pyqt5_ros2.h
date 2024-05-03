#ifndef PYQT5_ROS2_H
#define PYQT5_ROS2_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class pyQt5_ROS2; }
QT_END_NAMESPACE

class pyQt5_ROS2 : public QMainWindow
{
    Q_OBJECT

public:
    pyQt5_ROS2(QWidget *parent = nullptr);
    ~pyQt5_ROS2();

private:
    Ui::pyQt5_ROS2 *ui;
};
#endif // PYQT5_ROS2_H
