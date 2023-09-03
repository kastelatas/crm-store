#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>

namespace Ui
{
    class calculator;
}

enum class PriceUnit
{
    UAH_PER_KG,
    UAH_PER_LITER,
    UAH_PER_UNIT
};

enum class QuantityUnit
{
    KILOGRAMM,
    GRAMM,
    LITER,
    MILLILITER,
    UNIT
};

struct Ingredient
{
    QString name;
    float quantity;
    QuantityUnit quantityUnit;
    float price;
    PriceUnit priceUnit;
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
    void changeTab(int index);
    void addIngridient();

private:
    QComboBox *createQuantityUnitsComboBox();
    QComboBox *createPriceUnitsComboBox();
    QComboBox *createIngridientsComboBox();
    QPushButton *createDeleteButton();
    float coefficient(PriceUnit priseUnit, QuantityUnit quantityUnit) const;
    void updateDataInIngridientsComboBox();
    void writeToFile();
    void readFromFile();

    Ui::calculator *mUi;
    QVector<QString> mIngredients;
};

Q_DECLARE_METATYPE(PriceUnit)
Q_DECLARE_METATYPE(QuantityUnit)

#endif // CALCULATOR_H
