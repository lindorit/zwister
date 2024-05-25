#ifndef QUESTIONSWINDOWTWO_H
#define QUESTIONSWINDOWTWO_H

#include <vector>
#include <QDialog>

#include <QTimer>
#include <QMainWindow>

using namespace std;
namespace Ui {
class QuestionsWindowTwo;
}

class QuestionsWindowTwo : public QDialog
{
    Q_OBJECT

public:
    explicit QuestionsWindowTwo(QWidget *parent = 0);
    ~QuestionsWindowTwo();

    void marker(vector<QString>&, vector<QString>&, double&);
    void display(int&,vector<QString>&,vector<QString> &);
    void uncheckRadioButtons();
    void clearChoices();
    void writeReview(vector<QString>&, vector<QString>&, vector<QString>&,  double&);
    QString ratePlayer(double &score);
    void resizeEvent(QResizeEvent *event);

private slots:
    void on_previous_clicked();

    void on_next_clicked();

    void on_finish_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void quizTime();

private:
    Ui::QuestionsWindowTwo *ui;
    int time_in_secs;
    QTimer *timer;
};

#endif // QUESTIONSWINDOWTWO_H
