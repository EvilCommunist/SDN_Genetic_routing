#include "linkparamdialog.h"
#include "ui_linkparamdialog.h"

linkParamDialog::linkParamDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::linkParamDialog)
{
    ui->setupUi(this);
}

linkParamDialog::~linkParamDialog()
{
    delete ui;
}
