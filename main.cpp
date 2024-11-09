#include <QApplication>
#include <QPushButton>
#include "TransactionWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    TransactionWindow transactionWindow;
    transactionWindow.show();

    return QApplication::exec();
}
