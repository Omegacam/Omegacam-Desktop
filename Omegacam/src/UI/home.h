#ifndef _HOME_H_
#define _HOME_H_

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
    QScrollArea* rightScrollArea = nullptr;

    void setMainContentStream();

private:
    Ui::home *ui;

    double rightScrollAreaWidthRatio = 0.20;
    int rightScrollAreaWidth = 100;

    void resizeEvent(QResizeEvent*);
};
#endif // _HOME_H_
