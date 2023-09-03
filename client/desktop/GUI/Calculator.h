#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QComboBox>

namespace Ui
{
    class calculator;
}

struct Ingredient
{
    QString name;
    QString quantity;
    QString unity;
    QString price;
};

class Calculator : public QWidget
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = 0);
    ~Calculator();

public slots:
    void addNewIngridient();
    void copyLayout(QLayout *sourceLayout, QLayout *targetLayout);
    void calcCost();
    void removeIngridient(const QModelIndex &index);
    QComboBox *createComboBoxWithUnity();

private:
    Ui::calculator *mUi;
};

#endif // CALCULATOR_H
