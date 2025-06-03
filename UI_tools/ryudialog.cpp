#include "ryudialog.h"
#include "ui_ryudialog.h"

RyuDialog::RyuDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RyuDialog)
{
    ui->setupUi(this);
}

RyuDialog::~RyuDialog()
{
    delete ui;
}
