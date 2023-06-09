// $Header: c:/usuarios/alex/uba/tesis/cvsroot/simu/ggadimpl.h,v 1.3 2001/05/13 20:06:12 Ale Exp $

// Implementación de un modelo devs grafico

#ifndef __GGADIMPL_H__
#define __GGADIMPL_H__

#include <string>
#include <map>
#include "ggadport.h"
#include "ggadstate.h"
#include "ggadtrans.h"
#include "ggadsymboltable.h"
#include "ggadsyntax.h"
#include "ggadmsglist.h"
#include "ggaddynstateadapter.h"
#include "ggadvariable.h"
#include "ggadportvaluelist.h"

/** @defgroup model Model Implementation
*/


class GgadImplException {
    std::string message_;
public:
    GgadImplException( const std::string &message) : message_(message) {}
    const std::string &getMessage() { return message_; }
};


/** Exception too many found. */
class GgadImplNotFoundException : public GgadImplException {
public:
    GgadImplNotFoundException( const std::string &message)
        : GgadImplException( message ) {}
};



/** Exception too many found. */
class GgadImplTooManyException : public GgadImplException {
    std::string message_;
public:
    GgadImplTooManyException( const std::string &message)
            : GgadImplException( message ) {}
};



/** GGAD model implementation.
    @ingroup model
*/
class GgadImpl {

    /** A std::map of ports. The key is the port name. */
    typedef std::map<std::string, GgadPort> PortHash;

    /** A std::map of states. The key is the state name. */
    typedef std::map<std::string, GgadState> BurbujasHash;

    /** A std::map of internal transitions. The key is the source state name. */
    typedef std::map<std::string, GgadTransInt> TransInterna;

    typedef std::map<std::string, GgadValue> VariableValues;

    PortHash inports;
    PortHash outports;
    BurbujasHash burbujas;
    GgadTransStore transExterna;
    TransInterna transInterna;
    GgadVariableValues variables;

    /** The initial state of the model. */
    std::string initialStateName;

    /** The symbol table of the model. */
    GgadSymbolTable *table;

public:
    // @todo Let Ggad access the port lists in a cleaner way.
    friend class Ggad;

    GgadImpl();
    ~GgadImpl();

    void addInPort(const std::string &name);
    GgadPort* getInPort(const std::string &name);

    void addOutPort(const std::string & name);
    GgadPort* getOutPort(const std::string &name);

    void addState(const std::string &name);

    GgadState& getState(const std::string &name);
    bool isState(const std::string &name);

    void setTimeAdvance( const std::string &stateId, const std::string &timeAdvance );
    void setTimeAdvanceInfinite( const std::string &stateId );

    GgadState& getInitialState();
    void setInitialState(const std::string &name);

    void addTransExt(std::string& source, std::string& dest, GgadSyntaxNode *exp, GgadSyntaxNode *actions);
    GgadTransExt* getTransExt( const std::string &stateName, GgadDynamicStateAdapter &dynState);

    void addTransIntOutput( std::string& source, std::string& dest, GgadPortValueList* outputs, GgadSyntaxNode *actions);
    GgadTransInt* getTransInt( const std::string &stateName );
    GgadPortValueList *getStateOutput( const GgadState &state );

    void setSymbolTable( GgadSymbolTable *t) { table = t; }
    GgadSymbolTable *getSymbolTable() { return table; }

    GgadVariableValues &getVariables() { return variables; }
    void addVariable( const std::string &varName, const GgadValue &value );

    void printOn(ostream &s);

};


#endif //__GGADIMPL_H__
