#ifndef GENETICCONTROLLERDIALOG_H
#define GENETICCONTROLLERDIALOG_H

#include <QDialog>

namespace Ui {
class geneticControllerDialog;
}

class geneticControllerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit geneticControllerDialog(QWidget *parent = nullptr);
    ~geneticControllerDialog();

private slots:
    virtual void accept();

private:
    Ui::geneticControllerDialog *ui;
};

#endif // GENETICCONTROLLERDIALOG_H
