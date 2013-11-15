#ifndef OPTION_LIST_WIDGET
#define OPTION_LIST_WIDGET

#include "stable.h"
#include "option_widget.h"

class OptionListWidget : public QWidget
{
public:
    OptionListWidget(QWidget *parent);
    ~OptionListWidget();

    void add(OptionWidget *optionWidget); //insert at end of list
    int  insertAt(QPoint position, OptionWidget *optionWidget);
    void insertAt(int i, OptionWidget *optionWidget);

    OptionWidget* at(int i);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);


private:
    QList<OptionWidget*> *options;
    QVBoxLayout *layout;

};

#endif //OPTION_LIST_WIDGET