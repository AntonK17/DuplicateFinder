#include "warningwindow.h"
#include "ui_warningwindow.h"

WarningWindow::WarningWindow(QWidget *parent) :
    QDialog(parent),
    ui_w(new Ui::WarningWindow)
{
    ui_w->setupUi(this);
    ui_w->Frame_invis1->setFrameShape(QFrame::NoFrame);
    ui_w->Frame_invis2->setFrameShape(QFrame::NoFrame);
}

WarningWindow::~WarningWindow()
{
    delete ui_w;
}

void WarningWindow::on_Button_Yes_clicked()
{
    if (ui_w->CheckDeleteBox->isChecked())
        emit YesNoClicked(true,true);
    else
        emit YesNoClicked(false,true);
    this->close();
}

void WarningWindow::on_Button_No_clicked()
{
    this->close();
    emit YesNoClicked(false,false);
}
