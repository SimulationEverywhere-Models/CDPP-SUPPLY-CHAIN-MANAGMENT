// $Id$

#ifndef __GGADPARSYM_H__
#define __GGADPARSYM_H__

#include <string>
#include <list>
#include <sstream>

#include "ggadvalue.h"
#include "ggadmsglist.h"
#include "ggaddebug.h"
// defines the parameter to execute methods
#include "ggaddynstateadapter.h"

/** @defgroup syntax Syntax nodes
    @{
*/


/**
Abstract base class of all nodes in the Ggad syntax tree used for evaluating
rules in transitions.
*/
class GgadSyntaxNode {
public:

    GgadSyntaxNode() {};

    /** copy constructor. */
    GgadSyntaxNode( const GgadSyntaxNode & ) {};

    virtual ~GgadSyntaxNode() {}

    virtual GgadValue evaluate(GgadDynamicStateAdapter *valueList) = 0;

    virtual ostream &print( ostream & ) = 0;

    std::string asString() {
        std::ostringstream s;
        this->print(s);
        return s.str();
    }

    virtual GgadSyntaxNode *clone() = 0;

    virtual const std::string name() = 0;

};



/**
Node to evaluate a function.
*/
class GgadFunctionNode : public GgadSyntaxNode {
private:
    std::string name_;
    typedef std::list<GgadSyntaxNode*> Parameters;
    Parameters parameters;
public:
    GgadFunctionNode() {
        DM( name() );
    }

    ~GgadFunctionNode() {
        DM ( asString() );
        for ( Parameters::iterator i = parameters.begin(); i != parameters.end(); i++ ) {
            DM( (*i)->asString() );
            delete *i;
            DM("");
        }
        DM ( "" );
    }

    /** copy constructor.
    */
    GgadFunctionNode(const GgadFunctionNode &function)
    : name_(function.name_)
    {
        DM (name() << "::copy constructor " );
        GgadFunctionNode *f = const_cast<GgadFunctionNode*> (&function);
        DM ( f->asString() );
        for ( Parameters::iterator i = f->parameters.begin(); i != f->parameters.end(); i++ ) {
            //DM( (*i)->asString() );
            GgadSyntaxNode *n = (*i)->clone();
            //DM( n->asString() );
            parameters.push_back( n );
        }
        DM ( asString() );
    }

    GgadSyntaxNode *clone() {
        DM( name() + ".clone()" );
        GgadFunctionNode *f = new GgadFunctionNode(*this);
        DM( f->asString() );
        return f;
    }

    /** Sets the name of the function to be invocked. */
    void setName( const std::string &name ) { name_=name; }

    /** adds an actual parameter to the function. */
    void addParameter( GgadSyntaxNode *p ) {
        DM( name() << " function name 123456, #parameters " << parameters.size() << " " << asString() );
        parameters.push_front(p);
    }

    /** Evaluate a function. */
    virtual GgadValue evaluate(GgadDynamicStateAdapter *valueList);

    const std::string name() { return "GgadFunctionNode"; }

    virtual ostream &print( ostream &os ) {
        os << name() << ": " << name_ << "( ";
        for ( Parameters::iterator i = parameters.begin(); i != parameters.end(); i++ ) {
            os << *i << ":";
            (*i)->print( os );
            os << " ";
        }
        os << ") ";
        return os;
    }

};


/**
Syntax node to evaluate a constant.
*/
class GgadConstantNode : public GgadSyntaxNode {
private:
    GgadValue value_;

public:
    /**
    Constructor.
    @param value a constant (by example: 1234).
    */
    GgadConstantNode( const GgadValue value ) : value_( value ) {}

    /** copy constructor. */
    GgadConstantNode( const GgadConstantNode &value )
    : value_( value.value_ )
    {}

    GgadSyntaxNode *clone() {
        DM( name() + ".clone()" );
        return new GgadConstantNode( *this );
    }

    virtual GgadValue evaluate(GgadDynamicStateAdapter *valueList) { return value_; }

    const std::string name() { return "GgadConstantNode"; }

    ostream &print( ostream &os ) {
        os << name() << ": " << value_;
        return os;
    }

};


/**
Syntax node for ggad input operator.
*/
class GgadInputNode : public GgadSyntaxNode {
private:
    GgadSyntaxNode *function_;
    GgadConstantNode *value_;
public:
    GgadInputNode( GgadSyntaxNode *function, GgadConstantNode *value )
    : function_(function), value_(value)
    {}

    /** copy constructor. */
    GgadInputNode( const GgadInputNode &node ) {
        //DM("[ENTRY] GgadInputNode(" <<   ")" );
        function_ =  node.function_->clone();
        value_ = new GgadConstantNode( *(node.value_) );
        DM( function_->asString());
    }

    ~GgadInputNode() {
        delete function_;
        delete value_;
    }

    GgadSyntaxNode *clone() {
        DM( name() + ".clone()" );
        return new GgadInputNode( *this );
    }

    virtual GgadValue evaluate(GgadDynamicStateAdapter *valueList);

    const std::string name() { return "GgadInputNode"; }

    ostream &print( ostream &os ) {
        os << name() << ": ";
        function_->print(os);
        os << " ? ";
        value_->print(os);
        return os;
    }
};

/**
Syntax node for evaluating the value in an input port.
*/
class GgadPortInNode : public GgadSyntaxNode {
private:
    std::string portName_;
public:
    GgadPortInNode( const std::string &portName )
    : portName_(portName)
    {}

    /** copy constructor. */
    GgadPortInNode( const GgadPortInNode &node )
    : portName_(node.portName_)
    { DM (""); }

    GgadSyntaxNode *clone() {
        DM( name() + ".clone()" );
        return new GgadPortInNode( *this );
    }

    virtual GgadValue evaluate(GgadDynamicStateAdapter *valueList);

    const std::string name() { return "GgadPortInNode"; }

    ostream &print( ostream &os ) {
        os << name() << ":" << portName_ << " ";
        return os;
    }
};


/**
A syntax tree node to evaluate variables.
*/
class GgadVariableNode : public GgadSyntaxNode {
private:
    std::string variableName;

public:
    GgadVariableNode( const std::string &name )
    : variableName( name )
    {}

    GgadVariableNode( const GgadVariableNode &node )
    : variableName(node.variableName)
    {}

    GgadSyntaxNode *clone() {
        DM( name() + ".clone()" );
        return new GgadVariableNode( *this );
    }

    virtual GgadValue evaluate(GgadDynamicStateAdapter *dynState);

    const std::string name() { return "GgadVariableNode"; }

    ostream &print( ostream &os ) {
        os << name() << ":" << variableName << " ";
        return os;
    }

};


/** @} */   // end of syntax group



/** @defgroup actions Actions nodes.
    @{
*/


/** Abstract base class for action nodes. Actions differ from normal nodes
    in that they have side effects. If we need to implent action general
    behavior it could be done here.
*/
class GgadActionNode : public GgadSyntaxNode {
};



/** A syntax tree node that represent a list of actions.
*/

class GgadActionListNode : public GgadActionNode {
private:
    typedef std::list<GgadSyntaxNode*> Actions;
    Actions actions;

public:
    GgadActionListNode() {
        DM( name() );
    }

    virtual ~GgadActionListNode() {
        DM( "~GgadActionListNode " << this );
        for ( Actions::iterator i = actions.begin(); i != actions.end(); i++ ) {
            delete *i;
        }
    }

    GgadActionListNode( const GgadActionListNode &node )
    {
        DM( "GgadActionListNode copy constructor from " << &node );
        GgadActionListNode *l = const_cast<GgadActionListNode*> (&node);
        DM( l->asString() );
        for ( Actions::iterator i = l->actions.begin(); i != l->actions.end(); i++ ) {
            DM( (*i)->asString() );
            GgadSyntaxNode *n = (*i)->clone();
            DM( n->asString() );
            actions.push_back( n );
        }
        DM( "this=" << this );
    }

    GgadSyntaxNode *clone() {
        DM( name() + ".clone()" );
        return new GgadActionListNode( *this );
    }

    void addAction( GgadSyntaxNode *a ) {
        DM( "addAction( " << a->asString() << ")" );
        actions.push_back(a);
    }

    virtual GgadValue evaluate(GgadDynamicStateAdapter *dynState);

    const std::string name() { return "GgadActionListNode"; }

    ostream &print( ostream &os ) {
        os << name() << " cointaining " << actions.size() << " elements = { ";
        for ( Actions::iterator i = actions.begin(); i != actions.end(); i++ ) {
            os << (*i)->asString();
        }
        os << " }";
        return os;
    }

};


/**
A syntax tree node that assigns to a variable. <b>Because is an action this node modifies the state of the model.</b>
*/
class GgadSetVariableNode : public GgadActionNode {
private:
    std::string variableName;
    GgadSyntaxNode *exp_;

public:
    GgadSetVariableNode( const std::string &name, GgadSyntaxNode *exp )
    : variableName( name ), exp_(exp)
    {}

    GgadSetVariableNode( const GgadSetVariableNode &node )
    : variableName(node.variableName), exp_(node.exp_)
    {}

    GgadSyntaxNode *clone() {
        DM( name() + ".clone()" );
        return new GgadSetVariableNode( *this );
    }

    virtual GgadValue evaluate(GgadDynamicStateAdapter *dynState);

    const std::string name() { return "GgadSetVariableNode"; }

    ostream &print( ostream &os ) {
        os << name() << ":" << variableName << "= [" << exp_->asString() << "]";
        return os;
    }

};


/** A null action. This action does nothing.
*/
class GgadNullActionNode : public GgadActionNode {
public:

    ~GgadNullActionNode() {
        DM( "~GgadNullActionNode " << this );
    }

    GgadSyntaxNode *clone() {
        DM( name() + ".clone()" );
        GgadActionNode *a = new GgadNullActionNode();
        DM( a );
        return a;
    }

    virtual GgadValue evaluate(GgadDynamicStateAdapter *dynState);

    const std::string name() { return "GgadNullActionNode"; }

    ostream &print( ostream &os ) {
        os << name();
        return os;
    }
};

/** @} */   // end of group actions

#endif //__GGADPARSYM_H__


