#include "CellsLib.h"

namespace Netlist {
    CellsLib::CellsLib(QWidget* parent)
        :   QWidget(parent), cellViewer_(NULL), baseModel_(new CellsModel(this)), 
            view_(new QTableView(this)), load_(new QPushButton(this))
    {
        setAttribute(Qt::WA_QuitOnClose, false);
        setAttribute(Qt::WA_DeleteOnClose, false);
        setContextMenuPolicy(Qt::ActionsContextMenu);

        view_->setShowGrid(false);
        view_->setAlternatingRowColors(true);
        view_->setSelectionBehavior(QAbstractItemView::SelectRows);
        view_->setSelectionMode(QAbstractItemView::SingleSelection);
        view_->setSortingEnabled(true);
        view_->setModel(baseModel_);

        QHeaderView* horizontalHeader = view_->horizontalHeader();
        horizontalHeader->setDefaultAlignment(Qt::AlignHCenter);
        horizontalHeader->setMinimumSectionSize(300);
        horizontalHeader->setStretchLastSection(true);

        QHeaderView* verticalHeader = view_->verticalHeader();
        verticalHeader->setVisible(true);

        QHBoxLayout* horizontalLayout = new QHBoxLayout();
        horizontalLayout->addStretch();
        horizontalLayout->addWidget(load_);
        horizontalLayout->addStretch();

        QFrame* separator = new QFrame();
        separator->setFrameShape(QFrame::HLine);
        separator->setFrameShadow(QFrame::Sunken);

        QVBoxLayout* verticalLayout = new QVBoxLayout();
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        verticalLayout->addWidget(view_);
        verticalLayout->addLayout(horizontalLayout);
        
        setLayout(verticalLayout);

        load_->setText("Load");
        connect(load_, SIGNAL(clicked()), this, SLOT(load()));
    }

    int CellsLib::getSelectedRow() const {
        QModelIndexList selected = view_->selectionModel()->selection().indexes();

        if(selected.empty()) return -1;
        return selected.first().row();
    }

    void CellsLib::load() {
        int selectedRow = getSelectedRow();
        if(selectedRow < 0) return;
        cellViewer_->setCell(baseModel_->getModel(selectedRow));
    }

    void CellsLib::setCellViewer(CellViewer* cellviewer) {
        cellViewer_ = cellviewer;
    }
}