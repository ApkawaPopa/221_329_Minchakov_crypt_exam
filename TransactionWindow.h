#ifndef CRYPT_EXAM_TRANSACTIONWINDOW_H
#define CRYPT_EXAM_TRANSACTIONWINDOW_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class TransactionWindow; }
QT_END_NAMESPACE

struct Transaction {
    QString amount;
    QString walletNumber;
    QString dateTime;
    QString hash;
};

class TransactionWindow : public QWidget {
Q_OBJECT

public:
    explicit TransactionWindow(QWidget *parent = nullptr);

    ~TransactionWindow() override;

private:
    Ui::TransactionWindow *ui;
    QList<Transaction> transactions;
    void loadTransactionsFromFile(const QString &fileName);
    static QString calculateHash(const Transaction &transaction, const QString &previousHash);
    void setText();
    void displayTransactions(const QString &fileName);
    void on_btnOpenFile_clicked();
};


#endif
