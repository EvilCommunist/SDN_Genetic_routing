#include "controllerdialog.h"
#include "ui_controllerdialog.h"

ControllerDialog::ControllerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControllerDialog)
{
    ui->setupUi(this);
}

ControllerDialog::~ControllerDialog()
{
    delete ui;
}
