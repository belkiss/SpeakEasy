#include <iostream>

#include <QApplication>
#include "SE_Screen.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (!QGLFormat::hasOpenGL())
    {
        std::cerr << "This system has no OpenGL support" << std::endl;
        return 1;
    }

    SE_Screen vl_screen;
    vl_screen.setWindowTitle(QObject::tr("SpeakEasy, v0.1"));
    vl_screen.resize(300, 300);
    vl_screen.show();

    return app.exec();
}
