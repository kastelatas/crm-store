#include "Calculator.h"
#include "ui_calculator.h"
#include <QDebug>

Calculator::Calculator(QWidget *parent) : QWidget(parent),
                                          mUi(new Ui::calculator)
{
    mUi->setupUi(this);
    this->setWindowTitle("Калькулятор");
    this->hide();

    if (mUi != NULL)
    {
        mUi->calcTableWidget->setRowCount(1);
        mUi->calcTableWidget->setColumnCount(5);

        mUi->calcTableWidget->setHorizontalHeaderLabels({
                        "Название",
                        "Кол-во в", "Един. измерения",
                        "Цена за", "Един. измерения"
                    });

        QHeaderView *header = mUi->calcTableWidget->horizontalHeader();

        // Устанавливаем режим растяжения для каждой колонки
        for (int col = 0, count = mUi->calcTableWidget->columnCount(); col < count; ++col)
        {
            header->setSectionResizeMode(col, QHeaderView::Stretch);
        }

        mUi->calcTableWidget->setCellWidget(0, 4, createPriceUnitsComboBox());
        mUi->calcTableWidget->setCellWidget(0, 2, createQuantityUnitsComboBox());

        mUi->calcTableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);

        connect(mUi->addIngridient, SIGNAL(clicked()), this, SLOT(addNewIngridient()));
        connect(mUi->calcCost, SIGNAL(clicked()), this, SLOT(calcCost()));
        connect(mUi->calcTableWidget, SIGNAL(clicked(const QModelIndex &index)), this, SLOT(removeIngridient(const QModelIndex &index)));
    }
}

Calculator::~Calculator()
{
    delete mUi;
}

void Calculator::addNewIngridient()
{
    const int rowCount = mUi->calcTableWidget->rowCount(); // Получаем текущее количество строк

    mUi->calcTableWidget->insertRow(rowCount); // Добавляем новую строку
    mUi->calcTableWidget->setCellWidget(rowCount, 4, createPriceUnitsComboBox());
    mUi->calcTableWidget->setCellWidget(rowCount, 2, createQuantityUnitsComboBox());
}

void Calculator::copyLayout(QLayout *sourceLayout, QLayout *targetLayout)
{
    for (int i = 0; i < sourceLayout->count(); ++i)
    {
        QLayoutItem *item = sourceLayout->itemAt(i);
        if (item)
        {
            QWidget *widget = item->widget();
            if (widget)
            {
                targetLayout->addWidget(widget);
            }
        }
    }
}

void Calculator::calcCost()
{
    const int rowCount = mUi->calcTableWidget->rowCount();
    const int colCount = mUi->calcTableWidget->columnCount();

    QVector<Ingredient> tableData; // Вектор для хранения данных

    for (int row = 0; row < rowCount; ++row)
    {
        Ingredient rowData; // Вектор для хранения данных строки
        for (int col = 0; col < colCount; ++col)
        {
            const auto *item = mUi->calcTableWidget->item(row, col);
            const auto *comboBox = qobject_cast<QComboBox *>(mUi->calcTableWidget->cellWidget(row, col));
            if (item || comboBox)
            {
                switch (col)
                {
                case 0:
                    rowData.name = item->text();
                    break;
                case 1:
                    rowData.quantity = item->text().toFloat();
                    break;
                case 2:
                    rowData.quantityUnit = comboBox->itemData(comboBox->currentIndex()).value<QuantityUnit>();
                    break;
                case 3:
                    rowData.price = item->text().toFloat();
                    break;
                case 4:
                    rowData.priceUnit = comboBox->itemData(comboBox->currentIndex()).value<PriceUnit>();
                    break;
                default:
                    break;
                }
            }
        }
        tableData.push_back(rowData);
    }

    double productCost = 0;

    for (int i = 0; i < tableData.size(); i++)
    {
        const auto& item = tableData[i];
        float quantity = item.quantity;
        float price = item.price;

        double rowCost = (quantity * price) / coefficient(item.priceUnit, item.quantityUnit); // Делим на 1000, чтобы перевести в граммы

        productCost += rowCost;
    }

    mUi->productCost->setText(QString::number(productCost) + " грн.");
}

void Calculator::removeIngridient(const QModelIndex &index)
{
    if (index.column() == 0)
    {
        mUi->calcTableWidget->removeRow(index.row());
    }
}

QComboBox *Calculator::createQuantityUnitsComboBox()
{
    auto comboBox = new QComboBox(mUi->calcTableWidget);
    comboBox->addItem("кг",  QVariant::fromValue(QuantityUnit::KILOGRAMM));
    comboBox->addItem("г", QVariant::fromValue(QuantityUnit::GRAMM));
    comboBox->addItem("л", QVariant::fromValue(QuantityUnit::LITER));
    comboBox->addItem("мл", QVariant::fromValue(QuantityUnit::MILLILITER));
    comboBox->addItem("шт", QVariant::fromValue(QuantityUnit::UNIT));

    return comboBox;
}

QComboBox* Calculator::createPriceUnitsComboBox()
{
    auto comboBox = new QComboBox(mUi->calcTableWidget);
    comboBox->addItem("грн/кг",  QVariant::fromValue(PriceUnit::UAH_PER_KG));
    comboBox->addItem("грн/л", QVariant::fromValue(PriceUnit::UAH_PER_LITER));
    comboBox->addItem("грн/шт", QVariant::fromValue(PriceUnit::UAH_PER_UNIT));

    return comboBox;
}

/*
            | UAH_PER_KG	UAH_PER_LITER	UAH_PER_UNIT
KILOGRAMM	| 1             PO              N/A
GRAMM	    | 1000          PO              N/A
LITER	    | PO            1               N/A
MILLILITER	| PO            1000            N/A
UNIT	    | N/A           N/A             1

*/

float Calculator::coefficient(PriceUnit priseUnit, QuantityUnit quantityUnit) const
{
    float result = 1.0;



    return result;
}
