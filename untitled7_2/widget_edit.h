#ifndef WIDGET_EDIT_H
#define WIDGET_EDIT_H

#include <QWidget>

namespace Ui {
class widget_edit;
}

class widget_edit : public QWidget
{
    Q_OBJECT

public slots:
    void do_cut();//剪切内容
    void do_copy();//复制内容
    void do_paste();//贴贴内容
    void do_pleete(QFont);//字体设置的

public:
    explicit widget_edit(QWidget *parent = nullptr);
    ~widget_edit();

private:
    Ui::widget_edit *ui;
};

#endif // WIDGET_EDIT_H
