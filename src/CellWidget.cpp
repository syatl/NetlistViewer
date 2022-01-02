#include <QResizeEvent>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QApplication>
#include <QColor>
#include "CellWidget.h"
#include "Term.h"
#include "Instance.h"
#include "Symbol.h"
#include "Shape.h"
#include "Cell.h"
#include "Line.h"
#include "Node.h"
#include "Net.h"

/* color definition */
/* inspired by nord color palette https://www.nordtheme.com/ */

#define NORD_NIGHT_BLACK      QColor(46, 52, 64, 77)

#define NORD_SNOW_WHITE       QColor(216, 222, 233, 255)

#define NORD_FROST_GREEN      QColor(143, 188, 187, 255)
#define NORD_GREEN            QColor(101, 133, 132, 255)

#define NORD_FROST_BLUE       QColor(129, 161, 193, 255)
#define NORD_FROST_DARK_BLUE  QColor(94, 129, 172, 255)

#define NORD_AURORA_PURPLE    QColor(180, 142, 173, 255)
#define NORD_AURORA_YELLOW    QColor(235, 203, 139, 255)
#define NORD_AURORA_RED       QColor(191, 97, 106, 255)

namespace Netlist {

  using namespace std;

  ostream& operator<< ( ostream& o, const QRect& rect )
  {
    o << "<QRect x:" << rect.x()
      <<       " y:" << rect.y()
      <<       " w:" << rect.width()
      <<       " h:" << rect.height() << ">";
    return o;
  }


  ostream& operator<< ( ostream& o, const QPoint& p )
  { o << "<QRect x:" << p.x() << " y:" << p.y() << ">"; return o; }



  CellWidget::CellWidget ( QWidget* parent )
    : QWidget(parent)
    , cell_  (NULL)
    , viewport_(new Box(0, 0, 500, 500))
  {
    setAttribute    ( Qt::WA_OpaquePaintEvent );
    setAttribute    ( Qt::WA_NoSystemBackground );
    setAttribute    ( Qt::WA_StaticContents );
    setSizePolicy   ( QSizePolicy::Expanding, QSizePolicy::Expanding );
    setFocusPolicy  ( Qt::StrongFocus );
    setMouseTracking( true );
  }


  CellWidget::~CellWidget ()
  { }


  void  CellWidget::setCell ( Cell* cell )
  {
    cell_ = cell;
    repaint();
  }


  QSize  CellWidget::minimumSizeHint () const
  { return QSize(500,500); }


  void  CellWidget::resizeEvent ( QResizeEvent* event )
  { 
    repaint();
  }

  void CellWidget::goUp() {
    viewport_->translate(Point(0, -20));
    repaint();
  }

  void CellWidget::goDown() {
    viewport_->translate(Point(0, +20));
    repaint();
  }

  void CellWidget::goLeft() {
    viewport_->translate(Point(20, 0));
    repaint();
  }

  void CellWidget::goRight() {
    viewport_->translate(Point(-20, 0));
    repaint();
  }

  void CellWidget::keyPressEvent(QKeyEvent* event) {
    event->ignore();
    if(event->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier)) return;
    switch(event->key()){
      case Qt::Key_Up:    goUp    (); break;
      case Qt::Key_Down:  goDown  (); break;
      case Qt::Key_Left:  goLeft  (); break;
      case Qt::Key_Right: goRight (); break;
      default: return;
    }
    event->accept();
  } 

  void  CellWidget::paintEvent ( QPaintEvent* event )
  {
   // QFont  bigFont = QFont( "URW Bookman L", 36 );

    QString cellName = "NULL";
    if (cell_) cellName = cell_->getName().c_str();

    QPainter painter(this);
    //painter.setFont      ( bigFont );
    painter.setBackground( QBrush(Qt::black) );
    painter.eraseRect    ( QRect( QPoint(0,0), size() ) );
    if(cell_)
        query(1, painter);

    int frameWidth  = 460;
    int frameHeight = 100;
    QRect nameRect ( (size().width ()-frameWidth )/2
                   , (size().height()-frameHeight)/8
                   , frameWidth
                   , frameHeight
                   );
    painter.drawRect( nameRect );
    painter.drawText( nameRect, Qt::AlignTop | Qt::AlignCenter, cellName );
    }


  void CellWidget::query(unsigned int flags, QPainter& painter) {

    painter.setBrush(QBrush(NORD_NIGHT_BLACK));
    const vector<Instance*>& instances = cell_->getInstances();
    
    for(size_t i = 0; i < instances.size(); ++i){
      painter.setPen(QPen(NORD_AURORA_PURPLE, 3));

      Point instPos = instances[i]->getPosition();
      instPos.translate(0, -viewport_->getY2());

      const Symbol* symbol = instances[i]->getMasterCell()->getSymbol();
      if(not symbol) continue;
      const vector <Shape*>& shapes = symbol->getShapes();

      for(size_t j = 0; j < shapes.size(); ++j){
        BoxShape* boxShape = dynamic_cast<BoxShape*>(shapes[j]);
        LineShape* lineShape = dynamic_cast<LineShape*>(shapes[j]);
        EllipseShape* ellipseShape = dynamic_cast<EllipseShape*>(shapes[j]);
        ArcShape* arcShape = dynamic_cast<ArcShape*>(shapes[j]);

        if(boxShape){
          Box box = boxShape->getBoundingBox ();
          QRect rect = boxToScreenRect(box.translate(instPos));
          painter.drawRect(rect);
        }

        else if(lineShape){
          Point p1 = lineShape->getPoint1();
          Point p2 = lineShape->getPoint2();
          QPoint qp1 = pointToScreenPoint(p1.translate(instPos));
          QPoint qp2 = pointToScreenPoint(p2.translate(instPos));
          painter.drawLine(qp1, qp2);
        }

        else if(ellipseShape){
          Box box = ellipseShape->getBoundingBox();
          QRect rect = boxToScreenRect(box.translate(instPos));
          painter.drawEllipse(rect);
        }

        else if(arcShape){
          Box box = arcShape->getBoundingBox();
          QRect rect = boxToScreenRect(box.translate(instPos));
          painter.drawArc(rect, 16*arcShape->getStart(), 16*arcShape->getSpan());
        }
      }
      
      QRect qrect = boxToScreenRect(symbol->getBoundingBox().translate(instPos));
      QRect name = QRect(qrect.center().x(), qrect.center().y()+(qrect.height()/2), 60, 30);
      
      painter.setPen(QPen(NORD_AURORA_YELLOW, 1));
      painter.drawText(name, Qt::AlignTop, instances[i]->getName().c_str());
    }

    painter.setPen(QPen(NORD_FROST_DARK_BLUE, 1));
    painter.setBrush(QBrush(NORD_FROST_DARK_BLUE));
    const vector<Net*>& nets = cell_->getNets();

    for(size_t i = 0; i < nets.size(); ++i){
      const vector<Line*>& lines = nets[i]->getLines();

      for(size_t j = 0; j < lines.size(); ++j){
        Point p1 = lines[j]->getSourcePosition();
        Point p2 = lines[j]->getTargetPosition();
        p1.translate(0, -viewport_->getY2());
        p2.translate(0, -viewport_->getY2());
        
        QPoint qp1 = pointToScreenPoint(p1);
        QPoint qp2 = pointToScreenPoint(p2);
        painter.drawLine(qp1, qp2);
        if(lines[j]->getSource()->getDegree() > 2){
          QRect rect(qp1.x()-5, qp2.y()-5, 10, 10); 
          painter.drawEllipse(rect);
        }
      }
    }
    
    painter.setPen(QPen(NORD_FROST_GREEN, 1));
    painter.setBrush(QBrush(NORD_FROST_GREEN));
    const vector<Term*>& terms = cell_->getTerms();

    for(size_t i = 0; i < terms.size(); ++i){
      Point pt = terms[i]->getPosition();
      pt.translate(0, -viewport_->getY2());
      QPoint qp = pointToScreenPoint(pt);
      painter.drawRect(qp.x(), qp.y()-4, 8, 8);
  
      QRect rect = QRect(qp.x(), qp.y(), 40, 20);
      const char* tname = terms[i]->getName().c_str();
      switch(terms[i]->getDirection()){
        case Term::External: painter.drawText(rect, Qt::AlignBottom | Qt::AlignRight, tname); break; 
        case Term::Internal: painter.drawText(rect, Qt::AlignBottom | Qt::AlignLeft, tname); break;
        default: cerr << "CellWidget::query term direction error" << endl; break;
      }
    }

    for(size_t i = 0; i < instances.size(); ++i){
      Point instPos = instances[i]->getPosition();
      instPos.translate(0, -viewport_->getY2());
      const Symbol* symbol = instances[i]->getMasterCell()->getSymbol();
      if(not symbol) continue;
      const vector<Shape*>& shapes = symbol->getShapes();

      for(size_t j = 0; j < shapes.size(); ++j){
        TermShape* termShape = dynamic_cast<TermShape*>(shapes[j]);
        if(termShape){
          Point pt = Point(termShape->getX(), termShape->getY());
          QPoint qp = pointToScreenPoint(pt.translate(instPos));

          painter.setPen(QPen(NORD_AURORA_RED, 1));
          painter.setBrush(QBrush(NORD_AURORA_RED));
          painter.drawRect(qp.x(), qp.y()-4, 8, 8);	  

          QRect rect = QRect(qp.x(), qp.y(), 25, 25);

          const char* tname = termShape->getTerm()->getName().c_str();

          switch(termShape->getAlign()){
          case TermShape::TopRight:     painter.drawText(rect, Qt::AlignTop | Qt::AlignRight, tname);     break;
          case TermShape::TopLeft:      painter.drawText(rect, Qt::AlignTop | Qt::AlignLeft, tname);      break;
          case TermShape::BottomLeft:   painter.drawText(rect, Qt::AlignBottom | Qt::AlignLeft, tname);   break;
          case TermShape::BottomRight:  painter.drawText(rect, Qt::AlignBottom | Qt::AlignRight, tname);  break;
          default: cerr << "CellWidget::query unexpected term name alignment" << endl; break;
          }
        }
      }
    }
  
    painter.setPen(QPen(NORD_SNOW_WHITE, 1));
    painter.setBrush(QBrush(NORD_NIGHT_BLACK));

  }
 
}  // Netlist namespace.
