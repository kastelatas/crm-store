#include "clients.h"
#include "ui_clients.h"

clients::clients(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clients)
{
    ui->setupUi(this);
}

clients::~clients()
{
    delete ui;
}
