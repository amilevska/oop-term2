#ifndef SERVER_H
#define SERVER_H
#include<QTcpServer>
#include<QWidget>
#include<QTcpSocket>
#include<QTextEdit>
#include<QString>
#include<QMessageBox>
#include<QLabel>
#include<QVBoxLayout>
#include<QDataStream>
#include<QTime>
#include<QPainter>s
#include<cmath>
class Server : public QWidget
{
  Q_OBJECT
protected:
    void paintEvent(QPaintEvent * event);
private:
    QTcpServer *myServer;
    QTextEdit *myData;
    quint16  nextBlock;
    QTime time1;
    int num1;
    void SendToClient(QTcpSocket *, const QString & );
public slots:
    void newConnected();
    void readClient();
public:
    Server(int mPort,QWidget *parent =0);
};
#endif // SERVER_H
