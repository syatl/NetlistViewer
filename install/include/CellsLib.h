#ifndef NETLIST_CELL_LIB_H
#define NETLIST_CELL_LIB_H

#include <QTableView>
#include <QPushButton>
#include <QHeaderView>
#include "CellViewer.h"
#include "CellsModel.h"

namespace Netlist {
    class CellsLib : public QWidget {
        Q_OBJECT;
        public: 
                                CellsLib(QWidget* parent = NULL);
            void                setCellViewer(CellViewer*);
            int                 getSelectedRow() const;
            inline CellsModel*  getBaseModel() { return baseModel_; }

        public slots:
            void                load();
        
        private: 
            CellViewer* cellViewer_;
            CellsModel* baseModel_;
            QTableView* view_;
            QPushButton* load_;      
    };
}

#endif