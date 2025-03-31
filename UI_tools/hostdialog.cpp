#include "hostdialog.h"
#include "ui_hostdialog.h"

HostDialog::HostDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HostDialog)
{
    ui->setupUi(this);
}

HostDialog::~HostDialog()
{
    delete ui;
}
