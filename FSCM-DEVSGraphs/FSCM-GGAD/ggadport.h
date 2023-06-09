// $Header: c:/usuarios/alex/uba/tesis/cvsroot/simu/ggadport.h,v 1.3 2001/05/13 20:06:12 Ale Exp $

// port de un modelo ggad

#ifndef __GGADPORT_H__
#define __GGADPORT_H__

#include <string>


/** A port of a model.
    @ingroup model
*/
class GgadPort {
    std::string name;
public:
    // default constructor
    GgadPort() { ; }

    // copy constructor
    GgadPort( const GgadPort &port ) {
        this->name = port.name;
    }


    GgadPort(const std::string &name) {
        this->name = name;
    }

    std::string &getName() {
        return name;
    }

    const std::string& asString() const { return name; }

};

#endif //__GGADPORT_H__
