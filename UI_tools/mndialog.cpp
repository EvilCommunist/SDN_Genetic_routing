#include "mndialog.h"
#include "ui_mndialog.h"
#include <QVBoxLayout>
#include <QMessageBox>

MNDialog::MNDialog(const QString& scriptPath, QWidget *parent) :
    QWidget(parent, Qt::Window),
    ui(new Ui::MNDialog),
    terminal(nullptr),
    currentScriptPath(scriptPath),
    isRunning(true)
{
    ui->setupUi(this);
    setWindowFlag(Qt::Window);

    setupTerminal();
    startMininet();
}

MNDialog::~MNDialog()
{
    stopMininet();
    delete ui;
}

void MNDialog::setupTerminal()
{
    QVBoxLayout *layout = new QVBoxLayout(ui->termArea);
    layout->setContentsMargins(0, 0, 0, 0);

    try {
        terminal = new QTermWidget(ui->termArea);
        if (!terminal) {
            throw std::runtime_error("Failed to create terminal widget");
        }
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", e.what());
        return;
    }

    layout->addWidget(terminal);
    terminal->setColorScheme("Linux");

    terminal->setScrollBarPosition(QTermWidget::ScrollBarRight);
}

void MNDialog::startMininet()
{
    if (!terminal) {
        QMessageBox::critical(this, "Error", "Terminal not initialized");
        return;
    }

    terminal->clear();

    QString controllerPath = currentScriptPath;
    controllerPath.replace(" ", "\\ ");

    terminal->sendText("sudo python3 " + controllerPath + "\n");
    isRunning = true;
}

void MNDialog::stopMininet()
{
    if(isRunning){
        terminal->sendText("exit\n");
        isRunning = false;
    }
}

void MNDialog::on_start_clicked()
{
    startMininet();
}

void MNDialog::on_stop_clicked()
{
    stopMininet();
}
