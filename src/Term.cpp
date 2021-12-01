#include "Term.h"
#include "Net.h"

namespace Netlist{
    Term::Term (Cell* c, const std::string& name , Direction d)
        : node_(this), owner_(c), name_(name), direction_(d), net_(NULL) 
        {
            ((Cell*)owner_)->add(this);
        }
    Term::Term(Instance* i, const Term* modelTerm )
        : node_(this), owner_(i), name_(modelTerm->getName()), direction_(modelTerm->getDirection()), type_(Internal), net_(NULL)
        {
            ((Instance*)owner_)->add(this);
        }

    Term::~Term() {
        NodeTerm* ntrm = dynamic_cast<NodeTerm*>(&node_);

        if(type_ == Internal)
            ((Instance*)owner_)->remove(this);
        else 
            ((Cell*)owner_)->remove(this);
        if(net_ != NULL){
            net_->remove(&node_);
        }
    }

    bool Term::isInternal() const {
        if(type_ == Internal)
            return true;
        return false;
    }
    
    bool Term::isExternal() const { 
        if(type_ == Internal)
            return false;
        return true;
    }
    
    const std::string& Term::getName() const { return name_; }
    
    NodeTerm* Term::getNode() { return &node_;}
    
    Net* Term::getNet() const { return net_;}
    
    Cell* Term::getCell() const { return (type_ == External) ? static_cast <Cell*>(owner_) : NULL; }
    
    Cell* Term::getOwnerCell() const {
        if(isExternal()) 
            return (Cell*)owner_;
        return ((Instance*)owner_)->getCell();
    }
    
    Instance* Term::getInstance() const { return (type_ == Internal) ? static_cast <Instance*>(owner_) : NULL; }
    
    Term::Direction Term::getDirection() const { return direction_; }
   
    Point Term::getPosition() const { return node_.getPosition(); }
    
    Term::Type Term::getType() const {return type_;}
    
    void Term::setNet(Net* n) {
        if(n == NULL){
            net_->remove(&node_);
            net_ = NULL;
        }
        else if(net_ == NULL){
            n->add(&node_);
            net_ = n;
        }
        else{
            if(net_->remove(&node_)){
                n->add(&node_);
                net_ = n;
            }
        }
    }
    
    void Term::setNet(const std::string& str) { 
        setNet(getOwnerCell()->getNet(str));
    }
    
    void Term::setPosition(const Point& p) { node_.setPosition(p); }
    
    void Term::setPosition(int x, int y) { node_.setPosition(x, y); }
    
    void Term::setDirection(Direction d) { direction_ = d; }

    std::string Term::toString(Term::Type t) { 
        if(t == Term::Internal)
            return "Internal";
        else if(t == Term::External)
            return "External";
        return "";
    }
    
    std::string Term::toString (Term::Direction d) { 
        switch(d){
            case(Term::In):         return "In"; break;
            case(Term::Out):        return "Out"; break;
            case(Term::Inout):      return "Inout"; break;
            case(Term::Tristate):   return "Tristate"; break;
            case(Term::Transcv):    return "Transcv"; break;
            case(Term::Unknown):    return "Unkown"; break;
        }
        return "";
    }
    
    Term::Direction Term::toDirection ( std::string str) { 
        if(str == "In")
            return Term::In;
        else if(str == "Out")
            return Term::Out;
        else if(str == "Inout")
            return Term::Inout; 
        else if(str == "Tristate")
            return Term::Tristate;
        else if(str == "Transcv")
            return Term::Transcv;
        return Term::Unknown;        
    }

    void Term::toXml(std::ostream& o) {
        o << "      <term name=\"" << name_ << "\" direction=\"" << toString(direction_) << "\"" << " x=\"" << getPosition().getX() << "\"" << " y=\"" << getPosition().getY() << "\"/>" << std::endl;
    }

    Term* Term::fromXml(Cell* cell, xmlTextReaderPtr reader) {
        Term* term;
        Direction dir;
        std::string termName = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"name" ) );
        std::string termDir  = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"direction" ) );
        std::string termX    = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"x" ) );
        std::string termY    = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"y" ) );

        if(!termName.empty() and !termDir.empty() and !termX.empty() and !termY.empty()){
            if((dir = toDirection(termDir)) == Term::Unknown)
                return NULL;
            term = new Term(cell, termName, dir);
            term->setPosition(std::stoi(termX), std::stoi(termY));
            return term;
        }
        return NULL;
    } 
}   