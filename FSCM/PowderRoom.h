/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

#ifndef __PowderRoom_H
#define __PowderRoom_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
//TODO: add distribution class declaration here if needed
// Ej: class Distribution ;

/** declarations **/
class PowderRoom: public Atomic
{
public:
	PowderRoom( const string &name = "PowderRoom" ) ;	 // Default constructor
	~PowderRoom();					// Destructor
	virtual string className() const
		{return "PowderRoom";}

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
	const Port &PMP_in;
	const Port &Busy2;
	Port &Press;
	Port &Busy1;

	// [(!) declare common variables]
	// Lifetime programmed since the last state transition to the next planned internal transition.
	Time sigma;
	
	// Time elapsed since the last state transition until now
	Time elapsed;
	
	// Time remaining to complete the last programmed Lifetime
	Time timeLeft;	
	// Boolean variable to check if powder has been created.
	bool powder;
	// Boolean variable to check if the press room is in use.
	bool pressStat;
	// Powder room processing time.
	Time powderRoom_time;

	bool powderStat;
	int	raw;
};	// class PowderRoom


#endif   //__PowderRoom_H
