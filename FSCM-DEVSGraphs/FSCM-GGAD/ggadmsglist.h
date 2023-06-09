
#ifndef __GGADMSGLIST_H_
#define __GGADMSGLIST_H_

#include <string>
#include <sstream>
#include <map>

/**#include "cdTime.h"
*/
#include "ggadvalue.h"

/**
A message.
*/
class GgadMsg {
    /** name of port */
    std::string portName_;
    /** time at which the message was received. */
    Time t_;
    /** value received. */
    GgadValue value_;

public:
    GgadMsg ( const std::string &portName, Time eventTime, GgadValue value )
        : portName_(portName), t_(eventTime), value_(value)
    {}

    const std::string& getName() { return portName_; }
    Time getTime() { return t_; }
    GgadValue getValue() { return value_; }
    const std::string asString() {
        std::ostringstream s;
        s << "( "
            << portName_
            << ", "
            << t_.asString()
            << ", "
            << value_
            <<" )";
        return s.str();
    }

} ;



/**
Bag of messages received and its values indexed by the receiving port.
*/

typedef std::multimap< const std::string, GgadMsg > GgadMsgList;

std::string GgadMsgListAsString( GgadMsgList &valueList );
GgadValue GgadMsgListFind( GgadMsgList &msgList, const std::string &portName );

#endif // __GGADMSGLIST_H_
