#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    qDebug() << "=== Application started ===";
    
    QApplication app(argc, argv);
    
    qDebug() << "QApplication created";
    
    MainWindow window;
    
    qDebug() << "MainWindow created";
    
    window.show();
    window.raise();
    window.activateWindow();
    
    qDebug() << "Window shown and raised";
    qDebug() << "Window is visible:" << window.isVisible();
    qDebug() << "Window is active:" << window.isActiveWindow();
    qDebug() << "About to enter event loop";
    
    int result = app.exec();
    
    qDebug() << "Event loop finished with code:" << result;
    
    return result;
}
