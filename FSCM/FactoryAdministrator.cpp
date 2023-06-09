/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

/** include files **/
#include "FactoryAdministrator.h"           // base header
#include <iostream>
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator


/*******************************************************************
* Function Name: FactoryAdministrator
* Description: constructor
********************************************************************/
FactoryAdministrator::FactoryAdministrator( const string &name )
: Atomic( name ),
RawMaterials2( addInputPort( "RawMaterials2" ) ),
OrderInfo2( addInputPort( "OrderInfo2" ) ),
Busy1( addInputPort( "Busy1" ) ),
PMP_out( addInputPort( "PMP_out" ) ),
FacWar_out1( addInputPort( "FacWar_out1" ) ),
FacWar_out2( addInputPort( "FacWar_out2" ) ),
FacWar_in1( addOutputPort( "FacWar_in1" ) ),
FacWar_in2( addOutputPort( "FacWar_in2" ) ),
FinishedPro1( addOutputPort( "FinishedPro1" ) ),
Send( addOutputPort( "Send" ) ),
PMP_in( addOutputPort( "PMP_in" ) ),
factoryAdministratorProcessingTime(0,0,1,0)


// TODO: add ports here if needed (Remember to add them to the .h file also). Each in a new line.
// Ej:
// ,out(addOutputPort( "out" ))
// , in(addInputPort( "in" ))
{
	// TODO: add initialization code here. (reading parameters, initializing private vars, etc)
	// Code templates for reading parameters:
	// read string parameter:
	// 		stringVar = MainSimulator::Instance().getParameter( description(), "paramName" );
	// read int parameter:
	// 		intVar = str2Int( MainSimulator::Instance().getParameter( description(), "initial" ) );
	// read time parameter:
	//		timeVar = string time( MainSimulator::Instance().getParameter( description(), "preparation" ) ) ;
	// read distribution parameters:
	//		dist = Distribution::create( MainSimulator::Instance().getParameter( description(), "distribution" ) );
	//		MASSERT( dist ) ;
	//		for ( register int i = 0; i < dist->varCount(); i++ )
	//		{
	//			string parameter( MainSimulator::Instance().getParameter( description(), dist->getVar( i ) ) ) ;
	//			dist->setVar( i, str2Value( parameter ) ) ;
	//		}
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &FactoryAdministrator::initFunction()
{
	// [(!) Initialize common variables]
	this->elapsed = Time::Zero;
 	this->timeLeft = Time::Inf;
 	// this->sigma = Time::Inf; // stays in active state until an external event occurs;
 	this->sigma = Time::Zero; // force an internal transition in t=0;

 	// TODO: add init code here. (setting first state, etc)
 	
 	// set next transition
 	holdIn( active, this->sigma  ) ;
	currentship=0;
	current_finished=19;
	warehouseFinishRequest=false;
	warehouseFinishQuantity=0;
	warehouseRaw=false;
	current_raw=50;
	rawRecieved=0;
	warehouseFinish=false;
	shipToWarehouse=false;
	rawMaterial=0;
	readyToPMP=false;
	readyToShip=false;
	finishedProduct=0;
	powderStat=false;
	storefinishedProduct=0;
	shipToWarehouse=false;
	requestRaw=false;
	warehouseRawQuantity=0;
	sent=false;
	inProgress=0;

	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This method executes when an external event is received.
********************************************************************/
Model &FactoryAdministrator::externalFunction( const ExternalMessage &msg )
{
	//[(!) update common variables]	
	this->sigma = nextChange();	
	this->elapsed = msg.time()-lastChange();	
 	this->timeLeft = this->sigma - this->elapsed; 
	
	//TODO: implement the external function here.
 	// Remember you can use the msg object (mgs.port(), msg.value()) and you should set the next TA (you might use the holdIn method).
 	// EJ:
 	// if( msg.port() == in )
	//{
	//	// Do something
	//	holdIn( active, this->timeLeft );
	// }
 	if(msg.port() == OrderInfo2){
		if(msg.value() <=0){
			cout<<"Error: Factory Administrator asked to send negative or zero number of finished products. This is invalid option!"<<endl;
		}else if((msg.value() >= 1) && (msg.value() <= 20)){
			int temp=currentship+msg.value();
			if (temp>current_finished){
				cout<<"Error: Factory Administrator asked to send more available finished products!"<<endl;
			}else{
				currentship=temp;
				warehouseFinishRequest=true;
				warehouseFinishQuantity=currentship+180;
				current_finished=current_finished-currentship;
				holdIn( active, factoryAdministratorProcessingTime);
			}
		} else {
			// Since no order can be greater than 20 units, distributor should never request more.
			cout<<"Error: Factory Administrator asked to send more than 20 finished products at a time!"<<endl;
		}
	}

 	if (msg.port()== RawMaterials2){
 		if (msg.value()<=0){
			// Display Error Message because Supplier should not negative or zero input to factory
			cout<<"Error: Supplier should not negative or zero input to factory!"<<endl;
		}else if (msg.value()>(80-current_raw)){
			// Display Error Message because Supplier should not send more raw materials than capacity dictates
			cout<<"Error: Supplier should not send more raw materials than capacity dictates!"<<endl;
		}else if (msg.value()>=0 && msg.value()<=(80-current_raw)){
			int temp=msg.value();
			current_raw=current_raw+temp;
			rawRecieved=temp+100;
			warehouseRaw=true;
			holdIn( active, factoryAdministratorProcessingTime);
		}
	}

 	if (msg.port()== FacWar_out1){
		if (msg.value()!=4){
			// Display Error Message because powder room can never anything other than an input of 4 raw material units
			cout<<"Error: Factory warehouse should always send 4 raw materials at a time since pharmaceutical manufacturing plant cannot accept any other inputs other than 4 units!"<<endl;
		}else if(msg.value () ==4){
			rawMaterial=msg.value();
			readyToPMP=true;
			holdIn( active, factoryAdministratorProcessingTime);
		}
	}
	
 	if (msg.port()== FacWar_out2){
		if (msg.value()>20){
			// Display Error Message because total capacity for warehouse is only 20 so this should never happen
			cout<<"Error: Factory Warehouse should never be able to send more than 20 units of finished products!"<<endl;
		}else if(msg.value () <=20 && msg.value()>0){
			finishedProduct=msg.value();
			readyToShip=true;
			holdIn( active, factoryAdministratorProcessingTime);
		}else{
			// Simulation should never reach this
			cout<<"Error: Factory Warehouse should never send a negative output of finished products to administrator!"<<endl;
		}
	}

 	if(msg.port()==Busy1){
		if(msg.value()==1){
			powderStat=true;
			holdIn( active, factoryAdministratorProcessingTime);
		}else if (msg.value()==0){
			powderStat=false;
			sent=false;
			holdIn( active, factoryAdministratorProcessingTime);
		}else{
			cout<<"Error: Port Busy1 should never receive an input other than 0 or 1!"<<endl;
		}
	}

 	if(msg.port()==PMP_out){
		if (msg.value()!=1){
			// Display Error Message because PMP_out should only output a value of 1
			cout<<"Error: Pharmaceutical manufacturing plant should never send more than 1 unit of finished products!"<<endl;
		}else if(msg.value()==1){
			int temp=msg.value();

			if (current_finished>=20){
				//Simulation should never get here!
				cout<<"Warning: Overflow! Surplus units discarded."<<endl;
				temp=200;
				holdIn( active, factoryAdministratorProcessingTime);
			}
			inProgress=inProgress-1;
			storefinishedProduct=temp+180;
			current_finished=current_finished+1;
			shipToWarehouse=true;
			holdIn( active, factoryAdministratorProcessingTime);
		}
	}
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: This method executes when the TA has expired, right after the outputFunction has finished.
* 			   The new state and TA should be set.
********************************************************************/
Model &FactoryAdministrator::internalFunction( const InternalMessage & )
{
	//TODO: implement the internal function here

	if(this->state() == active){
		if((20-current_finished-inProgress)>0 && (20-current_finished-inProgress)<=20 && current_raw>=4 && !powderStat && !sent){
			requestRaw=true;
			warehouseRawQuantity=4+100;
			current_raw=current_raw-4;
		}else{
			passivate();
		}
	} else {
		//this will never happen
		if(this->state() == passive){
			cout << "Error: FactoryAdministrator internal function was called in passive state!" << endl;
		}
	}
	return *this;

}

/*******************************************************************
* Function Name: outputFunction
* Description: This method executes when the TA has expired. After this method the internalFunction is called.
*              Output values can be send through output ports
********************************************************************/
Model &FactoryAdministrator::outputFunction( const InternalMessage &msg )
{
	//TODO: implement the output function here
	// remember you can use sendOutput(time, outputPort, value) function.
	// sendOutput( msg.time(), out, 1) ;
	if(warehouseFinishRequest){
		//send output "warehouseFinishQuantity" to send
		warehouseFinishRequest=false;
		sendOutput(msg.time(), Send, warehouseFinishQuantity);
	}
	if(requestRaw){
		//send output "warehouseFinishQuantity" to send
		requestRaw=false;
		sent=true;
		sendOutput(msg.time(), Send, warehouseRawQuantity);
	}
	if(warehouseRaw){
		//send output "current_raw" to FacWar_in1;
		warehouseRaw=false;
	    sendOutput(msg.time(), FacWar_in1, rawRecieved);
	}
	if(readyToPMP && !powderStat && ((inProgress+current_finished)<20)){
		//send output "rawMaterial" to PMP_in;
		readyToPMP=false;
		powderStat=true;
		inProgress=inProgress+1;
	    sendOutput(msg.time(), PMP_in, rawMaterial);
	}
	if(readyToShip){
		//send output "finishedProduct" to FinishedPro1;
		readyToShip=false;
	    sendOutput(msg.time(), FinishedPro1, finishedProduct);
	}
	if(shipToWarehouse){
		//send output "storefinishedProduct" to FacWar_in2;
		shipToWarehouse=false;
	    sendOutput(msg.time(), FacWar_in2, storefinishedProduct);
	}
	return *this;
}

FactoryAdministrator::~FactoryAdministrator()
{
	//TODO: add destruction code here. Free distribution memory, etc. 
}
