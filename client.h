#ifndef CLIENT_H
#define CLIENT_H
#include<QWidget>
#include<QTcpSocket>
#include<QPushButton>
#include<QVBoxLayout>
#include<QLabel>
#include<QDebug>
#include<QDataStream>
#include<QString>
#include<QTime>
#include<QMessageBox>
class Client : public QWidget
{
    Q_OBJECT
public:
    explicit Client(const QString& strHost,int Port,QWidget *parent = 0);
signals:
private:
    QPushButton *button;
    QPushButton *button2;
    QPushButton *button3;
    QTcpSocket* mySocket;
    quint16 nextBlock;
    int norm;
private slots:
    void on_clicked1();
    void on_clicked2();
    void on_clicked3();
    void on_clicked4();
    void onConnected();
    void ReadyRead();
    void Error(QAbstractSocket::SocketError err);
    void SendToServer();
};

#endif // CLIENT_H
