#include "ryudialog.h"
#include "ui_ryudialog.h"
#include <QVBoxLayout>
#include <QMessageBox>

RyuDialog::RyuDialog(const QString& controllerPath, QWidget *parent) :
    QWidget(parent, Qt::Window),
    ui(new Ui::RyuDialog),
    terminal(nullptr),
    currentControllerPath(controllerPath)
{
    ui->setupUi(this);
    setWindowFlag(Qt::Window);
    setWindowTitle("Ryu");

    setupTerminal();
    startRyuManager();
}

RyuDialog::~RyuDialog()
{
    stopRyuManager();
    delete ui;
}

void RyuDialog::setupTerminal()
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

void RyuDialog::startRyuManager()
{
    if (!terminal) {
        QMessageBox::critical(this, "Error", "Terminal not initialized");
        return;
    }

    terminal->clear();

    QString controllerPath = currentControllerPath;
    controllerPath.replace(" ", "\\ ");

    terminal->sendText("ryu-manager " + controllerPath + "\n");
}

void RyuDialog::stopRyuManager()
{
    terminal->sendText("\x03");
}

void RyuDialog::on_restart_clicked()
{
    stopRyuManager();
    QTimer::singleShot(500, this, &RyuDialog::startRyuManager);
}

void RyuDialog::on_start_clicked()
{
    startRyuManager();
}

void RyuDialog::on_stop_clicked()
{
    stopRyuManager();
}
