/*#include <QApplication>
#include "database.h"
#include "roleselection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!Database::connect()) {
        qDebug() << "Failed to connect DB";
        return -1;
    }

    Database::init();

    RoleSelection w;
    w.show();

    return a.exec();
}

*/

#include "main_window.h"
#include <QApplication>
#include "database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    if (!Database::connect()) {
        qDebug() << "Failed to connect DB";
        return -1;
    }
    Database::init();


    MainWindow w;
    w.show();
    return a.exec();
}