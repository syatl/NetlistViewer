#ifndef NETLIST_ERROR_H
#define NETLIST_ERROR_H

#include <exception>
#include <string>

namespace Netlist {
    class Error {
        private:
            std::string message_;
        public: 
            Error(std::string message) throw() { message_ = message; };
        public: 
            ~Error() throw() {};
        public: 
            const char* what() const throw() { return message_.c_str(); };
    };
}


#endif