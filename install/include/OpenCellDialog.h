#ifndef OPEN_CELL_DIALOG_H
#define OPEN_CELL_DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QLayout>

namespace Netlist {
    class OpenCellDialog : public QDialog {
        Q_OBJECT;
        public: 
                            OpenCellDialog(QWidget* parent = NULL);
            static bool     run(QString& name);
            const QString   getCellName() const;
            void            setCellName(const QString&);
        protected:
            QLineEdit* lineEdit_;
    };
}

#endif