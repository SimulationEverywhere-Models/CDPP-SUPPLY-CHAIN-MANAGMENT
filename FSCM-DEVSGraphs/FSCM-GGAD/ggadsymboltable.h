// $Header$

#ifndef __GgadSymbolTable_H__
#define __GgadSymbolTable_H__

#include <string>
#include <map>
#include <sstream>

#include <strutil.h>

#include "ggaddebug.h"
#include "ggadfunc.h"


typedef int GgadSymbolType;

/**
This class represents a symbol of the table, with it's name and type
@ingroup model
*/
class GgadSymbol {

    std::string name;
    GgadSymbolType type;

 public:
    GgadSymbol() : type(0) {
        // DM("GgadSymbol 1");
    }

    GgadSymbol( const GgadSymbol &symbol)
        : name(symbol.name), type(symbol.type)
    {
        // DM("GgadSymbol 2 " << name << ", " << type );
    }

    GgadSymbol( const std::string &_name )
        : name(_name), type(0)
    {
        // DM("GgadSymbol 3 " << _name );
    }

    GgadSymbol( const std::string &_name, const GgadSymbolType _type )
        : name(_name), type(_type)
    {
        // DM("GgadSymbol 4 " << name << ", " << type );
    }

    const std::string &getName() { return name; }

    const GgadSymbolType &getType() { return type; }

    void setType( GgadSymbolType _type ) { this->type = _type; }

    const std::string asString() {
        std::ostringstream o;
        o << name << "," << type;
        std::string s = o.str();
        return s;
    }

};



/**
 * exception generated when an operation expect to find a symbol and can't.
 */
class GgadExceptionSymbolNotFound {
    std::string symbolName;

public:
    GgadExceptionSymbolNotFound(const std::string &name) : symbolName(name) {}
    const std::string& getName() { return symbolName; }
};



/**
 * exception generated when an operation attempt to std::set the type of a symbol and it
 * had already been typed.
 * @ingroup exceptions
 */
class GgadExceptionSymbolAlreadyTyped {
    std::string symbolName;

public:
    GgadExceptionSymbolAlreadyTyped(const std::string &name) : symbolName(name) {}
    const std::string& getName() { return symbolName; }
};


/**
 * exception generated when an operation attempt to std::set the type of a symbol and it
 * had already been typed.
 * @ingroup exceptions
 */
class GgadExceptionDuplicateSymbol {
    std::string symbolName;

public:
    GgadExceptionDuplicateSymbol(const std::string &name) : symbolName(name) {}
    const std::string& getName() { return symbolName; }
};


/**
Symbol table class
@ingroup model
*/
class GgadSymbolTable
{
    typedef std::map<std::string, GgadSymbol> Symbols;
    Symbols symbols;

    typedef std::map<std::string, GgadFunc*> GgadFuncTable;
    static GgadFuncTable *ggadFuncTable;


public:


    GgadSymbolTable();
    ~GgadSymbolTable();

    void addSymbol(const std::string &name);
    void addSymbol(const std::string &name, const GgadSymbolType simbolType);
    bool isSymbol(const std::string &name);

    const GgadSymbolType getSymbolType(const std::string &name);
    void setSymbolType(const std::string &name, const GgadSymbolType simbolType );

    void printOn(std::ostream &s); // debugging
    std::string asString();

    /** Register builtin functions to be used. */
    static void RegisterFunctions();

    static void InitFunctionTable() {
        DM( "InitFunctionTable" );
        ggadFuncTable = new GgadFuncTable();
    }

    /** Register a funcion.
    @param name Name that the function will be registered by.
    @param f pointer to a GgadFunc object that implements the function.
    */
    static void addFunction( const std::string &name, GgadFunc *f ) {
        DM( "addFunction(" << name << ", " << f->name() << ")");
        if ( ggadFuncTable == NULL ) {
            // not initialized
            InitFunctionTable();
        }

        // test parameters
        if ( name.length() == 0 || f == NULL ) {
            // FIXME! throw exception
            DM( "Invalid parameters!" );
        }

        // append the function to the table
        (*ggadFuncTable)[ lowerCase(name) ] = f;
    }


    /** Returns a pointer to the function object of given name.
        @param functionName Name of the function.
    */
    static GgadFunc *getFunctionByName( const std::string &functionName ) {
        if ( ggadFuncTable == NULL ) {
            // not initialized
            return NULL; // FIXME! throw an exception?
        }

        // search the function
        GgadFuncTable::iterator i = ggadFuncTable->find( functionName );
        if ( i != ggadFuncTable->end() ) {
            return (*i).second->create();
        } else {
            return NULL;
        }
    }

};

#endif // __GgadSymbolTable_H__

