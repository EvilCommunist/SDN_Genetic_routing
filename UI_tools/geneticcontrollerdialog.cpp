#include "geneticcontrollerdialog.h"
#include "ui_geneticcontrollerdialog.h"
#include "../File_tools/geneticcontrollergenerator.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>

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
    QString filename = QFileDialog::getSaveFileName(this,
                                                    "Сохранить файл",
                                                    QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/algorithm.py",
                                                    "Python скрипт (*.py)");
    if (filename.isEmpty()) {
        return;
    }
    if (!filename.endsWith(".py", Qt::CaseInsensitive)) {
        filename += ".py";
    }

    QString script = "";
    if (ui->one_to_one->isChecked()){
        script = GeneticControllerGenerator::generateGeneticAlgorithmScript(ui->POP_SIZE->text().toInt(),
                                                                            ui->P_CROSSOVER->text().toDouble()/100,
                                                                            ui->P_MUTATION->text().toDouble()/100,
                                                                            ui->MAX_GEN->text().toInt(),
                                                                            ui->EARLY_STOP->text().toInt());
    }else{
        script = GeneticControllerGenerator::generateGeneticAlgorithmScriptOneToAll(ui->POP_SIZE->text().toInt(),
                                                                                    ui->P_CROSSOVER->text().toDouble()/100,
                                                                                    ui->P_MUTATION->text().toDouble()/100,
                                                                                    ui->MAX_GEN->text().toInt(),
                                                                                    ui->EARLY_STOP->text().toInt());
    }

    bool ok = GeneticControllerGenerator::saveScript(script, filename);

    if(!ok){
        QMessageBox::warning(this, "Ошибка",
                                     "Произошло непредвиденное повреждение данных при сохранении файла!");
    }

    done(QDialog::Accepted);
}

geneticControllerDialog::~geneticControllerDialog()
{
    delete ui;
}
