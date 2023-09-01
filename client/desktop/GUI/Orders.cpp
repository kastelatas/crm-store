#include "Orders.h"
#include "ui_orders.h"

Orders::Orders(QWidget *parent) : QWidget(parent),
                                  ui(new Ui::orders)
{
    ui->setupUi(this);
    this->setWindowTitle("Заказы");
    this->hide();
}

Orders::~Orders()
{
    delete ui;
}
