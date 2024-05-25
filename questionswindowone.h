#ifndef QUESTIONSWINDOWONE_H
#define QUESTIONSWINDOWONE_H

#include <QDialog>
#include "pugixml.hpp"

#include <QTimer>
#include <QMainWindow>

using namespace pugi;
using namespace std;

namespace Ui {
class QuestionsWindowOne;
}

class QuestionsWindowOne : public QDialog
{
    Q_OBJECT

public:
    explicit QuestionsWindowOne(QWidget *parent = 0);
    ~QuestionsWindowOne();

    void marker(vector<QString>&, vector<QString>&, double&);
    void display(int&,vector<QString>&,vector<QString> &);
    void uncheckRadioButton();
    void clearChoices();
    void writeReview(vector<QString>&, vector<QString>&, vector<QString>&,  double&);
    QString ratePlayer(double &score);

    void resizeEvent(QResizeEvent *event);

private slots:
    void on_next_clicked();

    void on_previous_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_finish_clicked();

    void quizTimer();

private:
    Ui::QuestionsWindowOne *ui;
    int time_in_secs;
    QTimer *timer;
};

#endif // QUESTIONSWINDOWONE_H
