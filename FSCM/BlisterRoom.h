/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

#ifndef __BlisterRoom_H
#define __BlisterRoom_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
//TODO: add distribution class declaration here if needed
// Ej: class Distribution ;

/** declarations **/
class BlisterRoom: public Atomic
{
public:
	BlisterRoom( const string &name = "BlisterRoom" ) ;	 // Default constructor
	~BlisterRoom();					// Destructor
	virtual string className() const
		{return "BlisterRoom";}

protected:
	Model &initFunction();	
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	// [(!) TODO: declare ports, distributions and other private varibles here]
	/***********      Example declarations   **********************************/
	// const Port &in;	// this is an input port named 'in'
	// Port &out ;   	// this is an output port named 'out'
	// Distribution *dist ;
	// Distribution &distribution()	{ return *dist; }
	/**************************************************************************/
	const Port &Blister;
	const Port &Busy4;
	Port &FinalPack;
	Port &Busy3;

	// [(!) declare common variables]
	// Lifetime programmed since the last state transition to the next planned internal transition.
	Time sigma;
	
	// Time elapsed since the last state transition until now
	Time elapsed;
	
	// Time remaining to complete the last programmed Lifetime
	Time timeLeft;	

	Time blisterRoom_time;

	bool blister;

	bool packStat;

	int press;

	bool blisterStat;
};	// class BlisterRoom


#endif   //__BlisterRoom_H 
