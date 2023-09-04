#ifndef MENU_H
#define MENU_H

#include <QWidget>

namespace Ui
{
    class menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();

private:
    Ui::menu *ui;
};

#endif // MENU_H
