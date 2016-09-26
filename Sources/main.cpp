#include "../Headers/mainmenu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet(
        QString(
            "QPushButton {"
                "background-color: #3399CC;"
                "border: 0px solid black;"
                "padding: 10px;"
                "font-family: sans-serif;"
                "font-size: 15px;"
                "font-weight: bold;"
                "color: white;"
            "}"
            " "
            "QPushButton:pressed {"
                "background-color: #2681A5;"
            "}"
        )
    );
    MainMenu w;
    w.show();

    return a.exec();
}
