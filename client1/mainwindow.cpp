#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <ctime>
#include <random>
#include <QLayout>
#include <QDebug>
#include <string.h>
#include <QPushButton>

using namespace std;
QString ar[81];
int k;
int aa=0;
QList<QPushButton *> *buttons = new QList<QPushButton *>();
QList<QPushButton *> *buttons_2 = new QList<QPushButton *>();
//QString ar [9][9];


int victory_counter=0;
MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::MainWindow)
{
ui->setupUi(this);
QWidget::setFixedWidth(930);
QWidget::setFixedHeight(558);
socket = new QTcpSocket(this);
connect(socket, SIGNAL(readyRead()), this, SLOT(sockReady()));
connect(socket, SIGNAL(disconnected()), this, SLOT(sockDisc()));
socket->connectToHost("127.0.0.1",5555);
for(int i = 0; i < 9; i++)
{
for(int j = 0; j <9; j++){
    const string chlen = to_string(i*9+j);
   QString hui = QString::fromStdString(chlen);
   const QString a = hui ;
QPushButton *b = new QPushButton(a, this);
ui->bb->addWidget(b, i, j);
b->setObjectName(a);
b->setStyleSheet("QPushButton{"
                 "border: 2 pix solid #000000;"
                 "position: relative;"
                 "padding: 6px 8px;"
                 "margin: 4px;"
                 "text-align: center;"
                 "vertical-align: middle;"
                 " color: #ffffff;"
                 "background-color: #000000;"
                 "}"
                 ""
                 "QPushButton:enabled{"
                 "background-color: #c540c5;"
                 "}"
                 );

;
b->setEnabled(false);

connect(b, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
buttons->append(b);
}}
for(int i = 0; i < 3; i++)
{
for(int j = 0; j <3; j++){
    const string vagina = to_string(i*3+j+1);
   QString pizda = QString::fromStdString(vagina);
   const QString a = pizda;
QPushButton *c = new QPushButton(a, this);
ui->kk->addWidget(c, i, j);
c->setObjectName(a);
connect(c, SIGNAL(clicked()), this, SLOT(on_pushButton2_clicked()));
buttons_2->append(c);
}}
for(int i = 0; i < buttons->size(); i++)
{
buttons->at(i)->setFixedSize(62,62);
ui->bb->setSpacing(0);
}

for(int i = 0; i < buttons_2->size(); i++)
{
buttons_2->at(i)->setFixedSize(100,100);
ui->kk->setSpacing(0);
}
}

MainWindow::~MainWindow()
{
delete ui;
}


void MainWindow::on_pushButton2_clicked()
{
aa= QObject::sender()->objectName().toInt();

}

void MainWindow::on_pushButton_clicked()
{
    const string vagina = to_string(aa);
   QString pizda = QString::fromStdString(vagina);
   const QString a = pizda;

    buttons->at( QObject::sender()->objectName().toInt())->setText(a);

    k=(QObject::sender()->objectName().toInt());



    if(a.toInt()==ar[k].toInt()){
        const string vagina = to_string(aa);
       QString pizda = QString::fromStdString(vagina);
       const QString a = pizda;
        buttons->at( QObject::sender()->objectName().toInt())->setText(a);
        buttons->at( QObject::sender()->objectName().toInt())->setEnabled(false);
        victory_counter--;
        if( victory_counter<=0){
            if(socket->readAll()=="0"){
                QMessageBox::information(this,"Поражение","Вы проиграли!");
                 close();
            }
            QMessageBox::information(this,"Победа","Вы победили!");
            Data="1";
            socket->write(Data);
           close();
        }
}
}
void MainWindow::sockDisc()
{
    socket->deleteLater();
}
void MainWindow::sockReady()
{
    if (socket->waitForConnected(500))
{
        socket->waitForReadyRead(500);
        Data = socket->readAll();
        QString DataAsString = QTextCodec::codecForMib(106)->toUnicode(Data);
        for(int i=0;i<81;i++){
            ar[i]=DataAsString.at(i+81);
            if(DataAsString.at(i)==1){
            buttons->at(i)->setEnabled(true);
            buttons->at(i)->setText(0);
            victory_counter++;
            }
            else {
            buttons->at(i)->setText(DataAsString.at(i+81));
            }
        }

    }
}
