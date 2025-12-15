#include "widget_edit.h"
#include "ui_widget_edit.h"

void widget_edit::do_cut()
{
    ui->plainTextEdit->cut();
}

void widget_edit::do_copy()
{
    ui->plainTextEdit->copy();
}

void widget_edit::do_paste()
{
    ui->plainTextEdit->paste();
}

void widget_edit::do_pleete(QFont font)
{
    ui->plainTextEdit->setFont(font);
}

widget_edit::widget_edit(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::widget_edit)
{
    ui->setupUi(this);
}

widget_edit::~widget_edit()
{
    delete ui;
}
