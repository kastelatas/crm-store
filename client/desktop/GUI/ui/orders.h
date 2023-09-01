#ifndef ORDERS_H
#define ORDERS_H

#include <QWidget>

namespace Ui {
class orders;
}

class orders : public QWidget
{
    Q_OBJECT

public:
    explicit orders(QWidget *parent = 0);
    ~orders();

private:
    Ui::orders *ui;
};

#endif // ORDERS_H
