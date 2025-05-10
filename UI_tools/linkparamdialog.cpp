#include "linkparamdialog.h"
#include "ui_linkparamdialog.h"

linkParamDialog::linkParamDialog(SSLink*, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::linkParamDialog),
    link(link)
{
    ui->setupUi(this);
}

SSLink* linkParamDialog::getLink(){return link;}

linkParamDialog::~linkParamDialog(){delete ui;}
