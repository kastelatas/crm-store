#include "mainwindow.h"
#include <QApplication>

#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>

#include <QCoreApplication>
#include <QTcpServer>
#include <QWebSocketServer>
#include <QWebSocket>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    // Создайте WebSocket-сервер
    QWebSocketServer server("ws://localhost:8080", QWebSocketServer::NonSecureMode);

    QHostAddress address = QHostAddress("localhost:8080");

    if (server.listen(address, 8080))
    {
        qDebug() << "WebSocket сервер запущен на порту 8080";

        QObject::connect(&server, &QWebSocketServer::newConnection, [&server]()
                         {
                             QWebSocket *socket = server.nextPendingConnection();
                             qDebug() << "Подключено новое WebSocket-соединение";

                             QDateTime currentDateTime = QDateTime::currentDateTime();

                             QJsonObject jsonObject;
                             jsonObject["type"] = "text";
                             jsonObject["time"] = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
                             jsonObject["data"] = 30;

                             socket->sendTextMessage(QJsonDocument(jsonObject).toJson()); });
    }
    else
    {
        qDebug() << "Не удалось запустить WebSocket сервер";
    }

    MainWindow w;
    w.show();
    return a.exec();
}
