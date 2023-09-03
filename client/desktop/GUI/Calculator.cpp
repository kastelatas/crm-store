#include "Calculator.h"
#include "ui_calculator.h"
#include <QDebug>
#include "QFile"

Calculator::Calculator(QWidget *parent) : QWidget(parent),
                                          mUi(new Ui::calculator)
{
    mUi->setupUi(this);
    this->setWindowTitle("Калькулятор");
    this->hide();

    if (mUi != NULL)
    {
        // конфигурация таблицы калькулятора
        mUi->calcTableWidget->setRowCount(1);
        mUi->calcTableWidget->setColumnCount(6);

        mUi->calcTableWidget->setHorizontalHeaderLabels({"Название",
                                                         "Кол-во в", "Един. измерения",
                                                         "Цена за", "Един. измерения", "  "});

        QHeaderView *header = mUi->calcTableWidget->horizontalHeader();

        for (int col = 0, count = mUi->calcTableWidget->columnCount(); col < count; ++col)
        {
            header->setSectionResizeMode(col, QHeaderView::Stretch);
        }

        mUi->calcTableWidget->setCellWidget(0, 0, createIngridientsComboBox());
        mUi->calcTableWidget->setCellWidget(0, 2, createQuantityUnitsComboBox());
        mUi->calcTableWidget->setCellWidget(0, 4, createPriceUnitsComboBox());
        mUi->calcTableWidget->setCellWidget(0, 5, createDeleteButton());
        mUi->calcTableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);

        // конфигурация таблицы ингридиентов
        mUi->ingridientTableWidget->setRowCount(1);
        mUi->ingridientTableWidget->setColumnCount(1);
        mUi->ingridientTableWidget->setHorizontalHeaderLabels({"Название"});

        readFromFile();
        updateDataInIngridientsComboBox();

        connect(mUi->addIngridient, SIGNAL(clicked()), this, SLOT(addNewIngridient()));
        connect(mUi->calcCost, SIGNAL(clicked()), this, SLOT(calcCost()));
        connect(mUi->calcTableWidget, SIGNAL(clicked(const QModelIndex &index)), this, SLOT(removeIngridient(const QModelIndex &index)));
        connect(mUi->calcTabs, SIGNAL(currentChanged(int)), this, SLOT(changeTab(int)));
        connect(mUi->addIngridientToTable, SIGNAL(clicked()), this, SLOT(addIngridient()));
    }
}

Calculator::~Calculator()
{
    delete mUi;
}

void Calculator::addNewIngridient()
{
    const int rowCount = mUi->calcTableWidget->rowCount();

    mUi->calcTableWidget->insertRow(rowCount);
    mUi->calcTableWidget->setCellWidget(rowCount, 0, createIngridientsComboBox());
    mUi->calcTableWidget->setCellWidget(rowCount, 4, createPriceUnitsComboBox());
    mUi->calcTableWidget->setCellWidget(rowCount, 2, createQuantityUnitsComboBox());
    mUi->calcTableWidget->setCellWidget(rowCount, 5, createDeleteButton());
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

    QVector<Ingredient> tableData;

    for (int row = 0; row < rowCount; ++row)
    {
        Ingredient rowData;
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
        const auto &item = tableData[i];
        float quantity = item.quantity;
        float price = item.price;

        double rowCost = (quantity * price) / coefficient(item.priceUnit, item.quantityUnit);

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
    comboBox->addItem("кг", QVariant::fromValue(QuantityUnit::KILOGRAMM));
    comboBox->addItem("г", QVariant::fromValue(QuantityUnit::GRAMM));
    comboBox->addItem("л", QVariant::fromValue(QuantityUnit::LITER));
    comboBox->addItem("мл", QVariant::fromValue(QuantityUnit::MILLILITER));
    comboBox->addItem("шт", QVariant::fromValue(QuantityUnit::UNIT));

    return comboBox;
}

QComboBox *Calculator::createPriceUnitsComboBox()
{
    auto comboBox = new QComboBox(mUi->calcTableWidget);
    comboBox->addItem("грн/кг", QVariant::fromValue(PriceUnit::UAH_PER_KG));
    comboBox->addItem("грн/л", QVariant::fromValue(PriceUnit::UAH_PER_LITER));
    comboBox->addItem("грн/шт", QVariant::fromValue(PriceUnit::UAH_PER_UNIT));

    return comboBox;
}

QComboBox *Calculator::createIngridientsComboBox()
{
    auto comboBox = new QComboBox();
    for (const auto &item : mIngredients)
    {
        comboBox->addItem(item);
    }

    return comboBox;
}

QPushButton *Calculator::createDeleteButton()
{
    auto deleteButton = new QPushButton();
    // TODO update path to icon
    deleteButton->setIcon(QIcon(":/icons/remove.png"));
    deleteButton->setIconSize(QSize(24, 24));

    return deleteButton;
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

void Calculator::changeTab(int index)
{
    if (index == 0)
    {
        updateDataInIngridientsComboBox();
    }
}

void Calculator::updateDataInIngridientsComboBox()
{
    const int rowCount = mUi->calcTableWidget->rowCount();
    const int colCount = mUi->calcTableWidget->columnCount();

    for (int row = 0; row < rowCount; ++row)
    {
        for (int col = 0; col < colCount; ++col)
        {
            auto *comboBox = qobject_cast<QComboBox *>(mUi->calcTableWidget->cellWidget(row, col));
            if (comboBox && col == 0)
            {
                for (const auto &item : mIngredients)
                {
                    comboBox->addItem(item);
                }
            }
        }
    }
}

void Calculator::addIngridient()
{
    if (!mUi->ingridientInput->toPlainText().isEmpty())
    {
        const int rowCount = mUi->ingridientTableWidget->rowCount();
        mUi->ingridientTableWidget->insertRow(rowCount);

        QTableWidgetItem *newItem = new QTableWidgetItem(mUi->ingridientInput->toPlainText());

        mUi->ingridientTableWidget->setItem(rowCount, 0, newItem);

        mIngredients.push_back(mUi->ingridientInput->toPlainText());

        writeToFile();

        mUi->ingridientInput->clear();
    }
}

void Calculator::writeToFile()
{
    QFile file("ingredients.txt");

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        for (const auto &ingredient : mIngredients)
        {
            out << ingredient << "\n";
        }
        file.close();
    }
}

void Calculator::readFromFile()
{
    QFile file("ingredients.txt");

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);

        while (!in.atEnd())
        {
            QString line = in.readLine();
            mIngredients.push_back(line);
        }
        file.close();
    }
}