#include "reviewwindow.h"
#include "mainwindowimg.h"
#include "ui_reviewwindow.h"
#include "startquizwindow.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>

ReviewWindow::ReviewWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReviewWindow)
{
    ui->setupUi(this);
    readReview();

    ui->label->setStyleSheet("QLabel { background-color: transparent; color: white }");
    ui->textEdit->setStyleSheet("QTextEdit { background-color: transparent; color: white; border: 2px solid transparent }");
    ui->closeReviewWindowButton->setStyleSheet("QPushButton { background-color: transparent; color: white }");
}

ReviewWindow::~ReviewWindow()
{
    delete ui;
}

void ReviewWindow::on_closeReviewWindowButton_clicked()
{
    this->close();
    StartQuizWindow *sqw = new StartQuizWindow();
    sqw->showMaximized();
}

void ReviewWindow::readReview() {
    QFile file("C:/Users/MAZWI/Desktop/Projectsubmission/QuizProjectGROUPIFINAL/QuizProject/build-QuizProject-Desktop-Debug/review.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }
    QTextStream in(&file);
    ui->textEdit->setText(in.readAll());

    file.close();
}

void ReviewWindow::resizeEvent(QResizeEvent *event){
    QWidget::resizeEvent(event);
    mainwindowimg::setBackgroundImage(this,"C:/Users/MAZWI/Desktop/Projectsubmission/QuizProjectGROUPIFINAL/QuizProject/QuizProject/img.jpg");
}
