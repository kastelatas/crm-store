#ifndef CLIENTS_H
#define CLIENTS_H

#include <QWidget>

namespace Ui {
class clients;
}

class clients : public QWidget
{
    Q_OBJECT

public:
    explicit clients(QWidget *parent = 0);
    ~clients();

private:
    Ui::clients *ui;
};

#endif // CLIENTS_H
