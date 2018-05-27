#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>

class QGraphicsEllipseItem;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void resizeEvent(QResizeEvent *event);

    ~MainWindow();

private slots:
    void on_spinBox_valueChanged(int arg1);
    void on_start_clicked(bool checked);

    void on_actionCreator_triggered();

    void on_actionColor_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsEllipseItem *elp;
    QTimer *timer;
    int factor = 5760;
    int counter = 1;
    QColor color;
};

#endif // MAINWINDOW_H
