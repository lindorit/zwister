#include "questionswindowtwo.h"
#include "ui_questionswindowtwo.h"
#include "startquizwindow.h"

#include "mainwindowimg.h"
#include "reviewwindow.h"
#include "pugiconfig.hpp"
#include "pugixml.hpp"

#include <vector>
#include <fstream>
#include <QTextStream>
#include <QMessageBox>

using namespace pugi;
using namespace std;

vector<QString> allQuestions;
vector<QString> rightOptions;
vector<QString> userOptns;

QString userOptn;

double userScore(0);
const double finalMark = 18;
double quizRating = userScore/finalMark;
int p = 0;

int iTwo(1);
int iterate(0);


QuestionsWindowTwo::QuestionsWindowTwo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuestionsWindowTwo)
{
    ui->setupUi(this);
    on_next_clicked();

    ui->finish->setEnabled(false);

    ui->finish->setFlat(true);
    ui->next->setFlat(true);
    ui->previous->setFlat(true);

    ui->finish->setStyleSheet("QPushButton { background-color: transparent; color: white }");
    ui->next->setStyleSheet("QPushButton { background-color: transparent; color: white }");
    ui->previous->setStyleSheet("QPushButton { background-color: transparent; color: white }");

    ui->radioButton->setStyleSheet("QRadioButton { background-color: transparent; color: white }");
    ui->radioButton_2->setStyleSheet("QRadioButton { background-color: transparent; color: white }");

    ui->textEdit->setStyleSheet("QTextEdit { background-color: transparent; color: white; border: 2px solid transparent; }");
    ui->groupBox->setStyleSheet("QGroupBox { background-color: transparent; color: white }");

    ui->label->setStyleSheet("QLabel { background-color: transparent; color: white }");
    ui->label_3->setStyleSheet("QLabel { background-color: transparent; color: white }");

    time_in_secs = 900;
    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(quizTime()));

    timer->start(1000);
}

QuestionsWindowTwo::~QuestionsWindowTwo()
{
    delete ui;
}

void QuestionsWindowTwo::quizTime()
{
    if (time_in_secs == 0) {
        timer->stop();
        ui->label_3->setText("Time out!");
        return;
    }

    int time_in_mins = time_in_secs / 60;
    int t_in_secs = time_in_secs % 60;

    QString time = QString("%1:%2").arg(time_in_mins, 2, 10, QLatin1Char('0')).arg(t_in_secs, 2, 10, QLatin1Char('0'));
    ui->label_3->setText(time);

    time_in_secs--;
}

void QuestionsWindowTwo::marker(vector<QString> &playerOptions, vector<QString> &corrOpts, double &userScore) {
    try {
        for (int i = 0; i < playerOptions.size(); i++) {
            if (playerOptions[i] == corrOpts[i]) {
                userScore += 2;
            }
        }
    }
    catch(...) {

    }
}

void QuestionsWindowTwo::on_next_clicked()
{
    if (p > 0) {
        if (!ui->radioButton->isChecked() && !ui->radioButton_2->isChecked()) {
            userOptn = " ";
        }
        userOptns.push_back(userOptn);
    }

    p++;
    uncheckRadioButtons();
    display(iterate, allQuestions, rightOptions);
    iterate++;
    iTwo++;

    if (iterate == 8) {
       ui->finish->setEnabled(true);
    }
}

void QuestionsWindowTwo::on_previous_clicked()
{
    userOptns.pop_back();
    iterate = iterate-1;
    iTwo--;
    uncheckRadioButtons();
    display(iterate, allQuestions, rightOptions);

}

void QuestionsWindowTwo::on_finish_clicked()
{
    userOptns.push_back(userOptn);
    marker(userOptns, rightOptions, userScore);

    QMessageBox::information(this, "Your score: ", QString::number(userScore));
    this->close();
    iTwo = 1;
    iterate = 0;

    writeReview(allQuestions, rightOptions, userOptns, userScore);
    clearChoices();

    StartQuizWindow *stq = new StartQuizWindow();
    stq->showMaximized();
}

void QuestionsWindowTwo::display(int &iterater, vector<QString>& quizQuestionsVector, vector<QString> &rightOptions) {

    xml_document document;
    document.load_file("C:/Users/MAZWI/Desktop/Projectsubmission/QuizProjectGROUPIFINAL/QuizProject/QuizProject/LevelMedium.xml");

    xpath_node_set root = document.select_nodes("quiz/question");

    vector<xml_node> questionNodes;

    for (xpath_node node : root) {
        questionNodes.push_back(node.node());
    }

    vector<QString> questions;
    for (xml_node node : questionNodes) {
        questions.push_back(node.first_child().text().as_string());
    }

    xpath_node_set correctSet = document.select_nodes("quiz/question/option[@correct='true']");

    vector<QString> co;

    for (xpath_node node : correctSet) {
        co.push_back(node.node().text().as_string());
    }

    ui->textEdit->setText(QString::number(iTwo) + ". " + questions[iterate]);
    ui->radioButton->setText(questionNodes[iterate].first_child().next_sibling().text().as_string());
    ui->radioButton_2->setText(questionNodes[iterate].first_child().next_sibling().next_sibling().text().as_string());

    rightOptions = co;
    quizQuestionsVector = questions;

    if (iterate <= 0) {
        ui->previous->setEnabled(false);
    }
    else if (iterate >= 8) {
        ui->next->setEnabled(false);
    }
    else {
        ui->next->setEnabled(true);
        ui->previous->setEnabled(true);
    }
}


void QuestionsWindowTwo::writeReview(vector<QString> &q, vector<QString> &c, vector<QString> &u, double &sc) {
     int quizRating = (sc / finalMark) * 100;

    std::ofstream fileOut("C:/Users/MAZWI/Desktop/Projectsubmission/QuizProjectGROUPIFINAL/QuizProject/build-QuizProject-Desktop-Debug/review.txt");
     if (fileOut) {


        fileOut << "Name: " << "Nduduzo Mnguni" << endl;
        fileOut<< "Score: " << sc << " out of 18"<<"\nPercentage: " << quizRating << "%" << endl;
        fileOut<< "Title: " << ratePlayer(sc).toStdString() << endl;
        for (int i = 0; i < q.size(); i++) {
            fileOut << "\n\n" << (i + 1) << ". " << q[i].toStdString()  << endl;
            fileOut << "Correct Option: " << c[i].toStdString()  <<"\n"<< endl;
            fileOut << "Your Option: "<< u[i].toStdString()  << endl;
            fileOut << "\n\n";
        }

    }
    fileOut.close();
}


void QuestionsWindowTwo::uncheckRadioButtons() {
    ui->radioButton->setAutoExclusive(false);
    ui->radioButton->setChecked(false);
    ui->radioButton->setAutoExclusive(true);

    ui->radioButton_2->setAutoExclusive(false);
    ui->radioButton_2->setChecked(false);
    ui->radioButton_2->setAutoExclusive(true);
}

void QuestionsWindowTwo::clearChoices() {
    allQuestions.clear();
    rightOptions.clear();
    userOptns.clear();
    userScore = 0;
    p = 0;
}

QString QuestionsWindowTwo::ratePlayer(double &score) {
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

void QuestionsWindowTwo::on_radioButton_clicked()
{
    userOptn = ui->radioButton->text();
}

void QuestionsWindowTwo::on_radioButton_2_clicked()
{
    userOptn = ui->radioButton_2->text();
}

void QuestionsWindowTwo::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    mainwindowimg::setBackgroundImage(this,"C:/Users/MAZWI/Desktop/Projectsubmission/QuizProjectGROUPIFINAL/QuizProject/QuizProject/img.jpg");
}
