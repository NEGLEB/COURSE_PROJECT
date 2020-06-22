#include "myserver.h"
#include <ctime>
#include <iostream>
#include <random>
#include <string.h>
using namespace std;
myserver::myserver(){}

myserver::~myserver(){}
QString ar [9][9];
QString br [9][9];
void myserver::startServer()
{
    if (this->listen(QHostAddress::Any,5555))
    {
        qDebug()<<"Listening";

    }
    else
    {
        qDebug()<<"Not listening";
    }
}

void myserver::incomingConnection(qintptr socketDescriptor)
{
    socket[counter] = new QTcpSocket(this);
    socket[counter]->setSocketDescriptor(socketDescriptor);

        connect(socket[counter],SIGNAL(readyRead()),this,SLOT(sockReady()));
        connect(socket[counter],SIGNAL(disconnected()),this,SLOT(sockDisc()));

    qDebug()<<socketDescriptor<<" Client connected";


    qDebug()<<"Send client connect status - YES";
    counter++;
    if(counter>=2){

       gameStart();
    }

}

void myserver::sockReady()
{

        for(int i=0;i<2;i++){
            if(socket[i]->readAll()=="1"){
                socket[i%2]->write("0");
                close();
            }
        }

}

void myserver::sockDisc()
{
    qDebug()<<"Disconnect";
    socket[counter]->deleteLater();
    counter--;
}
void myserver::gameStart()
{
    mt19937 mersenne(static_cast<unsigned int>(time(0)));
    int counter=1;
    int lagger = 9;
    for (int i = 0; i < 9 ; i++)
    {
    for (int j = 0; j < 9 ; j++)
    {const string pipiska = to_string(counter);
        QString genitalii = QString::fromStdString(pipiska);
    ar[i][j]=genitalii;
    if (lagger==counter){
    lagger--;
    counter --;
    }counter++;
    if (counter == 10)
    {counter =1;}
    }
    }



    for(int i=0;i<9;i++){
        qSwap(ar[i][1],ar[i][3]);
        qSwap(ar[i][2],ar[i][6]);
        qSwap(ar[i][5],ar[i][7]);

    }
    int rand1=mersenne();
//    int cycle_holder=mersenne();
//    for(int i=0;i<cycle_holder%7;i++){
//        for(int j=0;j<3;j++){
//            for(int k=0;k<9;k++){
//            qSwap(ar[k][j],ar[k][(j+rand1%2)*2]);
//            }
//            rand1=mersenne();
//        }

//    }
//    rand1=mersenne();
//    cycle_holder=mersenne();
//    for(int i=0;i<cycle_holder%7;i++){
//        for(int j=0;j<3;j++){
//            for (int k=0;k<9;k++){
//            qSwap(ar[j][k],ar[(j+rand1%2)*2][k]);
//            }
//            rand1=mersenne();
//        }

//    }
//    rand1=mersenne();
//    cycle_holder=mersenne();
//    for(int i=0;i<3;i++){
//        for(int j=0;j<rand1%7;j++){
//            for(int k=0;k<9;k++){
//            qSwap(ar[k][i+rand1%2],ar[k][i+cycle_holder%2]);
//            }
//        }
//    }
//    rand1=mersenne();
//    cycle_holder=mersenne();
//    for(int i=0;i<3;i++){
//        for(int j=0;j<rand1%7;j++){
//            for(int k=0;k<9;k++){
//            qSwap(ar[i+rand1%2][k],ar[i+cycle_holder%2][k]);
//            }
//        }
//    }
    rand1=mersenne();
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(rand1%2==0){
               br[i][j]=1;
               rand1=mersenne();
            }
            else {br[i][j]=2;
            rand1=mersenne();
            }
        }
    }

    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            for(int k=0;k<2;k++){
                Data.append(br[i][j].toUtf8());
            }
        }
    }
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            for(int k=0;k<2;k++){
                Data.append(ar[i][j].toUtf8());
            }
        }
    }

    for(int k=0;k<2;k++){
        socket[k]->write(Data);
      }



}
