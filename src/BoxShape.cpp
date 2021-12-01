#include "Shape.h"

namespace Netlist {
    
    BoxShape::BoxShape(Symbol* s, const Box& b)
        : Shape(s), box_(b) 
        {}

    BoxShape::BoxShape(Symbol* s, int x1, int y1, int x2, int y2) 
        : Shape(s), box_(x1, y1, x2, y2)
        {}

    BoxShape::~BoxShape() 
        {}
    
    Box BoxShape::getBoundingBox() const {
        return box_;
    } 

    void BoxShape::toXml(std::ostream& o) const {
        o << "<box x1=\"" << box_.getX1() << "\" y1=\"" << box_.getY1() << "\" x2=\"" << box_.getX2() << "\" y2=\"" << box_.getY2() << "\"/>" << std::endl;
    }

    BoxShape* BoxShape::fromXml(Symbol* s, xmlTextReaderPtr reader) {
        BoxShape* boxshape;
        std::string x1 = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"x1"));
        std::string x2 = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"x2"));
        std::string y1 = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"y1"));
        std::string y2 = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"y2"));

        if(!x1.empty() and !x2.empty() and !y1.empty() and !y2.empty()){
            boxshape = new BoxShape(s, std::stoi(x1), std::stoi(y1), std::stoi(x2), std::stoi(y2));
            return boxshape;
        }
        return NULL;
    }
}