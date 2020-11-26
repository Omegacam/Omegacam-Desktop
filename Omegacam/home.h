#ifndef HOME_H
#define HOME_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class home; }
QT_END_NAMESPACE

class home : public QMainWindow{
    Q_OBJECT

public:
    home(QWidget *parent = nullptr);
    ~home();

private:
    Ui::home *ui;
};
#endif // HOME_H
