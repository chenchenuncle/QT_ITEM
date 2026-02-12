#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include <QDir>
#include <QFileDialog>
#include <QInputDialog>
#include <QFileInfo>
#include <QTemporaryFile>
#include <QTemporaryDir>

bool Dialog::isDocument()//还没有实现接口
{
    return true;
}

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Widget);
    wathcer=new QFileSystemWatcher;
    connect(wathcer,&QFileSystemWatcher::directoryChanged,ui->plainTextEdit,&QPlainTextEdit::appendPlainText);
    connect(wathcer,&QFileSystemWatcher::fileChanged,ui->plainTextEdit,&QPlainTextEdit::appendPlainText);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_4_clicked()
{
    QString str=QFileDialog::getExistingDirectory(this);
    if(str.isEmpty())
        return ;
    QCoreApplication::addLibraryPath(str);
    ui->plainTextEdit->appendPlainText("QCoreApplication::addLibraryPath():添加了搜索目录为："+str+'\n');
}


void Dialog::on_pushButton_5_clicked()
{
    ui->plainTextEdit->appendPlainText("返回执行文件目录："+QCoreApplication::applicationDirPath()+'\n');
}


void Dialog::on_pushButton_8_clicked()
{
    ui->plainTextEdit->appendPlainText("返回执行文件路径和文件名:"+QCoreApplication::applicationFilePath()+'\n');
}


void Dialog::on_pushButton_9_clicked()
{
    ui->plainTextEdit->appendPlainText("返回程序名称："+QCoreApplication::applicationName()+'\n');
}



void Dialog::on_pushButton_6_clicked()
{
    ui->plainTextEdit->appendPlainText("应用程序的组织名称:"+QCoreApplication::organizationName()+'\n');
}


void Dialog::on_pushButton_7_clicked()
{
    ui->plainTextEdit->appendPlainText("退出程序:");
    QCoreApplication::exit();
}


void Dialog::on_pushButton_10_clicked()
{
    QFile file(ui->lineEdit->text());
    if(file.exists())
        ui->plainTextEdit->appendPlainText("文件存在\n");
    else
        ui->plainTextEdit->appendPlainText("不存在改文件\n");
    file.close();
}


void Dialog::on_pushButton_11_clicked()
{
    QString str;
    if(QFile::moveToTrash(ui->lineEdit->text(),&str))
        ui->plainTextEdit->appendPlainText("已回收+文件路径+"+str+'\n');
    else
        ui->plainTextEdit->appendPlainText("回收失败！\n");
}


void Dialog::on_pushButton_12_clicked()
{
    QFile file(ui->lineEdit->text());
    if(!file.open(QIODeviceBase::WriteOnly|QIODeviceBase::Text)) return;
    ui->plainTextEdit->appendPlainText(QString().asprintf("文件大小为%d字节\n",(int)file.size()));
}


void Dialog::on_pushButton_13_clicked()
{
    if(QFile::remove(ui->lineEdit->text()))
        ui->plainTextEdit->appendPlainText("删除成功\n");
    else
        ui->plainTextEdit->appendPlainText("删除失败！\n");
}


void Dialog::on_pushButton_14_clicked()
{
    QString oldPath = ui->lineEdit->text();
    QString newName = QInputDialog::getText(this, "输入框", "请输入新文件名") + ".txt";

    // 提取原文件的目录路径
    QFileInfo fileInfo(oldPath);
    QString dirPath = fileInfo.absolutePath();  // 获取目录部分

    // 构建新的完整路径（在原目录中）
    QString newPath = dirPath + "/" + newName;

    if(QFile::rename(oldPath, newPath))
        ui->plainTextEdit->appendPlainText("修改文件名成功\n");
    else
        ui->plainTextEdit->appendPlainText("没有成功修改\n");
}


void Dialog::on_pushButton_15_clicked()
{
    QFileInfo file(ui->lineEdit_2->text());
    ui->plainTextEdit->appendPlainText("返回文件名.第一个前面的名字"+file.baseName()+'\n');
}


void Dialog::on_pushButton_16_clicked()
{
    QFileInfo file(ui->lineEdit_2->text());
    ui->plainTextEdit->appendPlainText("文件名创建日期和时间"+file.birthTime().toString()+'\n');
}


void Dialog::on_pushButton_17_clicked()
{
    QFileInfo file(ui->lineEdit_2->text());
    ui->plainTextEdit->appendPlainText("文件名（如果是目录路径,返回空字符|不包含后缀名）"+file.baseName()+'\n');
}


void Dialog::on_pushButton_18_clicked()
{
    QFileInfo file(ui->lineEdit_2->text());
    if(file.exists())
    ui->plainTextEdit->appendPlainText("确定目录右侧输入栏“目录路径（文件）是否存在:在");
    else
        ui->plainTextEdit->appendPlainText(("确定目录右侧输入栏“目录路径（文件）是否存在:不在"));
}


void Dialog::on_pushButton_19_clicked()
{
    QFileInfo file(ui->lineEdit_2->text());
    ui->plainTextEdit->appendPlainText("文件名（如果是目录路径,返回空字符)"+file.fileName()+'\n');
}


void Dialog::on_pushButton_20_clicked()
{
    QFileInfo file(ui->lineEdit_2->text());
    ui->plainTextEdit->appendPlainText("返回目录路径（包含本次目录名）"+file.filePath()+'\n');
}


void Dialog::on_pushButton_21_clicked()
{

    QFileInfo file(ui->lineEdit_2->text());
ui->plainTextEdit->appendPlainText("文件大小（字节，如果是目录或者文件没有内容为0）:"+QString("%1").arg(file.size())+'\n');
}

void Dialog::on_pushButton_22_clicked()
{

    QFileInfo file(ui->lineEdit_2->text());
    ui->plainTextEdit->appendPlainText("返回文件名后缀名(如果是目录，返回空字符)："+file.baseName()+'\n');
}

void Dialog::on_pushButton_23_clicked()
{
    ui->plainTextEdit->appendPlainText("在目录右侧建立右侧文件名(2边输入栏其一没有文件名或者目录)\n");
    QDir::addSearchPath(QDir(ui->lineEdit_2->text()).canonicalPath(),ui->lineEdit->text());
}


void Dialog::on_pushButton_24_clicked()
{
    ui->plainTextEdit->appendPlainText("返回应用程序的当前目录");
    ui->plainTextEdit->appendPlainText(QDir::currentPath()+'\n');
}


void Dialog::on_pushButton_25_clicked()
{
    ui->plainTextEdit->appendPlainText("返回根目录列表:");
    QFileInfoList list=QDir::drives();
    for(auto &i:list)
        ui->plainTextEdit->appendPlainText(i.absoluteFilePath());
}


void Dialog::on_pushButton_26_clicked()
{
    ui->plainTextEdit->appendPlainText("返回主目录绝对路径");
    ui->plainTextEdit->appendPlainText(QDir::homePath()+'\n');
}


void Dialog::on_pushButton_27_clicked()
{
    ui->plainTextEdit->appendPlainText("返回根绝对路径");
    ui->plainTextEdit->appendPlainText(QDir::rootPath()+'\n');
}


void Dialog::on_pushButton_28_clicked()
{
    ui->plainTextEdit->appendPlainText("修改目录名");
    QDir dir(ui->lineEdit_2->text());
    if(dir.cd(QInputDialog::getText(this,"输入框","请输入新的目录文件名")))
        ui->plainTextEdit->appendPlainText("修改成功\n");
    else
        ui->plainTextEdit->appendPlainText("修改失败\n");
}


void Dialog::on_pushButton_29_clicked()
{
    ui->plainTextEdit->appendPlainText("目录列表的目录和文件");
    QDir dir(ui->lineEdit_2->text());
    QStringList list=dir.entryList();
    for(auto i:list)
        ui->plainTextEdit->appendPlainText(i);
}


void Dialog::on_pushButton_30_clicked()
{

    ui->plainTextEdit->appendPlainText("删除目录中文件");
    QDir dir(ui->lineEdit_2->text());
    if(dir.remove(ui->lineEdit->text()))
        ui->plainTextEdit->appendPlainText("删除成功");
    else
        ui->plainTextEdit->appendPlainText("删除失败");
}

void Dialog::on_pushButton_clicked()
{
    QString str=QFileDialog::getExistingDirectory(this,"",QDir::currentPath());
    ui->lineEdit_2->setText(str);
}


void Dialog::on_pushButton_2_clicked()
{
    QString str=QFileDialog::getOpenFileName(this,"",QDir::currentPath());
    ui->lineEdit->setText(str);
}


void Dialog::on_pushButton_31_clicked()
{
    QTemporaryDir dir("D:/QT练习/Reading_and_Writing_Systems_and_Files/Test Area/xxxxx");

}


void Dialog::on_pushButton_32_clicked()
{
    QTemporaryDir dir("D:/QT练习/Reading_and_Writing_Systems_and_Files/Test Area/");
    dir.setAutoRemove(false);
    if(dir.isValid())
        ui->plainTextEdit->appendPlainText("成功建立");
    else
        ui->plainTextEdit->appendPlainText("建立失败\n"+dir.errorString());
}


void Dialog::on_pushButton_33_clicked()
{
    QTemporaryFile file("D:/QT练习/Reading_and_Writing_Systems_and_Files/Test Area/sdhisdgi.txt");
}


void Dialog::on_pushButton_34_clicked()
{
    QTemporaryFile file("D:/QT练习/Reading_and_Writing_Systems_and_Files/Test Area/");
    file.setAutoRemove(false);
    if(!file.open())
        return ;
    if(file.exists())
        ui->plainTextEdit->appendPlainText("建立成功");
    else
        ui->plainTextEdit->appendPlainText("建立失败");
    file.close();
}


void Dialog::on_pushButton_35_clicked()
{
    if(wathcer==nullptr)
    {
        wathcer=new QFileSystemWatcher;
        ui->plainTextEdit->appendPlainText("开始监视\n");
    }
    else
    {
        ui->plainTextEdit->appendPlainText("已经监视\n");
    }
}


void Dialog::on_pushButton_36_clicked()
{
    if(wathcer!=nullptr)
    {
        delete wathcer;
        wathcer=nullptr;
        ui->plainTextEdit->appendPlainText("结束监视\n");
    }
    else
        ui->plainTextEdit->appendPlainText("已经结束监视\n");
}


void Dialog::on_pushButton_37_clicked()
{
    if(wathcer==nullptr)
        return ;
    if(wathcer->addPath(ui->lineEdit->text()))
        ui->plainTextEdit->appendPlainText("已经添加监听文件\n");
    else
        ui->plainTextEdit->appendPlainText("添加失败\n");
}


void Dialog::on_pushButton_38_clicked()
{
    if(wathcer==nullptr)
        return ;
    if(wathcer->addPath(ui->lineEdit_2->text()))
        ui->plainTextEdit->appendPlainText("已经添加监听目录\n");
    else
        ui->plainTextEdit->appendPlainText("添加失败\n");
}

