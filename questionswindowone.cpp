#include "questionswindowone.h"
#include "ui_questionswindowone.h"
#include "startquizwindow.h"

#include "mainwindowimg.h"
#include "reviewwindow.h"
#include "pugiconfig.hpp"
#include "pugixml.hpp"
#

#include <vector>
#include <QDebug>
#include <QMessageBox>
#include <fstream>

using namespace pugi;
using namespace std;

vector<QString> userOptions;
vector<QString> correctOptions;
vector<QString> questions;

QString userOption;

double score(0);
const double finalMark(18);
int runner = 0;

int questionNumber(1);
int it(0);

QuestionsWindowOne::QuestionsWindowOne(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuestionsWindowOne)
{
    ui->setupUi(this);
    on_next_clicked();

    ui->finish->setEnabled((false));
    ui->finish->setFlat(true);
    ui->next->setFlat(true);
    ui->previous->setFlat(true);

    ui->finish->setStyleSheet("QPushButton { background-color: transparent; color: white }");
    ui->next->setStyleSheet("QPushButton { background-color: transparent; color: white }");
    ui->previous->setStyleSheet("QPushButton { background-color: transparent; color: white }");

    ui->radioButton->setStyleSheet("QRadioButton { background-color: transparent; color: white }");
    ui->radioButton_2->setStyleSheet("QRadioButton { background-color: transparent; color: white }");
    ui->radioButton_3->setStyleSheet("QRadioButton { background-color: transparent; color: white }");
    ui->radioButton_4->setStyleSheet("QRadioButton { background-color: transparent; color: white }");

    ui->textEdit->setStyleSheet("QTextEdit { background-color: transparent; color: white; border: 2px solid transparent; }");
    ui->groupBox->setStyleSheet("QGroupBox { background-color: transparent; color: white }");

    ui->label->setStyleSheet("QLabel { background-color: transparent; color: white }");
    ui->label_3->setStyleSheet("QLabel { background-color: transparent; color: white }");

    time_in_secs = 900;
    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(quizTimer()));

    timer->start(1000);
}

QuestionsWindowOne::~QuestionsWindowOne()
{
    delete ui;
}

void QuestionsWindowOne::quizTimer() {
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


void QuestionsWindowOne::on_next_clicked()
{
    if (runner > 0) {
        if (!ui->radioButton->isChecked() && !ui->radioButton_2->isChecked() && !ui->radioButton_3->isChecked() && !ui->radioButton_4->isChecked()) {
            userOption = " ";
        }
        userOptions.push_back(userOption);
    }

    runner++;
    uncheckRadioButton();
    display(it, questions, correctOptions);
    it++;
    questionNumber++;

    if (it == 8) {
        ui->finish->setEnabled(true);
    }

}

void QuestionsWindowOne::on_previous_clicked()
{
    userOptions.pop_back();
    it = it -1;
    questionNumber--;
    uncheckRadioButton();
    display(it, questions, correctOptions);
}

void QuestionsWindowOne::on_finish_clicked()
{
    userOptions.push_back(userOption);
    marker(userOptions,correctOptions,score);
    QMessageBox::information(this, "Your score: ", QString::number(score));
    this->close();
    questionNumber = 1;
    it = 0;

    writeReview(questions, correctOptions, userOptions, score);
    clearChoices();

    StartQuizWindow *stq = new StartQuizWindow();
    stq->showMaximized();
}

void QuestionsWindowOne::marker(vector<QString> &playerOptions, vector<QString> &rightOptions, double &userScore) {


    try {
        for(int i=0;i<playerOptions.size();i++){
             if (playerOptions[i] == rightOptions[i]) {
                userScore += 2;
             }
        }
    }

    catch(...) {

    }
}

void QuestionsWindowOne::clearChoices() {
    userOptions.clear();
    correctOptions.clear();
    questions.clear();
    score = 0;
}

QString QuestionsWindowOne::ratePlayer(double &score) {
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

void QuestionsWindowOne::writeReview(vector<QString> &q, vector<QString> &c, vector<QString> &u, double &sc) {
    int quizRating = (sc / finalMark) * 100;

    std::ofstream file("C:/Users/MAZWI/Desktop/Projectsubmission/QuizProjectGROUPIFINAL/QuizProject/build-QuizProject-Desktop-Debug/review.txt");
    if (file) {
       // QTextStream stream(&file);

        file << "Name: " << "Nduduzo Mnguni" << endl;
        file << "Score: " << sc << " out of 18"<<"\nPercentage: " << quizRating << "%" << endl;
        file << "Title: " << ratePlayer(sc).toStdString() << endl;
        for (int i = 0; i < q.size(); i++) {
            file << "\n\n" << (i + 1) << ". " << q[i].toStdString() << "\n" << endl;
            file << "Correct Option: " << c[i].toStdString() << "\n" << endl;
            file << "Your Option: "<< u[i].toStdString() << "\n" << endl;
            file << "\n\n";
        };
    }
    file.close();
}

void QuestionsWindowOne::display(int &iterator,vector<QString>& quizQuestionsVector,vector<QString> &rightOptions) {
    xml_document document;
    document.load_file("C:/Users/MAZWI/Desktop/Projectsubmission/QuizProjectGROUPIFINAL/QuizProject/QuizProject/LevelEasy.xml");

    vector<xml_node> nodes;
    xpath_node_set nodeset = document.select_nodes("quiz/question");

    for(xpath_node node : nodeset)
        nodes.push_back(node.node());

    vector<QString> questions;
    for(xml_node node : nodes){
        questions.push_back(node.first_child().text().as_string());
    }

    xpath_node_set correctSet = document.select_nodes("quiz/question/option[@correct='true']");

    for (xpath_node node : correctSet) {
        rightOptions.push_back(node.node().text().as_string());
    }

    ui->textEdit->setText(QString::number(questionNumber) + ". " + questions[iterator]);
    ui->radioButton->setText(nodes[iterator].first_child().next_sibling().text().as_string());
    ui->radioButton_2->setText(nodes[iterator].first_child().next_sibling().next_sibling().text().as_string());
    ui->radioButton_3->setText(nodes[iterator].first_child().next_sibling().next_sibling().next_sibling().text().as_string());
    ui->radioButton_4->setText(nodes[iterator].first_child().next_sibling().next_sibling().next_sibling().next_sibling().text().as_string());

    quizQuestionsVector = questions;

    if (it <= 0) {
        ui->previous->setEnabled(false);
    }
    else if (it >= 8) {
        ui->next->setEnabled(false);
    }
    else {
        ui->next->setEnabled(true);
        ui->previous->setEnabled(true);
    }
}

void QuestionsWindowOne::uncheckRadioButton() {
    ui->radioButton->setAutoExclusive(false);
    ui->radioButton->setChecked(false);
    ui->radioButton->setAutoExclusive(true);

    ui->radioButton_2->setAutoExclusive(false);
    ui->radioButton_2->setChecked(false);
    ui->radioButton_2->setAutoExclusive(true);

    ui->radioButton_3->setAutoExclusive(false);
    ui->radioButton_3->setChecked(false);
    ui->radioButton_3->setAutoExclusive(true);

    ui->radioButton_4->setAutoExclusive(false);
    ui->radioButton_4->setChecked(false);
    ui->radioButton_4->setAutoExclusive(true);
}

void QuestionsWindowOne::on_radioButton_clicked()
{
    userOption = ui->radioButton->text();
}

void QuestionsWindowOne::on_radioButton_2_clicked()
{
    userOption = ui->radioButton_2->text();
}

void QuestionsWindowOne::on_radioButton_3_clicked()
{
    userOption = ui->radioButton_3->text();
}

void QuestionsWindowOne::on_radioButton_4_clicked()
{
    userOption = ui->radioButton_4->text();
}

void QuestionsWindowOne::resizeEvent(QResizeEvent *event){
    QWidget::resizeEvent(event);
    mainwindowimg::setBackgroundImage(this,"C:/Users/MAZWI/Desktop/Projectsubmission/QuizProjectGROUPIFINAL/QuizProject/QuizProject/img.jpg");
}
