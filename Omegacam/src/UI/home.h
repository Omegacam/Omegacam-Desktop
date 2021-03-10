#ifndef _HOME_H_
#define _HOME_H_

#include <QMainWindow>
#include <QScrollArea>
#include "../common_includes.h"

QT_BEGIN_NAMESPACE
namespace Ui { class home; }
QT_END_NAMESPACE


class CameraListWidget;
class home : public QMainWindow{
    Q_OBJECT

public:
    static home* getInstance();
    //

    QScrollArea* rightScrollArea = nullptr;

    //void setMainContentStream();
    void displayBase64Frame(std::string raw);

    void closeEvent(QCloseEvent* event);

    CameraListWidget* getCameraListWidget();

private:
    home(QWidget *parent = nullptr);
    ~home();

    static home* obj; // singleton

    Ui::home *ui;
    //

    double rightScrollAreaWidthRatio = 0.20;
    int rightScrollAreaWidth = 100;

    CameraListWidget* cameraList = nullptr;

    QLabel* imageLabel = nullptr; // used to display images

    void resizeEvent(QResizeEvent*);
    void setupUI();
};
#endif // _HOME_H_
