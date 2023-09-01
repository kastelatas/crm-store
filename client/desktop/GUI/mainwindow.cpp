#include <QtWidgets>
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "defines/enums/MenuItems.hpp"

#include "qDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), mUi(new Ui::MainWindow)
{

    mMenuWidgets[0] = new Orders(this);
    mMenuWidgets[1] = new Menu(this);
    mMenuWidgets[2] = new Ingredients(this);
    mMenuWidgets[3] = new Calculator(this);
    mMenuWidgets[4] = new Clients(this);

    QString menuItems[] = {
        "Заказы",
        "Меню",
        "Ингредиенты",
        "Калькулятор",
        "Клиенты",
    };

    mUi->setupUi(this);

    if (mUi != NULL)
    {

        for (unsigned i = 0; i < mMenuWidgets.size(); i++)
        {
            mUi->mainVerticalLayout->addWidget(mMenuWidgets[i]);
        }

        QStringList menuItemsList;
        for (const auto &item : menuItems)
        {
            menuItemsList.append(item);
        }

        QStringListModel *model = new QStringListModel(menuItemsList, this);
        mUi->menuListView->setModel(model);
        mUi->menuListView->show();

        connect(mUi->menuListView, SIGNAL(clicked(QModelIndex)), this, SLOT(onMenuClicked(QModelIndex)));
    }
}

MainWindow::~MainWindow()
{
    delete mUi;
}

void MainWindow::onMenuClicked(const QModelIndex &index)
{
    int row = index.row();

    qDebug() << index.data().toString();

    for (unsigned i = 0; i < mMenuWidgets.size(); i++)
    {
        if (i != static_cast<unsigned int>(row))
        {
            mMenuWidgets[i]->hide();
        }
        else
        {
            mMenuWidgets[i]->show();
            mUi->mainGroupContainer->setTitle(mMenuWidgets[i]->windowTitle());
        }
    }
}