#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QTime>
#include <QRandomGenerator>

void MainWindow::insertrowColumns(int curent)
{
    //随机种子
    qlonglong id;

    //查询是否随机ID数据库已经存在
    while(1)
    {
        qlonglong mia=1240000000000,max=1249999999999;
        QRandomGenerator i(QTime::currentTime().msecsSinceStartOfDay());
        id=i.bounded(mia,max);
        QSqlQuery query(QSqlDatabase::database("stydy"));
        query.prepare("SELECT EXISTS(SELECT 1 FROM studyinfo WHERE study_ID=:a)");
        query.bindValue(":a",id);
        if(!query.exec())
            QMessageBox::information(this,"删除数据库问题","具体原因:"+query.lastError().text());
        if(!query.next())
            return;
        if(!query.value(0).toInt())
            break;
    }
    //初始化数据
    QSqlRecord record=model->record();
    record.setValue(record.indexOf("study_ID"),id);//随机种子
    record.setValue(record.indexOf("study_name"),"请输入名字");
    record.setValue(record.indexOf("gender"),"请输入性别");
    record.setValue(record.indexOf("College_ID"),"请输入学院");
    record.setValue(record.indexOf("Professional_ID"),"请输入专业");

    //向模型插入初始化数据
    model->insertRecord(curent,record);

    //激活组件
    ui->action_5->setEnabled(true);
    ui->action_6->setEnabled(true);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //初始化ui
    this->setCentralWidget(ui->tableView);

    //初始化连接数据库
    QSqlDatabase::addDatabase("QSQLITE","stydy");
    //初始化view/mdel
    model=new QSqlRelationalTableModel(this);
    itemmodel=new QItemSelectionModel(model,this);
    ui->tableView->setModel(model);
    ui->tableView->setSelectionModel(itemmodel);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_1_triggered()
{
    //选择文件
    QString str=QFileDialog::getOpenFileName(this,"选择文件","选择数据库");
    if(str.isEmpty())
        return;

    //打开数据库
    QSqlDatabase db=QSqlDatabase::database("stydy");
    db.setDatabaseName(str);
    if(!db.open())
    {
        QMessageBox::information(this,"打开数据库问题","原因:"+db.lastError().text());
        return;
    }

    //重新建立新的model
    delete model;
    model=new QSqlRelationalTableModel(this,db);
    itemmodel=new QItemSelectionModel(model,this);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(0,Qt::AscendingOrder);
    itemmodel->setModel(model);
    ui->tableView->setModel(model);
    ui->tableView->setSelectionModel(itemmodel);
    model->setTable("studyinfo");


    //建立表格标题字符串
    model->setHeaderData(0,Qt::Horizontal,"学生号");
    model->setHeaderData(1,Qt::Horizontal,"名字");
    model->setHeaderData(2,Qt::Horizontal,"性别");
    model->setHeaderData(3,Qt::Horizontal,"学院");
    model->setHeaderData(4,Qt::Horizontal,"专业");

    //显示专业名字和学院
    model->setRelation(model->fieldIndex("College_ID"),QSqlRelation("[College Information]","College_ID","College_name"));
    model->setRelation(model->fieldIndex("Professional_ID"),QSqlRelation("[Professional Information]","Professional_ID","Professional_name"));


    //建立委托项目
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    if (!model->select()) {
        qDebug() << "Error:" << model->lastError().text();
    }

    //激活组件
    ui->action_2->setEnabled(true);
    ui->action_2->setEnabled(true);
    ui->action_3->setEnabled(true);
    ui->action_4->setEnabled(true);
    ui->action_5->setEnabled(true);
    ui->action_6->setEnabled(true);
    ui->action_7->setEnabled(true);
}


void MainWindow::on_action_7_triggered()
{
    QSqlRecord record=model->record();
    QString str;
    int sum=record.count(),i=0;
    while (i<sum) {
        str+=record.fieldName(i++)+"\n";
    }
    QMessageBox::information(this,"字段名",str);
}


void MainWindow::on_action_5_triggered()
{
    //
    ui->action_5->setEnabled(false);
    ui->action_6->setEnabled(false);

    if(!model->submitAll())
        QMessageBox::information(this,"删除数据库问题","具体原因:"+model->lastError().text());
}


void MainWindow::on_action_6_triggered()
{
    ui->action_5->setEnabled(false);
    ui->action_6->setEnabled(false);

    model->revertAll();
    qDebug()<<itemmodel->currentIndex().row();
}


void MainWindow::on_action_2_triggered()
{
    //获取最后一行数据
    insertrowColumns(model->rowCount());
}


void MainWindow::on_action_3_triggered()
{
    insertrowColumns(itemmodel->currentIndex().row());
}


void MainWindow::on_action_4_triggered()
{
    QSqlQuery qurty(QSqlDatabase::database("stydy"));

    //获取要删除的数据
    QSqlRecord record=model->record(itemmodel->currentIndex().row());
    qlonglong id=record.value(0).toLongLong();
    qurty.prepare("DELETE FROM studyinfo WHERE study_ID=:id");
    qurty.bindValue(":id",id);
    qDebug()<<id;
    qDebug()<<itemmodel->currentIndex().row();
    if(!qurty.exec())
        QMessageBox::information(this,"删除数据库问题","具体原因:"+qurty.lastError().text());
    model->select();
}


void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    ui->action_5->setEnabled(true);
    ui->action_6->setEnabled(true);
}

