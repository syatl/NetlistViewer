#include "Shape.h"

namespace Netlist {
    EllipseShape::EllipseShape(Symbol* s, const Box& b)
        : Shape(s), box_(b)
        {}
    
    EllipseShape::EllipseShape(Symbol* s, int x1, int y1, int x2, int y2) 
        : Shape(s), box_(Box(x1, y1, x2, y2))
        {}

    EllipseShape::~EllipseShape()
        {}

    Box EllipseShape::getBoundingBox() const {
        return box_;
    }
    
    void EllipseShape::toXml(std::ostream& o) const {
        o << "<ellipse x1=\"" << box_.getX1() << "\" y1=\"" << box_.getY1() << "\" x2=\"" << box_.getX2() << "\" y2=\"" << box_.getY2() << "\"/>" << std::endl; 
    }

    EllipseShape* EllipseShape::fromXml(Symbol* s, xmlTextReaderPtr reader) {
        EllipseShape* ellipseshape;
        std::string x1 = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"x1"));
        std::string x2 = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"x2"));
        std::string y1 = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"y1"));
        std::string y2 = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"y2"));


        if(!x1.empty() and !x2.empty() and !y1.empty() and !y2.empty()){
            ellipseshape = new EllipseShape(s, std::stoi(x1), std::stoi(y1), std::stoi(x2), std::stoi(y2));
            return ellipseshape;
        }
        return NULL;

    }

}

