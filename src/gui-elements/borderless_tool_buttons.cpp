#include "borderless_tool_buttons.h"

BorderlessToolButton::BorderlessToolButton(QString imagePathName, QWidget *parent) : QToolButton(parent), movingActivated(false), draggingEnabled(false) {
    setIconSize(QSize(10, 10));
    setStyleSheet("image: url(" + imagePathName + "); border: none; margin: 0px; padding: 0px;");
};

BorderlessToolButton::~BorderlessToolButton() {

};

void BorderlessToolButton::setDragging(bool enabled) {
    draggingEnabled = enabled;
}

void BorderlessToolButton::movingFinished() {
    disableMoving();
}

void BorderlessToolButton::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        enableMoving();
        if(draggingEnabled) {
            setCursor(Qt::ClosedHandCursor);
        }
    }
    QToolButton::mousePressEvent(event);
}

void BorderlessToolButton::mouseReleaseEvent(QMouseEvent *event) {
    disableMoving();
    QToolButton::mouseReleaseEvent(event);
}

void BorderlessToolButton::mouseMoveEvent(QMouseEvent *event) {
    if(movingActivated && draggingEnabled) {
        emit(dragEvent(event));
    }
    QToolButton::mouseMoveEvent(event);
}

void BorderlessToolButton::enableMoving() {
    movingActivated = true;
    setMouseTracking(true);
    
}

void BorderlessToolButton::disableMoving() {
    movingActivated = false;
    setMouseTracking(false);
    unsetCursor();
}
