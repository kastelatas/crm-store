#include "Ingredients.h"
#include "ui_ingredients.h"

Ingredients::Ingredients(QWidget *parent) : QWidget(parent),
                                            ui(new Ui::ingredients)
{
    ui->setupUi(this);
    this->setWindowTitle("Ингредиенты");
    this->hide();
}

Ingredients::~Ingredients()
{
    delete ui;
}
