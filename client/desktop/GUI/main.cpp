#include "mainwindow.h"
#include <QApplication>

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
            // Обработка нового WebSocket-соединения
            QWebSocket *socket = server.nextPendingConnection();
            qDebug() << "Подключено новое WebSocket-соединение";

            // Отправка логов клиенту (пример)
            socket->sendTextMessage("Привет, это WebSocket-сервер!"); });
    }
    else
    {
        qDebug() << "Не удалось запустить WebSocket сервер";
    }

    MainWindow w;
    w.show();
    return a.exec();
}
