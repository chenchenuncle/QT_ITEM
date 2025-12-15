#include "mainwindow.h"
#include "qobjectdefs.h"
#include "qwindowdefs.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include "ttable.h"
#include "formdoc.h"
#include "widget_edit.h"
#include <QMdiSubWindow>

void MainWindow::do_take_tabwidget(int model)
{
    tabwidget->removeTab(model);
}

void MainWindow::do_show(QAction *action)
{
    if(action==ui->action_11)
    {
        ui->action->setVisible(true);
        ui->action_13->setVisible(true);
        ui->actionwigdet->setVisible(true);
        ui->action_wigdet->setVisible(true);
        ui->action_9->setVisible(false);
        ui->action_10->setVisible(false);
    }
    else
    {
        ui->action->setVisible(false);
        ui->action_13->setVisible(false);
        ui->actionwigdet->setVisible(false);
        ui->action_wigdet->setVisible(false);
        ui->action_9->setVisible(true);
        ui->action_10->setVisible(true);
    }
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched==tabwidget)
    {
    if(event->type()==QEvent::Paint)
    {
        QPainter painter(static_cast<QTabWidget*>(watched));
        painter.drawPixmap(static_cast<QPaintEvent*>(event)->rect(),QPixmap(":/qrc/风景图.png"));
        return true;
    }
    }
    return QWidget::eventFilter(watched,event);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //让2个模式排斥
    group=new QActionGroup(this);
    group->addAction(ui->actionMDI);
    group->addAction(ui->action_11);
    //初始化模式
    ui->action->setVisible(false);
    ui->action_13->setVisible(false);
    ui->actionwigdet->setVisible(false);
    ui->action_wigdet->setVisible(false);
    ui->action_9->setVisible(true);
    ui->action_10->setVisible(true);
    connect(group,SIGNAL(triggered(QAction*)),this,SLOT(do_show(QAction*)));
    //对多种窗口初始化
    midarea=new QMdiArea(this);
    tabwidget=new QTabWidget(this);
    this->setCentralWidget(midarea);
    tabwidget->installEventFilter(this);
    tabwidget->setTabsClosable(true);
    connect(tabwidget,&QTabWidget::tabCloseRequested,this,&::MainWindow::do_take_tabwidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_11_triggered()
{
    if(midarea==static_cast<QMdiArea*>(this->centralWidget()))
    {
        qDebug("成功配对！");
    }
    this->setCentralWidget(tabwidget);
}


void MainWindow::on_actionMDI_triggered()
{
    if(tabwidget==static_cast<QTabWidget*>(this->centralWidget()))
    {
        qDebug("成功配对2！");
    }
    this->setCentralWidget(midarea);
}


void MainWindow::on_actionwigdet_triggered()
{
    FormDoc* doc=new FormDoc(tabwidget);
    doc->setAttribute(Qt::WA_DeleteOnClose);
    tabwidget->addTab(doc,"基础窗口");
}


void MainWindow::on_action_wigdet_triggered()
{
    FormDoc* doc=new FormDoc;
    doc->setAttribute(Qt::WA_DeleteOnClose);
    doc->setWindowTitle("widget");
    doc->show();
}


void MainWindow::on_action_triggered()
{
    TTable* table=new TTable(tabwidget);
    table->setAttribute(Qt::WA_DeleteOnClose);
    tabwidget->addTab(table,"表格窗口");
}


void MainWindow::on_action_13_triggered()
{
    TTable* table=new TTable;
    table->setAttribute(Qt::WA_DeleteOnClose);
    table->setWindowTitle("tablewidget");
    table->show();
}


void MainWindow::on_action_1_triggered()
{
    widget_edit* widget=new widget_edit;
    midarea->addSubWindow(widget);
}

