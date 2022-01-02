#ifndef NETLIST_CELL_VIEWER_H
#define NETLIST_CELL_VIEWER_H

#include <QMainWindow>
#include <QLineEdit>
#include <QMenuBar>
#include <QAction>
#include "Cell.h"
#include "CellWidget.h"
#include "SaveCellDialog.h"
#include "OpenCellDialog.h"

namespace Netlist {
    class InstancesWidget;
    class CellsLib;

    class CellViewer : public QMainWindow {
        Q_OBJECT;
    public:
                          CellViewer          ( QWidget* parent=NULL );
        virtual           ~CellViewer          (){};
                Cell*     getCell             () const;
        inline  CellsLib* getCellsLib         () { return cellsLib_; } 

    signals: 
                void      cellLoaded          ();
    public slots:
                void      setCell             ( Cell* );
                void      saveCell            ();
                void      openCell            ();
                void      showCellsLib        ();  
                void      showInstancesWidget ();

    private:
        CellWidget*      cellWidget_;
        CellsLib*        cellsLib_;        
        InstancesWidget* instancesWidget_;  
        SaveCellDialog*  saveCellDialog_;
        OpenCellDialog*  openCellDialog_;
    };

}

#endif