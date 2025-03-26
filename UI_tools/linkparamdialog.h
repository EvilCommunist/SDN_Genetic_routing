#ifndef LINKPARAMDIALOG_H
#define LINKPARAMDIALOG_H

#include <QDialog>

namespace Ui {
class linkParamDialog;
}

class linkParamDialog : public QDialog
{
    Q_OBJECT

public:
    explicit linkParamDialog(QWidget *parent = nullptr);
    ~linkParamDialog();

private:
    Ui::linkParamDialog *ui;
};

#endif // LINKPARAMDIALOG_H
