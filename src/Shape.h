#ifndef NETLIST_SHAPE_H
#define NETLIST_SHAPE_H

#include "Symbol.h"
#include "Box.h"
#include "Term.h"

namespace Netlist {
    class BoxShape;
    class EllipseShape;
    class ArcShape;
    class LineShape;

    class Shape {
        public: 
            Shape(Symbol*);
            virtual ~Shape();
            virtual Box getBoundingBox() const = 0;
            Symbol* getSymbol() const;
            virtual void toXml(std::ostream& o) const = 0; 
            static Shape* fromXml(Symbol*, xmlTextReaderPtr); 
        private:
            Symbol* owner_;
    };

    class BoxShape : public Shape {
        public: 
            BoxShape(Symbol* s, const Box&);
            BoxShape(Symbol* s, int x1, int y1, int x2, int y2);
            ~BoxShape();
            Box getBoundingBox() const;

            void toXml(std::ostream& o) const;
            static BoxShape* fromXml(Symbol* s, xmlTextReaderPtr);
            
        private: 
            Box box_;
    };

    class TermShape : public Shape {
        public: 
            enum NameAlign { TopLeft=1, TopRight, BottomLeft, BottomRight, Unknown };
            TermShape(Symbol*, std::string name, int x, int y, NameAlign na);
            ~TermShape();
            Box getBoundingBox() const;
            Term* getTerm() const;
            int getX() const;
            int getY() const;
            void toXml(std::ostream& o) const;
            static TermShape* fromXml(Symbol* s, xmlTextReaderPtr);

        private: 
            Term* term_;
            NameAlign align_;
            int x_;
            int y_;
    };

    class LineShape : public Shape {
        public: 
            LineShape(Symbol* s, int x1, int y1, int x2, int y2);
            ~LineShape();
            Box getBoundingBox() const;
            void toXml(std::ostream& o) const;
            static LineShape* fromXml(Symbol* s, xmlTextReaderPtr);
        private:
            int x1_;
            int y1_;
            int x2_;
            int y2_;
    };
    
    class EllipseShape : public Shape {
        public:
            EllipseShape(Symbol* s, const Box& b);
            EllipseShape(Symbol* s, int x1, int y1, int x2, int y2);
            ~EllipseShape();
            Box getBoundingBox() const;
            void toXml(std::ostream& o) const;
            static EllipseShape* fromXml(Symbol* s, xmlTextReaderPtr);
        private:
            Box box_;
    };

    class ArcShape : public Shape {
        public: 
            ArcShape(Symbol* s, int start, int span, const Box& b);
            ArcShape(Symbol* s, int start, int span, int x1, int y1, int x2, int y2);
            ~ArcShape();
            Box getBoundingBox() const;
            void toXml(std::ostream& o) const;
            static ArcShape* fromXml(Symbol* s, xmlTextReaderPtr);
        private:
            Box box_;
            int start_;
            int span_;
    };
}

#endif