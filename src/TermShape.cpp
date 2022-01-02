#include "Shape.h"

namespace Netlist {
    TermShape::TermShape(Symbol* s, std::string name, int x, int y, NameAlign na)
            : Shape(s), term_(NULL), x_(x), y_(y), align_(na)
    {
        Cell* cell = s->getCell();
        term_ = cell->getTerm(name);            
    }

    TermShape::~TermShape() {}

    Box TermShape::getBoundingBox() const {
        return Box(x_, y_, x_, y_); // boite vide ?
    }

    Term* TermShape::getTerm() const {
        return term_;
    }

    int TermShape::getX() const {
        return x_;
    }

    int TermShape::getY() const {
        return y_;
    }

    TermShape::NameAlign TermShape::getAlign() const {
        return align_;
    }

    std::string alignToString(TermShape::NameAlign a) {
        switch(a){
            case(TermShape::BottomLeft):    return "bottom_left"; break;
            case(TermShape::BottomRight):   return "bottom_right"; break;
            case(TermShape::TopLeft):       return "top_left"; break;
            case(TermShape::TopRight):      return "top_right"; break;
        }
        return NULL;
    }

    TermShape::NameAlign stringToAlign(std::string str) {
        if(str == "bottom_left")
            return TermShape::BottomLeft;
        else if(str == "bottom_right")
            return TermShape::BottomRight;
        else if(str == "top_left")
            return TermShape::TopLeft;
        else if(str == "top_right")
            return TermShape::TopRight;
        return TermShape::Unknown;
    }

    void TermShape::toXml(std::ostream& o) const {
        o << "<term name=\"" << term_->getName() << "\" x1=\"" << x_ << "\" y1=\"" << y_ << "\" align=\"" << alignToString(align_) << "\"/>" << std::endl; 
    }

    TermShape* TermShape::fromXml(Symbol* s, xmlTextReaderPtr reader) {
        TermShape* termshape;
        TermShape::NameAlign a;
        std::string name    = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"name"));
        std::string x       = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"x1"));
        std::string y       = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"y1"));
        std::string align   = xmlCharToString(xmlTextReaderGetAttribute(reader, (const xmlChar*)"align"));
        if(!name.empty() and !x.empty() and !y.empty() and !align.empty()){
            if((a = stringToAlign(align)) == TermShape::Unknown)
                return NULL;
            termshape = new TermShape(s, name, std::stoi(x), std::stoi(y), a);
            return termshape;
        }
        return NULL;
    }
}
