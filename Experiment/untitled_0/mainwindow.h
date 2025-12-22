#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>
#include <QMdiArea>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QMdiArea* midarea;
    QWidget* winodw;

private slots:
    void do_show(bool);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionsadsd_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
