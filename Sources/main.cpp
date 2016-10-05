#include <QApplication>
#include <QFile>
#include <QTextStream>

#include "Headers/mainmenu.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile stylesheetFile(":/css/application.css");
    if(stylesheetFile.open(QFile::ReadOnly))
    {
        QTextStream stylesheet(&stylesheetFile);
        a.setStyleSheet(stylesheet.readAll());
    }

    MainMenu w;
    w.show();

    return a.exec();
}
