// $Header: c:/usuarios/alex/uba/tesis/cvsroot/simu/ggad.h,v 1.2 2001/04/15 15:43:19 Ale Exp $

// modelo atomico ggad para celldevs

#ifndef __GGAD_H__
#define __GGAD_H__

#include <string>
#include "atomic.h"
#include "ggaddynstate.h"
#include "ggadimpl.h"
#include "ggadmsglist.h"

/** @defgroup cdplusplus Classes that inherit from CD++
*/


/** GGAD Atomic model. Implements an atomic model for CD.
    @ingroup cdplusplus
*/
class Ggad : public Atomic {

public:
    Ggad( const std::string &name = "Ggad" );
    virtual ~Ggad();
    virtual std::string className() const { return "Ggad"; };

protected:
    Model &initFunction();

    //Model &externalFunction ( const MessageBag & );
    Model &externalFunction ( const ExternalMessage & );

    Model &internalFunction( const InternalMessage & );

    //Model &outputFunction( const CollectMessage & );
    Model &outputFunction( const InternalMessage & );

private:
    GgadImpl *myGI;
    GgadDynamicState modelState;

    virtual GgadState* getActualState();
    virtual void setActualStateId(std::string name);

    static GgadMsgList *CreateMsgList( const ExternalMessage &msg );
    //static GgadMsgList *CreateMsgList( const MessageBag &msgs );

    void logTrans( const std::string &type, const std::string &eventTime, const std::string &source, const std::string &destination );
    void logOutput( const std::string &eventTime, const std::string &portName, const GgadValue &value );
    void logMsgList( GgadMsgList &msgList );
};
#endif //__GGAD_H__
