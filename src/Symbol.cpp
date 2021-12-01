#include "Symbol.h"
#include "Shape.h"

namespace Netlist {
    Symbol::Symbol(Cell* c)
        : owner_(c)
        {}
    
    Symbol::~Symbol() 
        {}
    
    Cell* Symbol::getCell() const {
        return owner_;
    }

    Box Symbol::getBoundingBox() const {
        Box bb;
        for(size_t i = 0; i < shapes_.size(); ++i)
            bb.merge(shapes_[i]->getBoundingBox());
        return bb;
    }

    Point Symbol::getTermPosition(Term* t) const {
        TermShape* termshape = getTermShape(t);
        Point pt;
        if(termshape != NULL)
            return Point(termshape->getX(), termshape->getY());
        return Point();
    }

    TermShape* Symbol::getTermShape(Term* t) const {
        TermShape* termshape;
        for(size_t i = 0; i < shapes_.size(); ++i){
            termshape = dynamic_cast<TermShape*>(shapes_[i]);
            if(termshape->getTerm() == t)
                return termshape;
        }
        return NULL;
    }

    void Symbol::add(Shape* s) {
        shapes_.push_back(s);
    }

    void Symbol::remove(Shape* s) {
        std::vector<Shape*>::iterator it;
        for(it = shapes_.begin(); it != shapes_.end(); ++it){
            if(*it == s) 
                shapes_.erase(it);
        }
    }

    void Symbol::toXml(std::ostream& o) const {
        o << "  <symbol>" << std::endl;
        for(size_t i = 0; i < shapes_.size(); ++i){
            o << "      ";
            shapes_[i]->toXml(o);
        }
        o << "  </symbol>" << std::endl;
    }

    Symbol* Symbol::fromXml(Cell* c, xmlTextReaderPtr reader) {
        Symbol* symbol;
        const xmlChar* name;
        int status;
        if((symbol = c->getSymbol()) == NULL)
            return NULL;

        const xmlChar* symboltag = xmlTextReaderConstString(reader, (const xmlChar*)"symbol");
        
        while(true){
            status = xmlTextReaderRead(reader);

            if(status != 1){
                if(status != 0){
                    std::cerr << "[ERROR] Symbol::fromXml(): Unexpected termination of the XML parser." << std::endl;
                }
                break;
            }
            switch (xmlTextReaderNodeType(reader)){
                case XML_READER_TYPE_COMMENT:
                case XML_READER_TYPE_WHITESPACE:
                case XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
                continue;
            }

            name = xmlTextReaderConstLocalName(reader);
            if((name == symboltag) and (xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT))
                break;
            if(Shape::fromXml(symbol, reader))
                continue;

            std::cerr << "[ERROR] Symbol::fromXml(): Unkown or misplaced tag <" << name << "> (line:" << xmlTextReaderGetParserLineNumber(reader) << ")." << std::endl;
            break;
        }
        return symbol;
    }
    
}