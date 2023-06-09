

#ifndef __GGADDYNSTATE_H__
#define __GGADDYNSTATE_H__

#include <sstream>
#include <strutil.h>
#include "atomicstate.h"
#include "ggaddebug.h"
#include "ggadmsglist.h"
#include "ggadvariable.h"


/**
@ingroup cdplusplus Classes that depends on cd++ arquitecture
Atomic state of a Ggad Model.
*/

class GgadDynamicState : AtomicState {
    std::string actualStateName;
    GgadMsgList msgValues;

    GgadVariableValues variables;


public:

    GgadDynamicState() {
        DM( "GgadDynamicState constructor" );
    };


    virtual ~GgadDynamicState() {};


    /** initialize variables.
    */
    void initVariables( const GgadVariableValues &vars ) {
        // if this doesn't work try the commented code or stl copy
        DM( "initVariables()" );
        variables = vars;

        // check if values are right
        for( GgadVariableValues::iterator i = variables.begin();
             i != variables.end();
             i++) {
            //this->variables.push_back( *i );
            DM( (*i).first << "=" << (*i).second );
        }
    }

    /** copy constructor */
    GgadDynamicState( const GgadDynamicState &aState ) {
        DM( "GgadDynamicState copy constructor" );
        this->actualStateName = aState.actualStateName;
        this->msgValues = aState.msgValues;
        this->initVariables( aState.variables );
    }

    /** Assignment operator */
    GgadDynamicState &operator=(GgadDynamicState &dynState) {
        DM( "GgadDynamicState operator=" );
        /* handle self-assignment here if needed */
        if(this != &dynState) {
            this->actualStateName = dynState.actualStateName;
            this->msgValues = dynState.msgValues;
            this->initVariables( dynState.variables );
        }
        return *this;
    }

    /** Returns the size of the class in bytes. Must be implemented by each subclass.
        @warning Wonder what this does with STL.
    */
    int getSize() const {
        DM( "getSize =" << sizeof(GgadDynamicState) );
        return sizeof(GgadDynamicState);
    }

    void setMessages( const GgadMsgList &messages ) { msgValues = messages; }
    GgadMsgList &getMessages() { return msgValues; }

    void setCurrentState( std::string stateName ) { actualStateName = stateName; }
    std::string getCurrentState() { return actualStateName; }

    /** Assign a value to a variable. If the variable doesn't exists it is created, else
        the previous value is replaced.
        @param varName contains the name of the variable.
        @param value contains the value to be assigned.
    */
    void setVariableValue( std::string &varName, const GgadValue &value ) {
        variables[lowerCase(varName)]=value;
    }

    /** Obtains the current value of a variable.
        @param varName contains the name of the variable.
        @return The current value of variable whoose name is in varName.
    */
    GgadValue getVariableValue( const std::string &varName ) {
        GgadVariableValues::iterator iter = variables.find( lowerCase(varName) );
        if( iter != variables.end() ) {
            return ((*iter).second);
        } else {
            MException e;
            MTHROW(e);
        }
    }

    const std::string variablesAsString() {
        std::ostringstream s;
        for( GgadVariableValues::iterator i = variables.begin();
             i != variables.end();
             i++)
        {
            //this->variables.push_back( *i );
            s << " (" << (*i).first << "=" << (*i).second << ")";
        }
        return s.str();
    }
};


#endif // __GGADDYNSTATE_H__
