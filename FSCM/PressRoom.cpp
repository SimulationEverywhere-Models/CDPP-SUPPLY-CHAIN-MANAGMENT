/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

/** include files **/
#include "PressRoom.h"           // base header
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator


/*******************************************************************
* Function Name: PressRoom
* Description: constructor
********************************************************************/
PressRoom::PressRoom( const string &name )
: Atomic( name ),
Press( addInputPort( "Press" ) ),
Busy3( addInputPort( "Busy3" ) ),
Blister( addOutputPort( "Blister" ) ),
Busy2( addOutputPort( "Busy2" ) ),
pressRoom_time(4,0,0,0)
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
Model &PressRoom::initFunction()
{
	press=false;
	blisterStat=false;
	powder=0;
	pressStat=false;

	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This method executes when an external event is received.
********************************************************************/
Model &PressRoom::externalFunction( const ExternalMessage &msg )
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
 	if(msg.port() == Press){
		if(msg.value() == 1){
			powder=msg.value();
			pressStat = true; // change to press
			holdIn(active, 0);  // change to press
		} else {
			// The powder room should never send any input other than 1.
			cout<<"The powder room should never send any input other than 1. "<<endl;
		}
	}

	if(msg.port() == Busy3){
		if(msg.value() == 1){
			blisterStat = true;
			holdIn(active, 0);
		}else if(msg.value() == 0){
			blisterStat = false;
			holdIn(active, 0);
		}else{
			 //Error input! Simulation should never get here;
			cout<<"Error: Busy3 port should never get a value other than zero or one."<<endl;
		}
	}
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: This method executes when the TA has expired, right after the outputFunction has finished.
* 			   The new state and TA should be set.
********************************************************************/
Model &PressRoom::internalFunction( const InternalMessage & )
{
	//TODO: implement the internal function here
	if(this->state() == active){
		if (pressStat && !press && (powder==1)){
			press = true;
			holdIn(active, pressRoom_time);  // change to press
		}else{
			passivate();
		}
	} else {
		//this will never happen
		if(this->state() == passive){
			cout << "Error: Factory press room internal function was called in passive state!" << endl;
		}
	}
	return *this;

}

/*******************************************************************
* Function Name: outputFunction
* Description: This method executes when the TA has expired. After this method the internalFunction is called.
*              Output values can be send through output ports
********************************************************************/
Model &PressRoom::outputFunction( const InternalMessage &msg )
{
	//TODO: implement the output function here
	// remember you can use sendOutput(time, outputPort, value) function.
	// sendOutput( msg.time(), out, 1) ;
	if(!blisterStat && press){
		press=false;
		pressStat=false;
		blisterStat = true;
		sendOutput( msg.time(), Blister, 1) ;
	}
	if(pressStat){				//inform the powderRoom to stop sending materials
		// send output 1 to Busy2;
		sendOutput( msg.time(), Busy2, 1) ;
	}
	if(!pressStat){			//inform the powderRoom to start sending materials
		// send output 0 to Busy2;
		sendOutput( msg.time(), Busy2, 0) ;
	}
	return *this;

}

PressRoom::~PressRoom()
{
	//TODO: add destruction code here. Free distribution memory, etc. 
}
