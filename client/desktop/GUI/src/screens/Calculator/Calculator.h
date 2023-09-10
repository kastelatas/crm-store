#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QSignalMapper>

#include "common/enums/IngridientsServiceEnums.hpp"
#include "common/structs/IngridientsServiceStructs.hpp"

namespace Ui
{
    class calculator;
}

enum class TableID
{
    CALC_TABLE,
    INGRIDIENTS_TABLE
};

class Calculator : public QWidget
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = 0);
    ~Calculator();

public slots:
    void addNewIngridient();
    void calcCost();
    void changeTab(int index);
    void addIngridient();
    void clearCalcTable();
    void onDeleteCalcButtonClicked();
    void onDeleteIngridientButtonClicked();
    void writeToPDF();

private:
    QComboBox *createQuantityUnitsComboBox();
    QComboBox *createPriceUnitsComboBox();
    QComboBox *createIngridientsComboBox();
    QPushButton *createDeleteButton(TableID tableId);
    float coefficient(PriceUnit priseUnit, QuantityUnit quantityUnit) const;
    void updateDataInIngridientsComboBox();
    void writeToFile();
    void readFromFile();
    void updateIngridientTable();
    bool checkUnitSimile(PriceUnit priceUnit, QuantityUnit quantityUnit);

    Ui::calculator *mUi;
    QVector<Ingredient> mDish;
    QVector<QString> mIngredients;
    QSignalMapper *deleteButtonMapper;
};

Q_DECLARE_METATYPE(PriceUnit)
Q_DECLARE_METATYPE(QuantityUnit)

#endif // CALCULATOR_H
