#include <QFileDialog>
#include <QMessageBox>
#include <QCryptographicHash>
#include "TransactionWindow.h"
#include "ui_TransactionWindow.h"


TransactionWindow::TransactionWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::TransactionWindow) {
    ui->setupUi(this);
    displayTransactions("../transactions.csv");
}

TransactionWindow::~TransactionWindow() {
    delete ui;
}

void TransactionWindow::displayTransactions(const QString &fileName) {
    loadTransactionsFromFile(fileName);
    setText();
}

void TransactionWindow::loadTransactionsFromFile(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
        return;
    }

    QTextStream in(&file);
    transactions.clear();

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');

        if (fields.size() == 4) {
            Transaction transaction;
            transaction.amount = fields[0];
            transaction.walletNumber = fields[1];
            transaction.dateTime = fields[2];
            transaction.hash = fields[3];
            transactions.append(transaction);
        }
    }
}

QString TransactionWindow::calculateHash(const Transaction &transaction, const QString &previousHash) {
    QString data = transaction.amount + transaction.walletNumber + transaction.dateTime + previousHash;
    QByteArray hash = QCryptographicHash::hash(data.toUtf8(), QCryptographicHash::Sha256);
    return hash.toHex();
}

void TransactionWindow::setText() {
    QString previousHash = "";
    bool invalidFound = false;

    ui->txtTransactions->clear();
    for (const Transaction &transaction: transactions) {
        QString calculatedHash = calculateHash(transaction, previousHash);
        previousHash = calculatedHash;

        qDebug() << transaction.amount + ", " +
                    transaction.walletNumber + ", " +
                    transaction.dateTime + ", " +
                    calculatedHash;

        invalidFound = invalidFound || (calculatedHash != transaction.hash);

        QString color = invalidFound ? "red" : "white";

        ui->txtTransactions->appendHtml(
                "<p style=\"color:" + color + "\">" +
                transaction.amount + ", " +
                transaction.walletNumber + ", " +
                transaction.dateTime + ", " +
                transaction.hash +
                "</p>"
        );
    }
}
