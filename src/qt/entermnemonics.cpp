#include "entermnemonics.h"
#include "ui_entermnemonics.h"

#include "allocators.h"
#include "guiconstants.h"
#include "walletmodel.h"
#include "wallet/walletdb.h"

#include <QDateTime>
#include <QMessageBox>

EnterMnemonics::EnterMnemonics(QWidget* parent) : QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
                                                  ui(new Ui::EnterMnemonics)
{
    ui->setupUi(this);
    connect(ui->btnNext, SIGNAL(clicked()), this, SLOT(on_next()));
    connect(ui->useRecoveryHeight, SIGNAL(clicked(bool)), this, SLOT(on_useRecoveryHeight_clicked(bool)));
}

EnterMnemonics::~EnterMnemonics()
{
    delete ui;
}

void EnterMnemonics::on_next()
{
    bool knowsRecoveryHeight = ui->useRecoveryHeight->isChecked();
    std::string phrase = ui->mnemonics->toPlainText().trimmed().toStdString();

    // Check for empty phrase
    if (phrase.empty()) {
        QMessageBox::warning(this, tr("Recovery Phrase Empty"), tr("Recovery phrase is empty. Please enter your recovery phrase."), QMessageBox::Ok);
        return;
    }

    try {
        pwalletMain->GenerateNewHDChain(&phrase);
        CBlockLocator loc = chainActive.GetLocator(chainActive[0]);
        pwalletMain->SetBestChain(loc);
        CWalletDB walletdb(pwalletMain->strWalletFile);
        if (knowsRecoveryHeight) {
            bool ok;
            const int recoveryHeight = ui->recoveryHeight->text().toInt(&ok);
            if (!ok) {
                // Show a warning message for invalid recovery height
                QMessageBox::warning(this, tr("Invalid Recovery Height"), tr("Invalid recovery height. Please enter a valid number."), QMessageBox::Ok);
                return;
            }
            walletdb.WriteScannedBlockHeight(recoveryHeight); //set scanned block height to recoveryHeight
            walletdb.WriteWalletBirthday(recoveryHeight); //set wallet birthday to recoveryHeight
        } else {
            walletdb.WriteScannedBlockHeight(0); //reschedule to rescan entire chain to recover all funds and history
            walletdb.WriteWalletBirthday(0); //set wallet birthday to 0
        }
        QMessageBox::information(this, tr("Recovery Phrase Import Successful"), tr("Your mnemonics have been successfully imported into the wallet. Rescanning will be scheduled to recover all your funds."), QMessageBox::Ok);
        accept();
    } catch (const std::exception& ex) {
        QMessageBox::warning(this, tr("Recovery Phrase Invalid"), tr("Recovery phrase is invalid. Please try again and double check all words."), QMessageBox::Ok);
    }
}

void EnterMnemonics::on_useRecoveryHeight_clicked(bool checked)
{
    ui->recoveryHeight->setEnabled(checked);
}
