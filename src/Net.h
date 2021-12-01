#ifndef NETLIST_NET_H
#define NETLIST_NET_H

#include <iostream>
#include <vector>
#include <string>
#include "Cell.h"
#include "Term.h"
#include "Node.h"
#include "Line.h"

namespace Netlist{
    class Term;
    
    class Net {
        private:
            Cell*               owner_;
            std::string         name_;
            unsigned int        id_;
            Term::Type          type_;
            std::vector<Node*>  nodes_;
            std::vector<Line*>  lines_;
            
        public:
                                        Net (Cell*, const std:: string&, Term::Type);
                                        ~Net ();
            Cell*                       getCell () const;
            const std::string&          getName () const;
            unsigned int                getId () const;
            Term::Type                  getType () const;
            Node*                       getNode ( size_t id ) const;
            const std::vector<Node*>&   getNodes () const;
            size_t                      getFreeNodeId () const;
            void                        add ( Node* );
            void                        add ( Line* line );
            bool                        remove ( Node* );  
            bool                        remove ( Line* line );
            void                        toXml(std::ostream&);
            static Net*                 fromXml(Cell*,xmlTextReaderPtr);
            inline const std::vector<Line*>& getLines () const{  return lines_; }
            
                                        
    };
}

#endif