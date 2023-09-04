#ifndef ORDERS_H
#define ORDERS_H

#include <QWidget>

namespace Ui
{
    class orders;
}

class Orders : public QWidget
{
    Q_OBJECT

public:
    explicit Orders(QWidget *parent = 0);
    ~Orders();

private:
    Ui::orders *ui;
};

#endif // ORDERS_H
