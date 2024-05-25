#ifndef MAINWINDOWIMG_H
#define MAINWINDOWIMG_H

#include <QObject>
#include <QWidget>
#include <QPixmap>
#include <QPalette>

class mainwindowimg
{
public:
    mainwindowimg();
    static void setBackgroundImage(QWidget *wid, const QString &imgpath);
};

#endif // MAINWINDOWIMG_H
