#include "Shape.h"

namespace Netlist {

    ArcShape::ArcShape(Symbol* s, int start, int span, const Box& b)
        : Shape(s), start_(start), span_(span), box_(b)
        {}

    ArcShape::ArcShape(Symbol* s, int start, int span, int x1, int y1, int x2, int y2)
        : Shape(s), start_(start), span_(span), box_(Box(x1, y1, x2, y2))
        {}

    ArcShape::~ArcShape()
        {}

    Box ArcShape::getBoundingBox() const {
        return box_;
    }

    void ArcShape::toXml(std::ostream& o) const {
        o << "<arc x1=\"" << box_.getX1() << "\" y1=\"" << box_.getY1() << "\" x2=\"" << box_.getX2() << "\" y2=\"" << box_.getY2() << "\" start=\"" << start_ << "\" span=\"" << span_ << "\"/>" << std::endl;
    }
    
    ArcShape* ArcShape::fromXml(Symbol* s, xmlTextReaderPtr reader) {
        ArcShape* arcshape;
        std::string x1      = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"x1"));
        std::string x2      = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"x2"));
        std::string y1      = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"y1"));
        std::string y2      = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"y2"));
        std::string start   = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"start"));
        std::string span    = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"span"));

        if(!x1.empty() and !x2.empty() and !y1.empty() and !y2.empty() and !start.empty() and !span.empty()){
            arcshape = new ArcShape(s, std::stoi(start), std::stoi(span), std::stoi(x1), std::stoi(y1), std::stoi(x2), std::stoi(y2));
            return arcshape;
        }
        return NULL;
    }
}