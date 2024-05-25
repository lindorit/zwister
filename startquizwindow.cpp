#include "startquizwindow.h"
#include "mainwindowimg.h"
#include "ui_startquizwindow.h"
#include "questionswindowone.h"
#include "questionswindowtwo.h"
#include "questionswindowthree.h"
#include "reviewwindow.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>

StartQuizWindow::StartQuizWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartQuizWindow)
{
    ui->setupUi(this);

    ui->startQuizButton->setFlat(true);
    ui->startQuizButton->setStyleSheet("QPushButton { background-color: transparent; color: white }");

    ui->close->setFlat(true);
    ui->close->setStyleSheet("QPushButton { background-color: transparent; color: white }");

    ui->readReview->setFlat(true);
    ui->readReview->setStyleSheet("QPushButton { background-color: transparent; color: white }");

    ui->textEdit->setStyleSheet("QTextEdit { background-color: transparent; color: white }");
}

StartQuizWindow::~StartQuizWindow()
{
    delete ui;
}

int i(0);
void StartQuizWindow::on_startQuizButton_clicked()
{
    this->close();

    if (i == 0)
    {
        QuestionsWindowOne *q1 = new QuestionsWindowOne();
        q1->showMaximized();
        i++;
    }
    else if (i == 1)
    {
        QuestionsWindowTwo *q2 = new QuestionsWindowTwo();
        q2->showMaximized();
        i++;
    }

    else if (i == 2)
    {
        QuestionsWindowThree *q3 = new QuestionsWindowThree();
        q3->showMaximized();
        i++;
    }
    else if(i>2) {
        i=0;
        QuestionsWindowOne *q2 = new QuestionsWindowOne();
        q2->showMaximized();

    }

}

void StartQuizWindow::on_readReview_clicked()
{
    ReviewWindow *rw = new ReviewWindow();
    rw->showMaximized();
}

void StartQuizWindow::on_close_clicked()
{
    this->close();
}

void StartQuizWindow::resizeEvent(QResizeEvent *event){
    QWidget::resizeEvent(event);
    mainwindowimg::setBackgroundImage(this,"C:/Users/MAZWI/Desktop/Projectsubmission/QuizProjectGROUPIFINAL/QuizProject/QuizProject/img.jpg");
}
