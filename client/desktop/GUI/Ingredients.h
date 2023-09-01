#ifndef INGREDIENTS_H
#define INGREDIENTS_H

#include <QWidget>

namespace Ui
{
    class ingredients;
}

class Ingredients : public QWidget
{
    Q_OBJECT

public:
    explicit Ingredients(QWidget *parent = 0);
    ~Ingredients();

private:
    Ui::ingredients *ui;
};

#endif // INGREDIENTS_H
