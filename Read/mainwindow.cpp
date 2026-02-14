#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QByteArray>
#include <QDir>
#include <QGuiApplication>
#include <QSaveFile>

QString MainWindow::Contents()
{
    QString root=QDir::currentPath();
    QString name=QGuiApplication::applicationDisplayName();
    int last=root.lastIndexOf(name)+name.size();
    return root.first(last)+"/TXT";
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setDocumentMode(true);
    this->setCentralWidget(ui->tabWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action1_triggered()
{
    QString str;
    str=QFileDialog::getOpenFileName(this,"选择一个文件",Contents());
    if(str.isEmpty())
        return;
    QFile file(str);
    if(!file.open(QFile::Text|QFile::ReadOnly))
        return;
    ui->plainTextEdit->clear();
    while(!file.atEnd())
        ui->plainTextEdit->appendPlainText(QString(file.readLine()));
    ui->plainTextEdit_2->appendPlainText(ui->plainTextEdit->toPlainText());
    file.close();
}

void MainWindow::on_action2_triggered()
{
    QString dir=Contents();
    QString name=QFileDialog::getOpenFileName(this,"选择一个文本",dir);
    QFile file(name);
    if(!file.open(QFile::Text|QFile::ReadWrite))
        return;
    file.write(ui->plainTextEdit->toPlainText().toUtf8());
    file.close();
}


void MainWindow::on_action3_triggered()
{
    QString dir=Contents();
    QString name=QFileDialog::getOpenFileName(this,"选择一个文本",dir);
    QSaveFile file(name);
    if(!file.open(QIODeviceBase::WriteOnly|QIODeviceBase::Text))
        return;
    file.write(ui->plainTextEdit->toPlainText().toUtf8());
    if(!file.commit())
        return;
}


void MainWindow::on_action4_triggered()
{
    QString dir=Contents();
    QString name=QFileDialog::getOpenFileName(this,"选择一个文本",dir);
    QFile file(name);
    if(!file.open(QFile::ReadOnly|QFile::Text))
        return;
    QTextStream pout(&file);
    ui->plainTextEdit_2->clear();
    while(!pout.atEnd())
        ui->plainTextEdit_2->appendPlainText(pout.readLine());
}


void MainWindow::on_action5_triggered()
{
    QString dir=Contents();
    QString name=QFileDialog::getOpenFileName(this,"选择一个文本",dir);
    QFile file(name);
    if(!file.open(QFile::ReadWrite|QFile::Text))
        return;
    QTextStream pout(&file);
    pout<<ui->plainTextEdit_2->toPlainText();
}

