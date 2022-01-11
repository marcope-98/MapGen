#include "dialog.h"
#include <QApplication>
#include <QSettings>

void setupSettings();
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();

    return a.exec();
}

void setupSettings() {
    QSettings settings;
    settings.setValue("drawing/gridSize",10);
    settings.setValue("drawing/hanleSize",15);
    settings.setValue("drawing/gridEnabled",false);
}
