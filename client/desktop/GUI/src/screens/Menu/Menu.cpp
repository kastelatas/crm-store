#include "Menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) : QWidget(parent),
                              ui(new Ui::menu)
{
    ui->setupUi(this);
    this->setWindowTitle("Меню");
    this->hide();
}

Menu::~Menu()
{
    delete ui;
}
