#include "mainwindowimg.h"

mainwindowimg::mainwindowimg()
{

}

void mainwindowimg::setBackgroundImage(QWidget *wid, const QString &imgpath) {
    QPixmap img(imgpath);
    img=img.scaled(wid->size(),Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window,img);
    wid->setPalette(palette);
}
