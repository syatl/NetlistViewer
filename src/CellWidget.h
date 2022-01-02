#ifndef NETLIST_CELL_WIDGET_H
#define NETLIST_CELL_WIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QRect>
#include <QPoint>
class QPainter;

#include "Cell.h"
#include "Box.h"



namespace Netlist {
    class CellWidget : public QWidget {
        Q_OBJECT;
        public: 
                            CellWidget          (QWidget* parent = NULL);
            virtual         ~CellWidget         ();
                    void    setCell             (Cell* cell);
            inline  Cell*   getCell             () const { return cell_; }
            inline  int     xToScreenX          (int x) const { return x - viewport_->getX1(); }
            inline  int     yToScreenY          (int y) const { return viewport_->getY1() - y; }
            inline  QRect   boxToScreenRect     (const Box& b) const { return QRect(xToScreenX(b.getX1()), yToScreenY(b.getY1()), b.getX2() - b.getX1(), b.getY1() - b.getY2()); }     
            inline  QPoint  pointToScreenPoint  (const Point& p) const { return QPoint(xToScreenX(p.getX()), yToScreenY(p.getY())); }
            inline  int     screenXtoX          (int x) const { return x + viewport_->getX1(); }
            inline  int     screenYtoY          (int y) const { return viewport_->getY1() - y; }
            inline  Box     screenRectToBox     (const QRect& q) const { return Box(screenXtoX(q.x()), screenYtoY(q.y()), screenXtoX(q.x() + q.width()), screenYtoY(q.x() - q.height())); }
            inline  Point   screenPointToPoint  (const QPoint& q) const { return Point(screenXtoX(q.x()), screenYtoY(q.y())); }
                    void    goUp                ();
                    void    goDown              ();
                    void    goLeft              ();
                    void    goRight             ();

            virtual QSize   minimumSizeHint     () const;
            virtual void    resizeEvent         (QResizeEvent*);
        
        protected: 
            virtual void    paintEvent          (QPaintEvent*);
            virtual void    keyPressEvent       (QKeyEvent*);

        private: 
            Cell*   cell_;
            Box*    viewport_;
            void    query(unsigned int, QPainter&);
    };
} // Netlist namespace.

#endif  // NETLIST_CELL_WIDGET_H
