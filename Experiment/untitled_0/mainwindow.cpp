#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::do_show(bool)
{
    qDebug("文本信号：");
    qDebug()<<ui->plainTextEdit->isWindowModified();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    midarea=new QMdiArea;
    this->setCentralWidget(ui->plainTextEdit);
    winodw=new QWidget;
    midarea->addSubWindow(winodw);
    midarea->setAttribute(Qt::WA_DeleteOnClose);
    connect(ui->plainTextEdit,&QPlainTextEdit::modificationChanged,this,&QMainWindow::setWindowModified);
    // 将 &QMainWindow::do_show 改为 &MainWindow::do_show
    connect(ui->plainTextEdit,&QPlainTextEdit::modificationChanged,this,&MainWindow::do_show);
    qDebug("开始信号");
    qDebug()<<ui->plainTextEdit->isWindowModified();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionsadsd_triggered()
{
    winodw=new QWidget;
    midarea->addSubWindow(winodw,Qt::Widget);    winodw->show();
    this->setWindowModified(false);
    ui->plainTextEdit->setOverwriteMode(false);
    ui->plainTextEdit->setWindowModified(true);
    qDebug("点击信号");
    qDebug()<<ui->plainTextEdit->isWindowModified();
    ui->plainTextEdit->document()->setModified(false);
}

