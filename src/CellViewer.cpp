#include "CellViewer.h"

namespace Netlist {

    CellViewer::CellViewer(QWidget* parent)
        : QMainWindow(parent), cellWidget_(NULL), saveCellDialog_(new SaveCellDialog(this)), openCellDialog_(new OpenCellDialog(this))
        {
            cellWidget_ = new CellWidget();
            setCentralWidget(cellWidget_);
            
            QMenu* fileMenu = menuBar()->addMenu("&File");

            QAction* action = new QAction("&Save As", this);
            action->setStatusTip("Save to disk (rename) the Cell");
            action->setShortcut(QKeySequence("CTRL+S"));
            action->setVisible(true);
            fileMenu->addAction(action);
            connect(action, SIGNAL(triggered()), this, SLOT(saveCell()));

            action = new QAction("&Open", this);
            action->setStatusTip("Open new cell");
            action->setShortcut(QKeySequence("CTRL+O"));
            action->setVisible(true);
            fileMenu->addAction(action);
            connect(action, SIGNAL(triggered()), this, SLOT(openCell()));


            action = new QAction("&Quit", this);
            action->setStatusTip("Exit the Netlist Viewer");
            action->setShortcut(QKeySequence("CTRL+Q"));
            action->setVisible(true);
            fileMenu->addAction(action);
            connect(action, SIGNAL(triggered()), this, SLOT(close()));
            


        }

    void CellViewer::saveCell() {
        Cell* cell = getCell();
        if(cell == NULL) return;
        QString cellName = cell->getName().c_str();

        if(saveCellDialog_->run(cellName)){
            cell->setName(cellName.toStdString());
            cell->save(cellName.toStdString());
        }
    }

    void CellViewer::openCell() {
        Cell* cell = getCell();
        QString cname;
        if(cell)
            cname = cell->getName().c_str();

        if(OpenCellDialog::run(cname)){
            if((cell = Cell::find((cname.toStdString()))) == NULL)
                cell = Cell::load(cname.toStdString());
            setCell(cell);
        } 
    }

    void CellViewer::setCell(Cell* cell) {
        cellWidget_->setCell(cell);
    }

    Cell* CellViewer::getCell() const {
        return cellWidget_->getCell();
    }
}