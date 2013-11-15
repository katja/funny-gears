#include "option_widget.h"

OptionWidget::OptionWidget(const QString &title, QWidget *mainWidget, QWidget *parent) : QFrame(parent), mainWidget(mainWidget), isFolded(true) {

    setFrameStyle(QFrame::StyledPanel | QFrame::Raised);

    setMinimumWidth(300);

    moveButton    = new BorderlessToolButton("images/Move.png", this);
    moveButton->setDragging(true);
    connect(moveButton, SIGNAL(dragEvent(QMouseEvent*)), this, SLOT(dragEvent(QMouseEvent*)));

    foldInButton  = new BorderlessToolButton("images/ArrowUp.png", this);
    connect(foldInButton, SIGNAL(clicked()), this, SLOT(toggleFolding()));
    foldOutButton = new BorderlessToolButton("images/ArrowDown.png", this);
    connect(foldOutButton, SIGNAL(clicked()), this, SLOT(toggleFolding()));
    
    closeButton   = new BorderlessToolButton("images/Close.png", this);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *controlsLayout = new QHBoxLayout;
    controlsLayout->setMargin(0);
    controlsLayout->setAlignment(Qt::AlignRight | Qt::AlignTop);
    controlsLayout->addWidget(moveButton);
    controlsLayout->addWidget(foldInButton);
    controlsLayout->addWidget(foldOutButton);
    controlsLayout->addWidget(closeButton);

    QWidget *controlsWidget = new QWidget;
    controlsWidget->setLayout(controlsLayout);
    controlsWidget->adjustSize();
    controlsWidget->update();

    QHBoxLayout *titleLayout = new QHBoxLayout;
    titleLayout->setMargin(0);
    titleLayout->addWidget(new QLabel(title));
    titleLayout->addWidget(controlsWidget);

    QWidget *titleWidget = new QWidget;
    titleWidget->setLayout(titleLayout);
    titleWidget->adjustSize();
    titleWidget->update();
    
    separatorLine = new QFrame;
    separatorLine->setFrameShape(QFrame::HLine);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(titleWidget);
    layout->addWidget(separatorLine);
    layout->addWidget(mainWidget);

    toggleFolding();

    layout->update();
    setLayout(layout);
};

OptionWidget::~OptionWidget() {

};

void OptionWidget::dragEvent(QMouseEvent *event) {
    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;
    mimeData->setData(tr("OptionWidget"), mimeDataArray());
    drag->setMimeData(mimeData);

    Qt::DropAction dropAction = drag->exec(Qt::MoveAction);
    //Todo: remove item here???
    moveButton->movingFinished();
};

QByteArray OptionWidget::mimeDataArray() {
    QByteArray data;
    data.setNum(reinterpret_cast<qulonglong>(this), 16);
    return data;
};

void OptionWidget::close() {
    hide();
};

void OptionWidget::toggleFolding() {
    isFolded = !isFolded;
    mainWidget->setVisible(!isFolded);
    separatorLine->setVisible(!isFolded);
    foldInButton->setVisible(!isFolded);
    foldOutButton->setVisible(isFolded);
};