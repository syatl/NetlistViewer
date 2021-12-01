#include "Net.h"
#include "Term.h"

namespace Netlist {
    Net::Net(Cell* c, const std::string& str, Term::Type t) 
        :owner_(c), name_(str), id_(0), type_(t)
    {
        owner_->add(this);
    }
    
    Net::~Net() {
        NodeTerm* ntrm;
        for(size_t i = 0; i < nodes_.size(); ++i){
            ntrm = (NodeTerm*)nodes_[i];
            if(ntrm)
                ntrm->getTerm()->setNet(NULL); 
        }
    }

    Cell* Net::getCell()const { return owner_; }

    const std::string& Net::getName () const { return name_; }
    
    unsigned int Net::getId() const { return id_; }
    
    Term::Type Net::getType() const { return type_; }
    
    Node* Net::getNode(size_t id) const {
        if(id < nodes_.size())
            return nodes_[id];
        return NULL;
    }
    
    const std::vector<Node*>& Net::getNodes() const { return nodes_; }
    
    size_t Net::getFreeNodeId() const {
        for(size_t i = 0; i < nodes_.size(); ++i){
            if(nodes_[i] == NULL)
                return i;
        }
        return nodes_.size();
    }
    
    void Net::add(Node* n) {
        size_t id = n->getId();
        if(id == Node::noid){
            id = getFreeNodeId();
            n->setId(id);
        }
        if(id < nodes_.size())
            nodes_[id] = n;
        else{
            nodes_.resize(id+1);
            nodes_[id] = n;
        }
    }
    
    bool Net::remove(Node* n) { 
        for(size_t i = 0; i < nodes_.size(); ++i){
            if(nodes_[i] == n){
                nodes_[i] = NULL;
                return true;
            }
        }
        return false;
    }  

    void  Net::add ( Line* line )
    { if (line) lines_.push_back( line ); }

    bool  Net::remove ( Line* line )
    {
        if (line) {
            for ( std::vector<Line*>::iterator il = lines_.begin(); il != lines_.end() ; ++il ) {
                if (*il == line) {
                    lines_.erase( il );
                    return true;
                }
            }
        }
        return false;
    }
    void Net::toXml(std::ostream& o) {
        o << "      <net name=\"" << name_ << "\" type=\"" << Term::toString(type_) << "\"/>" << std::endl;
        for(size_t i = 0; i < nodes_.size(); ++i){
            if(nodes_[i] != NULL){
                o << "      ";
                nodes_[i]->toXml(o);
            }
        }
        for(size_t i = 0; i < lines_.size(); ++i){
                o << "      ";
                lines_[i]->toXml(o);
        }
        o << "      " << "</net>" << std::endl;
    }

    Net* Net::fromXml(Cell* cell, xmlTextReaderPtr reader) {
        Net* net;
        Term::Type t;
        const xmlChar* ntag;
        const xmlChar* nname;
        const xmlChar* ltag;

        int status;
        std::string name = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"name" ) );
        std::string type = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"type" ) );
        
        if(!name.empty() and !type.empty()){
            if(type == Term::toString(Term::Internal))
                t = Term::Internal;
            else if(type == Term::toString(Term::External))
                t = Term::External;
            else 
                return NULL;
            net = new Net(cell, name, t);
        }
        else 
            return NULL;
        
        ntag = xmlTextReaderConstString(reader, (const xmlChar*)"node");
        ltag = xmlTextReaderConstString(reader, (const xmlChar*)"line");
        while(true) {
            status = xmlTextReaderRead(reader);
            if (status != 1){
                if (status != 0)
                    std::cerr << "[ERROR] Net::fromXml(): Unexpected termination of the XML parser." << std::endl;
                break;
            }
            switch ( xmlTextReaderNodeType(reader) ){
                case XML_READER_TYPE_COMMENT:
                case XML_READER_TYPE_WHITESPACE:
                case XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
                continue;
            }

            nname = xmlTextReaderConstLocalName(reader);

            if(nname == ntag){
                if(xmlTextReaderNodeType(reader) == XML_READER_TYPE_ELEMENT){
                    if(!Node::fromXml(net, reader))
                        return NULL;
                }
                else if(xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT)
                    break;
            }
            else if(nname == ltag){
                if(xmlTextReaderNodeType(reader) == XML_READER_TYPE_ELEMENT){
                    if(!Line::fromXml(net, reader))
                        return NULL;
                }
                else if(xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT)
                    break;
                else 
                    return NULL;
            }
            else
                break;
        }
        return net;
    }       

}
