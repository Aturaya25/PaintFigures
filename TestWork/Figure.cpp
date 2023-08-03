#include "Figure.h"
void Figure::setSelected(bool isChecked)
{
    if (isChecked) {
        color = QColor("#b3ffe5");
        _isSelected = true;
    }
    else {
        color = Qt::gray;
        _isSelected = false;
    }
}

