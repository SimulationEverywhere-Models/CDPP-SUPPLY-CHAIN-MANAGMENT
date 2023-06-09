

#if !defined(__GGADPORTVALUELIST_H__)
#define __GGADPORTVALUELIST_H__

#include <string>
#include <map>
#include <sstream>
#include "ggadsyntax.h"
#include "ggadvalue.h"
#include "ggaddebug.h"

typedef std::map < std::string, GgadSyntaxNode* > GgadPortValueList;

inline std::string GgadPortValueListAsString( GgadPortValueList *gpvl ) {
    DM( gpvl );
    std::ostringstream s;
    if ( gpvl != NULL ) {
        s << "[ ";
        for( GgadPortValueList::iterator i=gpvl->begin(); i != gpvl->end(); i++ ) {
            s << "( " << ((*i).first) << " ! " << (*i).second << " ) ";
        }
        s << " ]";
    } else {
        s << "NULL";
    }
    return s.str();

}

#endif        //  #if !defined(__GGADPORTVALUELIST_H__)

