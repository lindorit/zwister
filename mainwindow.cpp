#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "startquizwindow.h"
#include "mainwindowimg.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->login->setFlat(true);
    ui->login->setStyleSheet("QPushButton { background-color: transparent; color: white }");
    ui->close->setFlat(true);
    ui->close->setStyleSheet("QPushButton { background-color: transparent; color: white }");

    ui->label->setStyleSheet("QLabel {color: white }");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_close_clicked()
{
    this->close();
}

void MainWindow::on_login_clicked()
{
    this->close();
    StartQuizWindow *qwo = new StartQuizWindow();
    qwo->showMaximized();
}

void MainWindow::resizeEvent(QResizeEvent *event){
    QWidget::resizeEvent(event);
    mainwindowimg::setBackgroundImage(this,"C:/Users/MAZWI/Desktop/Projectsubmission/QuizProjectGROUPIFINAL/QuizProject/QuizProject/img.jpg");
}
