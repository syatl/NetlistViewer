#ifndef NETLIST_INSTANCES_WIDGET_H
#define NETLIST_INSTANCES_WIDGET_H

#include <QTableView>
#include <QHeaderView>
#include <QPushButton>
#include "Cell.h"
#include "CellViewer.h"
#include "InstancesModel.h"


namespace Netlist {
    class InstancesWidget : public QWidget {
        Q_OBJECT;
        public: 
                        InstancesWidget(QWidget* parent = NULL);
            void        setCellViewer(CellViewer*);
            int         getSelectedRow() const;
            inline void setCell(Cell* cell) { baseModel_->setCell(cell); }
        public slots:
            void        load();
        private:
            CellViewer* CellViewer_;
            InstancesModel* baseModel_;
            QTableView* view_;
            QPushButton* load_;
    };
}

#endif