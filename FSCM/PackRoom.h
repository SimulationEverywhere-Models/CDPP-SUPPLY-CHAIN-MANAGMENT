/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

#ifndef __PackRoom_H
#define __PackRoom_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
//TODO: add distribution class declaration here if needed
// Ej: class Distribution ;

/** declarations **/
class PackRoom: public Atomic
{
public:
	PackRoom( const string &name = "PackRoom" ) ;	 // Default constructor
	~PackRoom();					// Destructor
	virtual string className() const
		{return "PackRoom";}

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
	const Port &FinalPack;
	Port &PMP_out;
	Port &Busy4;
	// [(!) declare common variables]
	// Lifetime programmed since the last state transition to the next planned internal transition.
	Time sigma;
	
	// Time elapsed since the last state transition until now
	Time elapsed;
	
	// Time remaining to complete the last programmed Lifetime
	Time timeLeft;	

	Time packRoom_time;

	bool pack;

	bool packStat;
	int blister;

};	// class PackRoom


#endif   //__PackRoom_H 
