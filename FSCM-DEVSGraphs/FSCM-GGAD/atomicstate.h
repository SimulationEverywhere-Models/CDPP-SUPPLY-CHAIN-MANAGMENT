/*******************************************************************
*
*  DESCRIPTION: class AtomicState 
*
*  AUTHOR: Alejandro Troccoli
*
*  EMAIL: mailto://atroccol@dc.uba.ar
*
*  DATE: 06/11/2000
*
*******************************************************************/

#ifndef _ATOMICSTATE_H
#define _ATOMICSTATE_H

//#include "modelstate.h"
#include <iostream>

//class AtomicState : public ModelState {
class AtomicState {
public:

	enum State
	{
		active,
		passive
	} ;


	State st;

	AtomicState(){};
	virtual ~AtomicState(){};

	AtomicState& operator=(AtomicState& thisState); //Assignment
	void copyState(AtomicState *);
	int  getSize() const;

};

inline 
std::ostream& operator<<( std::ostream& o, const AtomicState::State& st) {
	o << (int) st;
	return o;
}

inline
std::istream& operator>>( std::istream& is, AtomicState::State& st) {
	int s;
	is >> s;
	st = AtomicState::State(s);
	return is;
}

#endif // _ATOMICSTATE_H
