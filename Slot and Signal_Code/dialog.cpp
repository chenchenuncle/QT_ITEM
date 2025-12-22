#include "dialog.h"

void Dialog::iniu()
{
    chekcbokunder=new QCheckBox("下划线");
    chekcbokitalic=new QCheckBox("斜体");
    chekcboxbold=new QCheckBox("粗体");
    QHBoxLayout *vlay1=new QHBoxLayout;
    vlay1->addWidget(chekcbokunder);
    vlay1->addWidget(chekcbokitalic);
    vlay1->addWidget(chekcboxbold);

    radioblack=new QRadioButton("黑色");
    radiobule=new QRadioButton("蓝色");
    radiorad=new QRadioButton("红色");
    QHBoxLayout *vlay2=new QHBoxLayout;
    vlay2->addWidget(radioblack);
    vlay2->addWidget(radiobule);
    vlay2->addWidget(radiorad);

    pushok=new QPushButton("确定");
    pushcancel=new QPushButton("清除");
    pushclose=new QPushButton("退出");
    QHBoxLayout *vlay3=new QHBoxLayout;
    vlay3->addWidget(pushok);
    vlay3->addWidget(pushcancel);
    vlay3->addWidget(pushclose);

    txtEdit=new QPlainTextEdit;
    txtEdit->setPlainText("hoold\n手工建设");
    QFont font=txtEdit->font();
    font.setPixelSize(20);
    QPalette palette=txtEdit->palette();
    palette.setColor(QPalette::Text,"#aaff7f");
    txtEdit->setFont(font);
    txtEdit->setPalette(palette);

    QVBoxLayout*vlay4=new QVBoxLayout(this);
    vlay4->addLayout(vlay1);
    vlay4->addLayout(vlay2);
    vlay4->addWidget(txtEdit);
    vlay4->addLayout(vlay3);
    setLayout(vlay4);

}

inline void Dialog::inisignalslots()
{
    connect(chekcbokunder,SIGNAL(clicked(bool)),this,SLOT(do_chkcbokunder(bool)));
    connect(chekcbokitalic,SIGNAL(clicked(bool)),this,SLOT(do_checbokitalic(bool)));
    connect(chekcboxbold,SIGNAL(clicked(bool)),this,SLOT(do_checbokboxdold(bool)));
    connect(radioblack,SIGNAL(clicked()),this,SLOT(do_setFontColor()));
    connect(radiobule,SIGNAL(clicked()),this,SLOT(do_setFontColor()));
    connect(radiorad,SIGNAL(clicked()),this,SLOT(do_setFontColor()));
    connect(pushok,SIGNAL(clicked()),this,SLOT(accept()));
    connect(pushcancel,SIGNAL(clicked()),this,SLOT(do_btncancel()));
    connect(pushclose,SIGNAL(clicked()),this,SLOT(close()));
}
void Dialog::do_chkcbokunder(bool checked)
{
    QFont font=txtEdit->font();
    font.setUnderline(checked);
    txtEdit->setFont(font);
}

void Dialog::do_checbokitalic(bool checked)
{
    QFont font=txtEdit->font();
    font.setItalic(checked);
    txtEdit->setFont(font);
}

void Dialog::do_checbokboxdold(bool checked)
{
   QFont font=txtEdit->font();
   font.setBold(checked);
   txtEdit->setFont(font);
}

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
     iniu();
     inisignalslots();
     setWindowTitle("手工建设");
}

Dialog::~Dialog() {}


void Dialog::do_setFontColor()
{
   QPalette palette=txtEdit->palette();
   if(radioblack->isChecked())
   palette.setColor(QPalette::Text,Qt::black);
   else if(radiobule->isChecked())
   palette.setColor(QPalette::Text,Qt::blue);
   else if(radiorad->isChecked())
   palette.setColor(QPalette::Text,Qt::red);
   else
   palette.setColor(QPalette::Text,Qt::green);
   txtEdit->setPalette(palette);
}

void Dialog::do_btncancel()
{
   txtEdit->clear();
}

