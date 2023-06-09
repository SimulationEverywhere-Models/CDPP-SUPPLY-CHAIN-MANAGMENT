// $Id$

#ifndef __GGADTRANS_H__
#define __GGADTRANS_H__


#include <map>
#include <list>

#include "strutil.h"
#include "ggadport.h"
#include "ggadstate.h"
#include "ggadsyntax.h"
#include "ggadvalue.h"
#include "ggaddebug.h"
#include "ggadportvaluelist.h"


/** Internal transition.
    @ingroup model
*/
class GgadTrans {
protected:
    /** Name of source state. */
    std::string origen;
    /** Name of destination state. */
    std::string destino;
    /** Actions to be executed on the transition. */
    GgadSyntaxNode *actions_;

public:

    GgadTrans() : actions_(NULL) {
        DM( "GgadTrans()" );
    }


    GgadTrans(const std::string &source, const std::string &dest, GgadSyntaxNode *actions)
    : origen(source), destino(dest), actions_(NULL) {
        DM("[ENTRY] GgadTrans( " << source << ", " << dest << ", " << actions << ")");
        if ( actions != NULL )
            actions_ = actions->clone();
        DM( "actions_=" << actions_ );
        DM("[EXIT] GgadTrans(...)");
    }

    /** Copy constructor */
    GgadTrans( const GgadTrans &trans )
    : origen( trans.origen ), destino (trans.destino), actions_(NULL) {
        DM( "[ENTRY] GgadTrans copy constructor "
            << trans.origen << "->"
            << trans.destino << " { "
            << trans.actions_ << " }"
        );
        if (trans.actions_ != NULL ) {
            actions_ = trans.actions_->clone();
        }
        DM( "[EXIT] GgadTrans copy constructor " << ", " << actions_ );
    }


    /** Asignment operator, we <b>MUST</b> implement this method to store the transition
        in STL containers, else will end with deleting twice the same pointers.
        A future versión could implement reference counting, avoiding the need of
        duplicate the syntax trees.
    */
    GgadTrans& operator=( const GgadTrans &trans ) {
        DM("operator=");
        if ( &trans != this ) { // self assignment check
            origen=trans.origen;
            destino=trans.destino;
            if ( trans.actions_ != NULL )
                actions_ = trans.actions_->clone();
        }
        DM( "[EXIT] operator=" );
        return *this;
    }

    virtual ~GgadTrans() {
        DM( "[ENTRY] ~GgadTrans()" );
        delete actions_;
        DM( "[EXIT] ~GgadTrans()" );
    }

    const std::string asString() {
        return origen + "->" + destino + " : "
               + ( actions_ != NULL ? actions_->asString() : "(action=NULL)" );
    };


    const std::string& getSource() const {
        return origen;
    }


    const std::string& getDestination() const {
        return destino;
    }


    GgadSyntaxNode *getActions() const {
        return actions_;
    }
};


class GgadTransInt : public GgadTrans {
    /** Output list. */
    GgadPortValueList *outputs_;

public:

    GgadTransInt() : outputs_(NULL) {
        DM( "GgadTransInt()" );
    }


    GgadTransInt( const std::string &source, const std::string &dest,
        GgadSyntaxNode *actions, GgadPortValueList *outputs )
    : GgadTrans( source, dest, actions), outputs_(NULL) {
        DM("[ENTRY] GgadTrans( " << source << ", " << dest << ", " << actions << ", " << outputs << " )");
        outputs_ = new GgadPortValueList();
        if ( outputs != NULL )
            *outputs_ = *outputs;

        DM("[EXIT] GgadTrans(...)" );
    }


    virtual ~GgadTransInt() {
        DM( "~GgadTransInt" );
        //delete actions_;
        delete outputs_;
    }


    /** Copy constructor */
    GgadTransInt( const GgadTransInt &trans )
    : GgadTrans( trans.origen, trans.destino, trans.actions_), outputs_(NULL) {
        DM( "[ENTRY] GgadTrans copy constructor "
            << trans.actions_
            << "(" << trans.outputs_ << ")"
        );

        if ( trans.outputs_ != NULL ) {
            outputs_ = new GgadPortValueList();
            if ( trans.outputs_ != NULL )
                *outputs_ = *(trans.outputs_);
        }
        /*if (trans.actions_ != NULL ) {
            actions_ = trans.actions_->clone();
        }*/
        DM( "[EXIT] GgadTrans copy constructor " << outputs_ << ", " << actions_ );
    }

    GgadTransInt& operator=( const GgadTransInt &trans ) {
        DM("operator=");
        if ( &trans != this ) { // self assignment check
            origen=trans.origen;
            destino=trans.destino;
            outputs_=new GgadPortValueList();
            if ( trans.outputs_ != NULL )
                *outputs_ = *(trans.outputs_);

            if ( trans.actions_ != NULL )
                actions_ = trans.actions_->clone();
        }
        DM( "[EXIT] operator=" );
        return *this;
    }


    GgadPortValueList *getOutputs() const {
        return outputs_;
    }


    const std::string asString() {
        return origen + "->" + destino + " : "
               + GgadPortValueListAsString( outputs_ ) + " / "
               + ( actions_ != NULL ? actions_->asString() : "(Null action)" );
    };

};


/** External transition.
    @ingroup model
*/
class GgadTransExt : public GgadTrans {
    /** Expresion to be evaluated. */
    GgadSyntaxNode *exp_;

public:

    GgadTransExt() : exp_(NULL) {
        DM( "" );
    }


    GgadTransExt(const std::string &source, const std::string &dest,
                    GgadSyntaxNode *actions, GgadSyntaxNode *exp)
        : GgadTrans( source, dest, actions ), exp_(NULL) {
        DM("GgadTransExt()");
        exp_ = exp->clone();
        //actions_ = actions->clone();
    }


    virtual ~GgadTransExt() {
        DM( "[ENTRY] ~GgadTransExt() of instance " << origen << "->" << destino );
        DM( "actions: " << actions_ );
        delete exp_;
        //delete actions_;
        DM( "[EXIT] ~GgadTransExt() of instance " << origen << "->" << destino );
    }


    GgadTransExt( const GgadTransExt &trans )
    : GgadTrans( trans.origen, trans.destino, trans.actions_ ), exp_(NULL)
    {
        GgadTransExt *t = const_cast<GgadTransExt *>(&trans);
        DM("[ENTRY] GgadTransExt( const GgadTransExt & " << t->asString() << " )");
        assert( trans.exp_ != NULL );
        exp_ = (trans.exp_)->clone();
        DM("[EXIT] GgadTransExt( const GgadTransExt &)");
    }


    /** Asignment operator, we <b>MUST</b> implement this method to store the transition
        in STL containers, else will end with deleting twice the same pointers.
        A future versión could implement reference counting for not having to
        duplicate the syntax trees.
    */
    GgadTransExt& operator=( const GgadTransExt &trans ) {
        if (&trans != this) { // self assignment check
            origen = trans.origen;
            destino = trans.destino;
            exp_ = (trans.exp_)->clone();
            if ( trans.actions_ != NULL ) {
                actions_ = trans.actions_->clone();
            }
        }
        return *this;
    }


    GgadSyntaxNode *getExp() const {
        return exp_;
    }


    const std::string asString() {
        return origen + "->" + destino + " : "
               + ( exp_ != NULL ? exp_->asString() : "(Null expresion)" ) + " / "
               + ( actions_ != NULL ? actions_->asString() : "(Null action)" );
    };


};


struct GgadTransKey {
    std::string origen;
    std::string port;

    const std::string asString() const {
        std::string s=origen + " / " + port;
        return s;
    }
};

struct transLess {
    bool operator() (const GgadTransKey& x, const GgadTransKey& y) const {
        if (x.origen < y.origen) return true;
        else if (x.origen == y.origen) return x.port < y.port;
        else return false;
    };
};


class GgadTransStore {
public:
    typedef std::list<GgadTransExt> TransList;

private:
    typedef std::map<std::string, TransList> TransMap;
    TransMap transMap;

public:

    void add( const std::string &sourceState, const GgadTransExt &trans );
    TransList & find( const std::string &sourceState );

    typedef TransMap::iterator iterator;
    iterator begin() { return transMap.begin(); }
    iterator end() { return transMap.end(); }
};

#endif //__GGADTRANS_H__
