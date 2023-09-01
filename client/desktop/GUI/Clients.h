#ifndef CLIENTS_H
#define CLIENTS_H

#include <QWidget>

namespace Ui
{
    class clients;
}

class Clients : public QWidget
{
    Q_OBJECT

public:
    explicit Clients(QWidget *parent = 0);
    ~Clients();

private:
    Ui::clients *ui;
};

#endif // CLIENTS_H
