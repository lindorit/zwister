#ifndef REVIEWWINDOW_H
#define REVIEWWINDOW_H

#include <QDialog>

namespace Ui {
class ReviewWindow;
}

class ReviewWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ReviewWindow(QWidget *parent = 0);
    ~ReviewWindow();
    void readReview();
    void resizeEvent(QResizeEvent *event);

    Ui::ReviewWindow *ui;

private slots:
    void on_closeReviewWindowButton_clicked();

private:

};

#endif // REVIEWWINDOW_H
