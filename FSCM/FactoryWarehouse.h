/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*
*********************************************************************/

#ifndef __FactoryWarehouse_H
#define __FactoryWarehouse_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
//TODO: add distribution class declaration here if needed
// Ej: class Distribution ;

/** declarations **/
class FactoryWarehouse: public Atomic
{
public:
	FactoryWarehouse( const string &name = "FactoryWarehouse" ) ;	 // Default constructor
	~FactoryWarehouse();					// Destructor
	virtual string className() const
		{return "FactoryWarehouse";}

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

	// [(!) declare common variables]
	// Lifetime programmed since the last state transition to the next planned internal transition.
	Time sigma;

	// Time elapsed since the last state transition until now
	Time elapsed;

	// Time remaining to complete the last programmed Lifetime
	Time timeLeft;

	//input materials from outside
		const Port &FacWar_in1;
		const Port &FacWar_in2;
		const Port &Send;
		Port &FacWar_out1;
		Port &FacWar_out2;

	    //Maximum number of finished products that can be stored in the warehouse
		const int finishedProductCapacity;
		//Maximum number of raw materials that can be stored in the warehouse
		const int rawMaterialCapacity;
	    //Current number of raw materials in the warehouse
		int currentRaw;
		//Current number of finished products in the warehouse
		int currentFinished;
	    //Number of materials requested from administrator
		int material;

		int rawTobesent;
		//Number of materials to be sent to administrator
		int finishedTobesent;
		//If administrator asked warehouse to send materials (true=yes, false=no)
		bool sendRaw;
		bool sendFinished;
		//Warehouse processing time
		Time FactoryWarehouseProcessingTime;



};	// class FactoryWarehouse


#endif   //__FactoryWarehouse_H
