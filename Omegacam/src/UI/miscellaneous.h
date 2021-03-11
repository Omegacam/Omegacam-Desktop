#ifndef _MISCELLANEOUS_H_
#define _MISCELLANEOUS_H_

#include "../common_includes.h"

#include "QLayout"

class uimisc {
public:
    static void clearLayout(QLayout* layout) {
        while (QLayoutItem* item = layout->takeAt(0)) {
            QWidget* widget;
            if (widget = item->widget()) {
                widget->deleteLater();
            }
            if (QLayout* childLayout = item->layout()) {
                clearLayout(childLayout);
            }
            delete item;
        }
    }
};

#endif // !_MISCELLANEOUS_H_
