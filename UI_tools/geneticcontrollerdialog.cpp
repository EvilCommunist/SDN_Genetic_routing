#include "geneticcontrollerdialog.h"
#include "ui_geneticcontrollerdialog.h"

geneticControllerDialog::geneticControllerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::geneticControllerDialog)
{
    ui->setupUi(this);
    ui->MAX_GEN->setText("100");
    ui->EARLY_STOP->setText("15");
    ui->POP_SIZE->setText("50");
    ui->P_CROSSOVER->setText("85");
    ui->P_MUTATION->setText("15"); // default values
}

void geneticControllerDialog::accept(){

}

geneticControllerDialog::~geneticControllerDialog()
{
    delete ui;
}
