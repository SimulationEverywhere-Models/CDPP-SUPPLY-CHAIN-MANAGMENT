// $Header: c:/usuarios/alex/uba/tesis/cvsroot/simu/ggadstate.h,v 1.2 2001/04/15 15:43:19 Ale Exp $

#ifndef __GGADSTATE_H__
#define __GGADSTATE_H__

#include <string>
/**#include "cdTime.h"
 *
 */
#include "ggaddebug.h"


/** A state of the Ggad model.
    @ingroup model
*/
class GgadState {
    std::string name;
    Time timeAdvance;

public:
    // default constructor
    GgadState()
        : name(""),
        timeAdvance(Time::Inf)
    {
        //DM("State Constructor vacio");
    }


    // copy constructor
    GgadState( const GgadState &state )
    {
        //DM( "State copy constructor");
        name=state.getName();
        timeAdvance=state.getTimeAdvance();
        //D(name);
        //D(getName() );
        //D(state.name);

    }


    GgadState(const std::string &name_)
        : name(name_),
        timeAdvance(Time::Inf)
    {
        //DM("State constructor(std::string)");
        //D(name);
    }

    GgadState(std::string &name, Time time)
        : timeAdvance(time) {
        //DM("State constructor(std::string, time)");
        this->name = name;
        //D(name);
    }

    const Time& getTimeAdvance() const {
        return timeAdvance;
    }


    void setTimeAdvance(const Time &ta) {
        this->timeAdvance = ta;
    }

    const std::string& getName() const {
        return name;
    }

    std::string asString() const {
        return name + "," + "(" + timeAdvance.asString() + ")";
    }
};

#endif //__GGADSTATE_H__
