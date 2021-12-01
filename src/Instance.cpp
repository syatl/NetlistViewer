#include "Instance.h"
#include "Cell.h"
#include "Shape.h"

namespace Netlist{
    
    Instance::Instance ( Cell* owner , Cell* model , const std::string& str) 
            : owner_(owner), masterCell_(model), name_(str)
    {
        owner_->add(this);
        std::vector<Term*> cell_terms = model->getTerms();
        for(size_t i = 0; i < cell_terms.size(); ++i)
            add(new Term(this, cell_terms[i]));
        
    }

    Instance::~Instance () {
        for(size_t i = 0; i < terms_.size(); ++i)
            delete terms_[i];
    }
    
    const std::string& Instance::getName () const { return name_; }
    
    Cell* Instance::getMasterCell () const { return masterCell_; }
    
    Cell* Instance::getCell () const {  return owner_; }
    
    const std::vector<Term*>&  Instance::getTerms () const { return terms_; }
    
    Term* Instance::getTerm(const std::string& str) const { 
        for(size_t i = 0; i < terms_.size(); i++){
            if(terms_[i]->getName() == str)
                return terms_[i];
        }
        return NULL;
    }
    
    Point Instance::getPosition() const { return position_; }
    
    bool Instance::connect(const std::string& name, Net* n) {
        Term* t = getTerm(name);
        if(t != NULL){
            t->setNet(n);
            return true;
        }
        return false;
    }
    
    void Instance::add(Term* t) {
        terms_.push_back(t);
    }
    
    void Instance::remove(Term* t) {
        for(size_t i = 0; i < terms_.size(); i++){
            if(terms_[i] == t)
                terms_.erase(terms_.begin()+i);
        }
    }   
    
    void Instance::setPosition(const Point& p) {
        position_ = Point(p);
        std::vector<Shape*> shapes = getMasterCell()->getSymbol()->getShapes();
        std::vector<Shape*>::iterator it;
        TermShape* termshape;
        Term* t;
        for(it = shapes.begin(); it != shapes.end(); ++it){
            termshape = dynamic_cast<TermShape*>(*it);
            if(termshape != NULL){
                t = getTerm(termshape->getTerm()->getName());
                t->setPosition(getPosition().translate(termshape->getX(), termshape->getY()));
            }
        }
    }
    
    void Instance::setPosition(int x, int y) {
        position_ = Point(x, y);
        std::vector<Shape*> shapes = getMasterCell()->getSymbol()->getShapes();
        std::vector<Shape*>::iterator it;
        TermShape* termshape;
        Term* t;
        for(it = shapes.begin(); it != shapes.end(); ++it){
            termshape = dynamic_cast<TermShape*>(*it);
            if(termshape != NULL){
                t = getTerm(termshape->getTerm()->getName());
                t->setPosition(getPosition().translate(termshape->getX(), termshape->getY()));
            }
        }
    }

    void Instance::toXml(std::ostream& o) {
        o << "      <instance name=\"" << name_ << "\" mastercell=\"" << masterCell_->getName() << "\" x=\"" << position_.getX() << "\" y=\"" << position_.getY() << "\"/>" << std::endl;
    }

    Instance* Instance::fromXml(Cell* cell, xmlTextReaderPtr reader) {
        Instance* inst;
        std::string model = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"mastercell" ) );
        std::string name  = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"name" ) );
        std::string x     = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"x" ) );
        std::string y     = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"y" ) );

        if(!name.empty() or !model.empty() or !x.empty() or !y.empty()) {
            inst = new Instance(cell, Cell::find(model), name);
            inst->setPosition(std::stoi(x), std::stoi(y));
            return inst;
        }    
        return NULL;
        
    }
}
