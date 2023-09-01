#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>

namespace Ui
{
    class calculator;
}

class Calculator : public QWidget
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = 0);
    ~Calculator();

private:
    Ui::calculator *ui;
};

#endif // CALCULATOR_H
