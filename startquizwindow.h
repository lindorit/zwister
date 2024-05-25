#ifndef STARTQUIZWINDOW_H
#define STARTQUIZWINDOW_H

#include <QDialog>

namespace Ui {
class StartQuizWindow;
}

class StartQuizWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StartQuizWindow(QWidget *parent = 0);
    ~StartQuizWindow();
    void resizeEvent(QResizeEvent *event);

private slots:
    void on_startQuizButton_clicked();

    void on_readReview_clicked();

    void on_close_clicked();

private:
    Ui::StartQuizWindow *ui;
};

#endif // STARTQUIZWINDOW_H
