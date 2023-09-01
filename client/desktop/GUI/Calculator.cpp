#include "Calculator.h"
#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent) : QWidget(parent),
                                          ui(new Ui::calculator)
{
    ui->setupUi(this);
    this->setWindowTitle("Калькулятор");
    this->hide();
}

Calculator::~Calculator()
{
    delete ui;
}
