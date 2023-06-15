#ifndef ENTERMNEMONICS_H
#define ENTERMNEMONICS_H

#include <QDialog>
#include <QSettings>

class WalletModel;

namespace Ui {
class EnterMnemonics;
}

class EnterMnemonics : public QDialog
{
    Q_OBJECT

public:
    explicit EnterMnemonics(QWidget *parent = 0);
    ~EnterMnemonics();
private Q_SLOTS:
    void on_next();
    void on_useRecoveryHeight_clicked(bool checked);

private:
    Ui::EnterMnemonics *ui;
    QSettings settings;
};

#endif // ENTERMNEMONICS_H
