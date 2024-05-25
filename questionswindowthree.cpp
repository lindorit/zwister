#include "questionswindowthree.h"
#include "ui_questionswindowthree.h"
#include "mainwindowimg.h"
#include "startquizwindow.h"
#include "pugiconfig.hpp"
#include "pugixml.hpp"

#include <vector>
#include <QMessageBox>
#include <fstream>
#include <QTextStream>

double scoreThree(0);
const double finalMark(18);
double rateThree = (scoreThree/finalMark) * 100;

QString userOptionThree;

int qNumber(1);
int iThree(0);
int num = 0;

vector<QString> allUserOptions;
vector<QString> allCorrectOptions;
vector<QString> allQuizQuestions;

QString userChoice;

using namespace pugi;
using namespace std;

QuestionsWindowThree::QuestionsWindowThree(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuestionsWindowThree)
{
    ui->setupUi(this);
    on_nextButton_clicked();

    ui->finishButton->setFlat(true);
    ui->nextButton->setFlat(true);
    ui->previousButton->setFlat(true);

    ui->finishButton->setStyleSheet("QPushButton { background-color: transparent; color: white }");
    ui->nextButton->setStyleSheet("QPushButton { background-color: transparent; color: white }");
    ui->previousButton->setStyleSheet("QPushButton { background-color: transparent; color: white }");

    ui->groupBox->setStyleSheet("QGroupBox { background-color: transparent; color: white }");

    ui->label->setStyleSheet("QLabel { background-color: transparent; color: white }");
    ui->timeLabel->setStyleSheet("QLabel { background-color: transparent; color: white }");
    ui->questionPrompt->setStyleSheet("QLabel { background-color: transparent; color: white }");

    ui->lineEdit->setStyleSheet("QLineEdit {background-color: transparent; color: white; border: 2px solid white}");

    time_in_secs = 600;
    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(quizTimeScaale()));

    timer->start(1000);
}

QuestionsWindowThree::~QuestionsWindowThree()
{
    delete ui;
}

void QuestionsWindowThree::on_previousButton_clicked()
{
    allUserOptions.pop_back();
    iThree=iThree-1;
    qNumber--;
    clearLineEdit();
    display(iThree, allQuizQuestions, allCorrectOptions);

}

void QuestionsWindowThree::quizTimeScaale() {
    if (time_in_secs == 0) {
        timer->stop();
        ui->timeLabel->setText("Time out!");
        return;
    }

    int time_in_mins = time_in_secs / 60;
    int t_in_secs = time_in_secs % 60;

    QString time = QString("%1:%2").arg(time_in_mins, 2, 10, QLatin1Char('0')).arg(t_in_secs, 2, 10, QLatin1Char('0'));
    ui->timeLabel->setText(time);

    time_in_secs--;
}

void QuestionsWindowThree::on_nextButton_clicked()
{
    if (num > 0) {
        if (ui->lineEdit->text() == "") {
            userChoice  = ui->lineEdit->text();
        }
        allUserOptions.push_back(userChoice);
    }

    num++;
    clearLineEdit();
    display(iThree, allQuizQuestions, allCorrectOptions);
    iThree++;
    qNumber++;

    if (iThree == 8) {
        ui->finishButton->setEnabled(true);
    }
}

void QuestionsWindowThree::on_finishButton_clicked()
{
    allUserOptions.push_back(userChoice);
    marker(allUserOptions, allCorrectOptions, scoreThree);
    QMessageBox::information(this, "Your score: ", QString::number(scoreThree));
    this->close();
    qNumber = 1;
    iThree = 0;

    writeReview(allQuizQuestions, allCorrectOptions, allUserOptions, scoreThree);
    clearAll();

    StartQuizWindow *sqw = new StartQuizWindow();
    sqw->showMaximized();
}

void QuestionsWindowThree::display(int &i, vector<QString> &q,vector<QString> &c) {
    xml_document document;
    document.load_file("C:/Users/MAZWI/Desktop/Projectsubmission/QuizProjectGROUPIFINAL/QuizProject/QuizProject/LevelHard.xml");

    vector<xml_node> nodes;
    xpath_node_set nodeset = document.select_nodes("quiz/question");

    for(xpath_node node : nodeset)
        nodes.push_back(node.node());

    vector<QString> questions;
    for(xml_node node : nodes){
        questions.push_back(node.first_child().text().as_string());
    }

    vector<QString> correctOptions;
    xpath_node_set correctSet = document.select_nodes("quiz/question/option[@correct='true']");

    for (xpath_node node : correctSet) {
        correctOptions.push_back(node.node().text().as_string());
    }

    ui->questionPrompt->setText(QString::number(qNumber) + ". " + questions[i]);

    q = questions;
    c = correctOptions;

    if (iThree <= 0) {
        ui->previousButton->setEnabled(false);
    }

    else if (iThree >= 8) {
        ui->nextButton->setEnabled(false);
    }
    else {
        ui->nextButton->setEnabled(true);
        ui->previousButton->setEnabled(true);
    }
}

void QuestionsWindowThree::clearLineEdit() {
    ui->lineEdit->clear();
}

void QuestionsWindowThree::marker(vector<QString> &userOptionThree, vector<QString> &correctOptions, double &scoreThree) {
    try {
        for (int i = 0; i < userOptionThree.size(); i++) {
            if (userOptionThree[i] == correctOptions[i]) {
                scoreThree += 2;
            }
        }
    }
    catch(...) {

    }
}

void QuestionsWindowThree::on_lineEdit_editingFinished()
{
    userChoice = ui->lineEdit->text();
    //allUserOptions.push_back(userChoice);
}

void QuestionsWindowThree::writeReview(vector<QString> &q, vector<QString> &c, vector<QString> &u, double &sc) {
    int quizRating = (sc / finalMark) * 100;

    std::ofstream fileOutput("C:/Users/MAZWI/Desktop/Projectsubmission/QuizProjectGROUPIFINAL/QuizProject/build-QuizProject-Desktop-Debug/review.txt");
    if (fileOutput) {

        fileOutput << "Name: " << "Nduduzo Mnguni" << endl;
        fileOutput << "Score: " << sc << " out of 18"<<"\nPercentage: " << quizRating << "%" << endl;
        fileOutput << "Title: " << ratePlayer(sc).toStdString() << endl;
        for (int i = 0; i < q.size(); i++) {
            fileOutput << "\n\n" << (i + 1) << ". " << q[i].toStdString() << "\n" << endl;
            fileOutput << "Correct Option: " << c[i].toStdString() << "\n" << endl;
            fileOutput << "Your Option: "<< u[i].toStdString() << "\n" << endl;
            fileOutput << "\n\n";
        }
    }
    fileOutput.close();
}

void QuestionsWindowThree::clearAll() {
    allUserOptions.clear();
    allQuizQuestions.clear();
    allCorrectOptions.clear();
    scoreThree = 0;
    num = 0;
}

QString QuestionsWindowThree::ratePlayer(double &score) {
    int percent = (score/finalMark) * 100;

    if (percent < 20)
        return "NO CLASS\nComment:You still need to engage yourself more with the programming environment!\nFAILED!";

    else if (percent > 19 && percent < 50)
        return "BEGINNER\nComment: You still need to put more effort in programming!\nFAILED!";
    else if (percent > 49 && percent < 60)
        return "AMATEUR";
    else if (percent > 59 && percent < 80)
        return "EXPERT\nComment: You have done very well,keep it up !!\nPASSED! ";
    else
        return "PROFESSOR\nComment: You have done exceptionally well!\nPASSED WITH DISTINCTION!!!";

}

void QuestionsWindowThree::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    mainwindowimg::setBackgroundImage(this,"C:/Users/MAZWI/Desktop/Projectsubmission/QuizProjectGROUPIFINAL/QuizProject/QuizProject/img.jpg");
}
