/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

#ifndef __PressRoom_H
#define __PressRoom_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
//TODO: add distribution class declaration here if needed
// Ej: class Distribution ;

/** declarations **/
class PressRoom: public Atomic
{
public:
	PressRoom( const string &name = "PressRoom" ) ;	 // Default constructor
	~PressRoom();					// Destructor
	virtual string className() const
		{return "PressRoom";}

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
	const Port &Press;
	const Port &Busy3;
	Port &Blister;
	Port &Busy2;

	// [(!) declare common variables]
	// Lifetime programmed since the last state transition to the next planned internal transition.
	Time sigma;
	
	// Time elapsed since the last state transition until now
	Time elapsed;
	
	// Time remaining to complete the last programmed Lifetime
	Time timeLeft;	// Boolean variable to check if powder has been created.
	bool press;
	// Boolean variable to check if the blister room is in use.
	bool blisterStat;
	// Press room processing time.
	Time pressRoom_time;
	int powder;
	bool pressStat;
};	// class PressRoom


#endif   //__PressRoom_H 
