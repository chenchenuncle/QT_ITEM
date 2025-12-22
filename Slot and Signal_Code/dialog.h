#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <Qtwidgets>
class Dialog : public QDialog
{
    Q_OBJECT
private:
    QCheckBox *chekcbokunder;
    QCheckBox *chekcbokitalic;
    QCheckBox *chekcboxbold;
    QRadioButton *radioblack;
    QRadioButton *radiorad;
    QRadioButton *radiobule;
    QPushButton *pushok;
    QPushButton *pushcancel;
    QPushButton *pushclose;
    QPlainTextEdit *txtEdit;
    void iniu();
    void inisignalslots();
private slots:
    void do_chkcbokunder(bool checked);
    void do_checbokitalic(bool checked);
    void do_checbokboxdold(bool checked);
    void do_setFontColor();
    void do_btncancel();
public:
    Dialog(QWidget*parent=nullptr);
    ~Dialog();
};



#endif // DIALOG_H
