// $Header$

#ifndef __GGADFUNC_H__
#define __GGADFUNC_H__

#include <list>
#include "ggadfuncexception.h"
#include "ggadvalue.h"

#define VALUE GgadValue

class GgadFunc {

protected:

    int formalParams;
    int actualParams;

    typedef std::list<GgadValue> Parameters;
    Parameters parameters;


    void setFormalParams(int c) {
        formalParams=c;
    }


    int getFormalParams() {
        //DM( formalParams );
        return formalParams;
    }


    void initActualParams() {
        actualParams=0;
    }


    void incActualParams() {
        actualParams++;
    }


    int getActualParams() {
        //DM( actualParams );
        return actualParams;
    }


    GgadValue getParameter( const int n ) {
        int counter=n;
        Parameters::iterator i=parameters.begin();
        while ( counter > 0 && i != parameters.end() ) {
            counter--;
            i++;
        }
        return *i;
    }


    /**
    This method must be overriden to implements each function's specific behaviour.
    */
    virtual GgadValue executeImpl() = 0;

public:
    GgadFunc() {
        //DM( "Constructor" );
        setFormalParams(-1);
        initActualParams();
        //DM( "exit Constructor" );
    }


    virtual ~GgadFunc() {
        //DM( "exit destructor" );
    };


    virtual std::string name() = 0;


    void clear() {
        parameters.clear();
        initActualParams();
    }


    void addParameter( GgadValue v ) {
        DM( "[ENTER] " << this << " [" << name() << "] addParameter " << v );
        DM( "actual=" << actualParams << " formal=" << formalParams );
        if ( getActualParams() >= getFormalParams() ) {
            // error: too much parameters
            DM("error");
            throw new GgadFuncException( "Too much parameters", getFormalParams() );
        } else {
            //DM("a");
            actualParams++;
            //DM("b");
            parameters.push_back(v);
            //DM("c");
        }
        /* debug
        int j=0;
        for(Parameters::iterator i = parameters.begin(); i != parameters.end(); i++ ) {
            GgadValue w = (*i);
            DM( "param[ " << j << "]=" << w );
            j++;
        } */
        DM( "[EXIT] addParameter" );
    }


    /**
    Public interface to execute a function.
    */
    virtual GgadValue execute() {
        if ( getActualParams() != getFormalParams() ) {
            // error: not enough parameters
            throw new GgadFuncException( "Too few parameters", getFormalParams() );
        } else {
            GgadValue v=executeImpl();
            // erase the parameters for next use. It would be better if symbol table
            // returns a new function object.
            clear();
            return v;
        }
    }


    /** Creates a new function object of this class. */
    virtual GgadFunc* create() = 0;
};



#endif // __GGADFUNC_H__
