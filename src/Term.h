#ifndef NETLIST_TERM_H
#define NETLIST_TERM_H

#include <iostream>
#include <vector>
#include <string>
#include "Node.h"
#include "Cell.h"
#include "Instance.h"

namespace Netlist{
    class Net;

    class Term {
        public:
            enum Type { Internal=1, External =2 };
            enum Direction { In=1, Out=2, Inout=3, Tristate=4, Transcv =5, Unknown =6 };
        private:
            void*           owner_;
            std::string     name_;
            Direction       direction_;
            Type            type_;
            Net*            net_;
            NodeTerm        node_;  
        public:
                                Term ( Cell* , const std::string& name , Direction );
                                Term ( Instance*, const Term* modelTerm );
                                ~Term ();
            bool                isInternal () const;
            bool                isExternal () const;
            const std:: string& getName () const;
            NodeTerm*               getNode ();
            Net*                getNet () const;
            Cell*               getCell () const;
            Cell*               getOwnerCell () const;
            Instance*           getInstance () const;
            Direction           getDirection () const;
            Point               getPosition () const;
            Type                getType () const;
            void                setNet ( Net* );
            void                setNet ( const std::string& );
            void                setPosition ( const Point& );
            void                setPosition ( int x, int y );
            void                setDirection ( Direction );
            static std::string  toString    ( Type );
            static std::string  toString    ( Direction );
            static Direction    toDirection ( std::string );
            void                toXml(std::ostream& o);
            static Term*        fromXml(Cell*, xmlTextReaderPtr);
    };
}



#endif
