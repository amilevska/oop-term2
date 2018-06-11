#include "client.h"
#include<cmath>
void Client::ReadyRead()
{
    QDataStream in(mySocket);
    in.setVersion(QDataStream::Qt_4_2);
    for (;;) {
        if (!nextBlock) {
            if (mySocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> nextBlock;
        }

        if (mySocket->bytesAvailable() < nextBlock) {
            break;
        }
        QTime   time;
        QString str;
        in >> time >> str;
        QMessageBox::information(this,"Server Send",time.toString()+" "+str);
        nextBlock = 0;
    }
}

void Client::Error(QAbstractSocket::SocketError err)
{
    QString strError =
        "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                     "The host was not found." :
                     err == QAbstractSocket::RemoteHostClosedError ?
                     "The remote host is closed." :
                     err == QAbstractSocket::ConnectionRefusedError ?
                     "The connection was refused." :
                     QString(mySocket->errorString())
                    );
    //myText->append(strError);
    QMessageBox::information(this,"ERROR!",strError);
    exit(1);
}
void Client::SendToServer()
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);
    out <<quint16() << QTime::currentTime()<<norm;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    mySocket->write(arrBlock);
    mySocket->flush();
}
void Client::onConnected()
{
    QMessageBox::information(this,"connect..","Received the connected() signal");
}
Client::Client(const QString &strHost, int Port, QWidget *parent):QWidget(parent),nextBlock(0)
{
    mySocket =new QTcpSocket(this);
    mySocket->connectToHost(strHost,Port);
    connect(mySocket,SIGNAL(connected()),this,SLOT(onConnected()));
    connect(mySocket,SIGNAL(readyRead()),this,SLOT(ReadyRead()));
    connect(mySocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(Error(QAbstractSocket::SocketError)));
    button=new QPushButton("Коло");
    button2=new QPushButton("Квадрат");
    button3=new QPushButton("Лінія");
    //button4=new QPushButton("точка");
    connect(button,SIGNAL(clicked(bool)),this,SLOT(on_clicked1()));
    connect(button,SIGNAL(clicked(bool)),this,SLOT(SendToServer()));
    connect(button2,SIGNAL(clicked(bool)),this,SLOT(on_clicked2()));
    connect(button2,SIGNAL(clicked(bool)),this,SLOT(SendToServer()));
    connect(button3,SIGNAL(clicked(bool)),this,SLOT(on_clicked3()));
    connect(button3,SIGNAL(clicked(bool)),this,SLOT(SendToServer()));
   // connect(button4,SIGNAL(clicked(bool)),this,SLOT(on_clicked4()));
    //connect(button4,SIGNAL(clicked(bool)),this,SLOT(SendToServer()));
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
       pvbxLayout->addWidget(new QLabel("<H1>Client</H1>"));
       pvbxLayout->addWidget(button);
       pvbxLayout->addWidget(button2);
       pvbxLayout->addWidget(button3);
      // pvbxLayout->addWidget(button4);
       setLayout(pvbxLayout);
}

void Client::on_clicked1()
{
    norm=1;

}
void Client::on_clicked2()
{
    norm=2;
}

void Client::on_clicked3()
{
    norm=3;
}

void Client::on_clicked4()
{
    norm=4;
}

