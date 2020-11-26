#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include <QScrollArea>

QT_BEGIN_NAMESPACE
namespace Ui { class home; }
QT_END_NAMESPACE

class home : public QMainWindow{
    Q_OBJECT

public:
    home(QWidget *parent = nullptr);
    ~home();

    void buttonClicked();
    QSize getRootWindowSize();

private:
    Ui::home *ui;

    float rightScrollAreaWidthRatio = 0.35;
    int rightScrollAreaWidth = 0;
    QScrollArea* rightScrollArea = new QScrollArea(this);

    void resizeEvent(QResizeEvent*);
};
#endif // HOME_H
