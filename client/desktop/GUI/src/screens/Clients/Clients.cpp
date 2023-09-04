#include "Clients.h"
#include "ui_Clients.h"

Clients::Clients(QWidget *parent) : QWidget(parent),
                                    ui(new Ui::clients)
{
    ui->setupUi(this);
    this->setWindowTitle("Клиенты");
    this->hide();
}

Clients::~Clients()
{
    delete ui;
}
