#ifndef QUESTIONSWINDOWTHREE_H
#define QUESTIONSWINDOWTHREE_H

#include <QDialog>
#include <vector>

#include <QTimer>
#include <QMainWindow>

using namespace std;

namespace Ui {
class QuestionsWindowThree;
}

class QuestionsWindowThree : public QDialog
{
    Q_OBJECT

public:
    explicit QuestionsWindowThree(QWidget *parent = 0);
    ~QuestionsWindowThree();

    void marker(vector<QString>&, vector<QString>&, double&);
    void display(int&,vector<QString>&,vector<QString> &);
    void uncheckRadioButton();
    void clearChoices();
    void writeReview(vector<QString>&, vector<QString>&, vector<QString>&,  double&);
    void clearLineEdit();
    void clearAll();

    QString ratePlayer(double&);

    void resizeEvent(QResizeEvent *event);

private slots:
    void on_previousButton_clicked();

    void on_nextButton_clicked();

    void on_finishButton_clicked();

    void on_lineEdit_editingFinished();

    void quizTimeScaale();

private:
    Ui::QuestionsWindowThree *ui;
    int time_in_secs;
    QTimer *timer;
};

#endif // QUESTIONSWINDOWTHREE_H
