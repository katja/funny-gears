#ifndef BORDERLESS_TOOL_BUTTON
#define BORDERLESS_TOOL_BUTTON

#include "../stable.h"

class BorderlessToolButton : public QToolButton
{
    Q_OBJECT

public:
    BorderlessToolButton(QString imagePathName, QWidget *parent = 0);
    ~BorderlessToolButton();

    void setDragging(bool enabled);
    void movingFinished();

signals:
    void dragEvent(QMouseEvent *event);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    
private slots:
    void enableMoving();
    void disableMoving();

private:
    bool movingActivated;
    bool draggingEnabled;

};

#endif