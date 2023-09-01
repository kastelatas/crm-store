#ifndef INGREDIENTS_H
#define INGREDIENTS_H

#include <QWidget>

namespace Ui {
class ingredients;
}

class ingredients : public QWidget
{
    Q_OBJECT

public:
    explicit ingredients(QWidget *parent = 0);
    ~ingredients();

private:
    Ui::ingredients *ui;
};

#endif // INGREDIENTS_H
