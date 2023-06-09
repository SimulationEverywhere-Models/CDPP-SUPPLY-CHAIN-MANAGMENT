/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*
*********************************************************************/

/** include files **/
#include "FactoryWarehouse.h"           // base header
#include <iostream>
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator
#include "strutil.h"       // str2float( ... )


/*******************************************************************
* Function Name: FactoryWarehouse
* Description: constructor
********************************************************************/
FactoryWarehouse::FactoryWarehouse( const string &name )
: Atomic( name ),
FacWar_in1( addInputPort( "FacWar_in1" ) ),
FacWar_in2( addInputPort( "FacWar_in2" ) ),
Send( addInputPort( "Send" ) ),
FacWar_out1( addOutputPort( "FacWar_out1" ) ),
FacWar_out2( addOutputPort( "FacWar_out2" ) ),
finishedProductCapacity(20),
rawMaterialCapacity(80),
FactoryWarehouseProcessingTime(0,0,0,0)
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
Model &FactoryWarehouse::initFunction()
{
	// [(!) Initialize common variables]
	currentFinished=19;
	currentRaw=50;
	material=0;
	finishedTobesent=0;
	rawTobesent=0;
	sendFinished =false;
	sendRaw =false;
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This method executes when an external event is received.
********************************************************************/
Model &FactoryWarehouse::externalFunction( const ExternalMessage &msg )
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

 	//Receive raw materials from FacWar_in1 port
 		if(msg.port() == FacWar_in1){
 			if((msg.value() > 100)&&(msg.value() <= 180)){
 				int temp = msg.value() + currentRaw-100;
 				//Warehouse overflow; discard surplus
 				if(temp > rawMaterialCapacity){
 					  temp = rawMaterialCapacity;
 					  cout << "Warehouse raw material overflow!  Raw material inventory is set to 80. " << endl;
 				}

 				//Set inventory to the maximum raw material capacity
 				currentRaw=temp;

 		        if (this->state() == passive){
 		        	holdIn( active, FactoryWarehouseProcessingTime);
 		        }
 			}else{  //if the input is out of range
 				cout << "Warning: Warehouse must receive a valid integer of raw materials (>100 & <=180)!" << endl;
 			}

 		}

 		//Receive finished products from FacWar_in2 port
 		if(msg.port() == FacWar_in2){
 			if((msg.value() > 180)&&(msg.value() <= 200)){
 				//Add products manufactured to inventory
 				int temp = msg.value() + currentFinished-180;
 				//Warehouse overflow; discard surplus
 				if(temp > finishedProductCapacity){
 					  temp = finishedProductCapacity;
 					  cout << "Warehouse finished products overflow!  Finished products inventory is set to 20. " << endl;
 				}

 				//Set inventory to the maximum finished material capacity
 				currentFinished=temp;

 				//Set inventory to the maximum finished product capacity
 		        if (this->state() == passive){
 		        	holdIn( active, FactoryWarehouseProcessingTime);
 		 		}

 			}else{  //if the input is out of range
 				cout << "Warning: Warehouse must receive a valid integer of finished products (>180 & <=200)!" << endl;
 			}
 		}

 		if(msg.port() == Send){
 			if(msg.value()>=101 && msg.value()<=180){
 				rawTobesent=msg.value()-100;
 				if (currentRaw>=rawTobesent && this->state() == passive){
 					sendRaw=true;
 		        	holdIn(active, FactoryWarehouseProcessingTime);
 				}else{
 					//Display error message;
 					cout << "Error: Warehouse asked to send more raw units than there is in current storage!" << endl;
 				}
 			}else if (msg.value()>=181 && msg.value()<=200){
 				finishedTobesent=msg.value()-180;
 				if (currentFinished>=finishedTobesent && this->state() == passive){
 					sendFinished=true;
 					holdIn( active, FactoryWarehouseProcessingTime);
 				}else{
 					//Display error message;
 					cout << "Error: Warehouse asked to send more finished products units than there is in current storage!" << endl;
 				}
 			}else{
 				cout<<"Error: Send port received invalid input from Administrator!"<<endl;
 			}
 		}

	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: This method executes when the TA has expired, right after the outputFunction has finished.
* 			   The new state and TA should be set.
********************************************************************/
Model &FactoryWarehouse::internalFunction( const InternalMessage & )
{
	if(this->state() == active){
		passivate();
 	}else {
		//this will never happen
		if(this->state() == passive){
			cout << "Error: FactoryWarehouse internal function was called in passive state!" << endl;
		}
	}

 	return *this;
}

/*******************************************************************
* Function Name: outputFunction
* Description: This method executes when the TA has expired. After this method the internalFunction is called.
*              Output values can be send through output ports
********************************************************************/
Model &FactoryWarehouse::outputFunction( const InternalMessage &msg )
{
	//TODO: implement the output function here
	// remember you can use sendOutput(time, outputPort, value) function.
	// sendOutput( msg.time(), out, 1) ;
	if(sendRaw){
		currentRaw=currentRaw-rawTobesent;
		sendRaw=false;
		sendOutput(msg.time(), FacWar_out1,rawTobesent);
	}

	if(sendFinished){
		currentFinished=currentFinished-finishedTobesent;
		sendFinished=false;
		sendOutput(msg.time(), FacWar_out2,finishedTobesent);
	}

	return *this;

}

FactoryWarehouse::~FactoryWarehouse()
{
	//TODO: add destruction code here. Free distribution memory, etc.
}
