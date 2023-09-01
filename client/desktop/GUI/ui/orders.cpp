#include "orders.h"
#include "ui_orders.h"

orders::orders(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::orders)
{
    ui->setupUi(this);
}

orders::~orders()
{
    delete ui;
}
