#include "server.h"


void Server::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setPen(QPen(Qt::black,1,Qt::SolidLine));
    switch(num1){
    case 1:
        painter.drawEllipse(QRect(170,170,150,150));
        break;
    case 2:
        painter.drawRect(QRect(170,170,150,150));
        break;
    case 3:
        painter.drawLine(170,170,100,100);
        break;

    }
}
void Server::SendToClient(QTcpSocket *mySocket, const QString &str )
{
    QByteArray mBlock;
    QDataStream out(&mBlock,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);
        out << quint16(0) << QTime::currentTime() << str;
        out.device()->seek(0);
        out << quint16(mBlock.size() - sizeof(quint16));
        mySocket->write(mBlock);
}
void Server::newConnected()
{
   QTcpSocket *mySocket=myServer->nextPendingConnection();
   connect(mySocket,SIGNAL(disconnected()),mySocket,SLOT(deleteLater()));
   connect(mySocket,SIGNAL(readyRead()),this,SLOT(readClient()));
   SendToClient(mySocket,"Connected...");
}

void Server::readClient()
{

    QTcpSocket *mySocket=(QTcpSocket*) sender();
    QDataStream in(mySocket);
    qDebug()<<mySocket;
    for (;;) {
            if (!nextBlock) {
                if (mySocket->bytesAvailable() < sizeof(quint16)) {
                    break;
                }
                in >> nextBlock;
            }
     if(mySocket->bytesAvailable()<nextBlock)break;
     QTime time =time1;
    // qreal num3;
             in >> time1 >> num1;//>>num3;
                //int teta=time1.msec()-time.msec();
                repaint();
             nextBlock = 0;
             mySocket->waitForBytesWritten(3000);
             switch(num1){
                case 1:
             SendToClient(mySocket, "малює коло");
                 break;
             case 2:
                 SendToClient(mySocket, "малює квадрат");
                 break;
             case 3:
                 SendToClient(mySocket, "малює лінію");
    }
    }
}

Server::Server(int mPort,QWidget *parent ):QWidget(parent),nextBlock(0)
{
    QHostAddress *host=new QHostAddress("192.168.0.104");
   myServer=new QTcpServer(this);
   //myServer->listen(host->Broadcast,1212);
   qDebug()<<myServer->serverAddress();
   if(!myServer->listen(host->Any,mPort))
   {
       QMessageBox::critical(parent,"Error",myServer->errorString());
       myServer->close();
        return;
   }
   else {
       QMessageBox::information(parent,"connected","Server is start");
   }
   connect(myServer,SIGNAL(newConnection()),this,SLOT(newConnected()));

}
