#include "Shape.h"

namespace Netlist {

    
    LineShape::LineShape(Symbol* s, int x1, int y1, int x2, int y2)
        : Shape(s), x1_(x1), y1_(y1), x2_(x2), y2_(y2) 
        {}

    LineShape::~LineShape()
        {}

    Point LineShape::getPoint1() const {
        return Point(x1_, y1_);
    }

    Point LineShape::getPoint2() const {
        return Point(x2_, y2_);
    }

    Box LineShape::getBoundingBox() const {
        return Box(x1_, y1_, x2_, y2_);
    }

    void LineShape::toXml(std::ostream& o) const {
        o << "<line x1=\"" << x1_ << "\" y1=\"" << y1_ << "\" x2=\"" << x2_ << "\" y2=\"" << y2_ << "\"/>" << std::endl;
    }    

    LineShape* LineShape::fromXml(Symbol* s, xmlTextReaderPtr reader) {
        LineShape* lineshape;
        std::string x1 = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"x1"));
        std::string y1 = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"y1"));
        std::string x2 = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"x2"));
        std::string y2 = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"y2"));
        
        if(!x1.empty() and !x2.empty() and !y1.empty() and !y2.empty()){
            lineshape = new LineShape(s, std::stoi(x1), std::stoi(y1), std::stoi(x2), std::stoi(y2));
            return lineshape;
        }
        return NULL;
    }
}

