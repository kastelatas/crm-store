#include "ingredients.h"
#include "ui_ingredients.h"

ingredients::ingredients(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ingredients)
{
    ui->setupUi(this);
}

ingredients::~ingredients()
{
    delete ui;
}
