#include "option_list_widget.h"

OptionListWidget::OptionListWidget(QWidget *parent) : QWidget(parent) {
    options = new QList<OptionWidget*>();
    setAcceptDrops(true);
    
    layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    setLayout(layout);
    update();
};

OptionListWidget::~OptionListWidget() {

};

void OptionListWidget::dragEnterEvent(QDragEnterEvent *event) {
    //only accept OptionWidgets with MoveAction
    if(event->mimeData()->hasFormat("OptionWidget") && event->possibleActions() & Qt::MoveAction)
        event->acceptProposedAction();
};

void OptionListWidget::dropEvent(QDropEvent *event) {
    bool noError = true;
    qlonglong data = event->mimeData()->data(tr("OptionWidget")).toULongLong(&noError, 16);
    OptionWidget* widget = reinterpret_cast<OptionWidget*>(data);
    if(options->contains(widget)) {
        int oldIndex = options->indexOf(widget);
        int newIndex = insertAt(event->pos(), widget);
        if (oldIndex < newIndex)
            options->removeAt(oldIndex);
        else
            options->removeAt(oldIndex + 1);
    }
};

void OptionListWidget::add(OptionWidget *optionWidget) {
    insertAt(options->size(), optionWidget);
};

OptionWidget* OptionListWidget::at(int i) {
    return options->at(i);
};

int OptionListWidget::insertAt(QPoint position, OptionWidget *optionWidget) {
    QPoint centeredPosition(x() + 0.5 * width(), position.y());

    if(position.y() <= 0) { //position is above widget
        insertAt(0, optionWidget);
        return 0;

    } else if(y() + height() <= position.y()) { //position is below widget => insert at the end
        add(optionWidget);
        return options->size();

    } else { //y position is in widget
        int insertBelow = 0;
        for (int i = 0; i < options->size() && i == insertBelow; ++i) {
            if(options->at(i)->frameGeometry().top() >= position.y() ||
                options->at(i)->frameGeometry().contains(centeredPosition)) {
                insertAt(i, optionWidget);
            } else {
                insertBelow += 1;
            }
        }
        if(insertBelow == options->size()) {//widget was still not inserted
            add(optionWidget);
        }
        return insertBelow;
    }
};

void OptionListWidget::insertAt(int i, OptionWidget *optionWidget) {
    int j = (i < 0) ? 0 : i;
    j = (j >= options->size()) ? options->size() : j;

    options->insert(j, optionWidget);
    layout->insertWidget(j, optionWidget);
    layout->update();
    update();
};