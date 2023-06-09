/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

#ifndef __FactoryAdministrator_H
#define __FactoryAdministrator_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
//TODO: add distribution class declaration here if needed
// Ej: class Distribution ;

/** declarations **/
class FactoryAdministrator: public Atomic
{
public:
	FactoryAdministrator( const string &name = "FactoryAdministrator" ) ;	 // Default constructor
	~FactoryAdministrator();					// Destructor
	virtual string className() const
		{return "FactoryAdministrator";}

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
	const Port &RawMaterials2;
	const Port &OrderInfo2;
	const Port &Busy1;
	const Port &PMP_out;
	const Port &FacWar_out1;
	const Port &FacWar_out2;
	Port &FacWar_in1;
	Port &FacWar_in2;
	Port &FinishedPro1;
	Port &Send;
	Port &PMP_in;
	// [(!) declare common variables]
	// Lifetime programmed since the last state transition to the next planned internal transition.
	Time sigma;
	
	// Time elapsed since the last state transition until now
	Time elapsed;
	
	// Time remaining to complete the last programmed Lifetime
	Time timeLeft;	


	int currentship;

	int current_finished;

	bool warehouseFinishRequest;

	int warehouseFinishQuantity;

	bool warehouseRaw;

	int current_raw;

	int rawRecieved;

	int raw;

	int warehouseFinish;

	Time factoryAdministratorProcessingTime;
	// Amount of raw material that the administrator receives from the warehouse and needs to send to the PMP  model
	int rawMaterial;
	// Boolean variable that tells the administrator to output to PMP model
	bool readyToPMP;
	// Boolean variable that tells the administrator to output to distributor
	bool readyToShip;
	// Amount of finished products that the administrator receives from the warehouse and needs to send to the distributor
	int finishedProduct;
	// Boolean variable that represents the state of the powder room in the PMP model
	bool powderStat;
	// Amount received from PMP to store into warehouse
	int storefinishedProduct;
	// Boolean variable that tells the administrator to send the finished products from PMP to warehouse.
	bool shipToWarehouse;
	// Boolean variable tells the administrator to ask the warehouse to send raw materials to be sent for manufacturing.
	bool requestRaw;
	// Amount of raw material that administrator requests from the warehouse.
	int warehouseRawQuantity;

	bool sent;

	int inProgress;


};	// class FactoryAdministrator


#endif   //__FactoryAdministrator_H 
