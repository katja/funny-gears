#ifndef OPTION_WIDGET
#define OPTION_WIDGET

#include "stable.h"
#include "gui-elements/borderless_tool_buttons.h"

class OptionWidget : public QFrame {

    Q_OBJECT

public:
    OptionWidget(const QString &title, QWidget *mainWidget, QWidget *parent = 0);
    ~OptionWidget();

private slots:
    void dragEvent(QMouseEvent *event);
    void close();
    void toggleFolding();

private:
    QWidget *mainWidget;
    BorderlessToolButton
            *moveButton,
            *foldInButton,
            *foldOutButton,
            *closeButton;
    QFrame  *separatorLine;
    bool    isFolded;

    QByteArray mimeDataArray();

};

#endif //OPTION_WIDGET