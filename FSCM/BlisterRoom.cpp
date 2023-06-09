/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

/** include files **/
#include "BlisterRoom.h"           // base header
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator


/*******************************************************************
* Function Name: BlisterRoom
* Description: constructor
********************************************************************/
BlisterRoom::BlisterRoom( const string &name )
: Atomic( name ),
Blister( addInputPort( "Blister" ) ),
Busy4( addInputPort( "Busy4" ) ),
FinalPack( addOutputPort( "FinalPack" ) ),
Busy3( addOutputPort( "Busy3" ) ),
blisterRoom_time(6,0,0,0)
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
Model &BlisterRoom::initFunction()
{
	/*// [(!) Initialize common variables]
	this->elapsed = Time::Zero;
 	this->timeLeft = Time::Inf;
 	// this->sigma = Time::Inf; // stays in active state until an external event occurs;
 	this->sigma = Time::Zero; // force an internal transition in t=0;

 	// TODO: add init code here. (setting first state, etc)
 	
 	// set next transition
 	holdIn( active, this->sigma  ) ;*/
	blister=false;
	packStat=false;
	blisterStat=false;
	press=0;

	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This method executes when an external event is received.
********************************************************************/
Model &BlisterRoom::externalFunction( const ExternalMessage &msg )
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
 	if(msg.port() == Blister){
		if(msg.value() == 1){
			press=msg.value();
			blisterStat = true; // change to blister
			holdIn(active, 0);  // change to blister
		} else {
			// The press room should never send any input other than 1.
			cout<<"The press room should never send any input other than 1. "<<endl;
		}
	}

	if(msg.port() == Busy4){
		if(msg.value() == 1){
			packStat = true;
			holdIn(active, 0);
		}else if(msg.value() == 0){
			packStat = false;
			holdIn(active, 0);
		}else{
			 //Error input! Simulation should never get here;
			cout<<"Error: Busy4 port should never get a value other than zero or one."<<endl;
		}
	}
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: This method executes when the TA has expired, right after the outputFunction has finished.
* 			   The new state and TA should be set.
********************************************************************/
Model &BlisterRoom::internalFunction( const InternalMessage & )
{
	//TODO: implement the internal function here
	if(this->state() == active){
		if (blisterStat && !blister && (press==1)){
			blister = true;
			holdIn(active, blisterRoom_time);  // change to blister
		}else{
			passivate();
		}
	} else {
		//this will never happen
		if(this->state() == passive){
			cout << "Error: Factory blister room internal function was called in passive state!" << endl;
		}
	}
	return *this;

}

/*******************************************************************
* Function Name: outputFunction
* Description: This method executes when the TA has expired. After this method the internalFunction is called.
*              Output values can be send through output ports
********************************************************************/
Model &BlisterRoom::outputFunction( const InternalMessage &msg )
{
	//TODO: implement the output function here
	// remember you can use sendOutput(time, outputPort, value) function.
	// sendOutput( msg.time(), out, 1) ;
	if(!packStat && blister){
		blister=false;
		blisterStat=false;
		sendOutput( msg.time(), FinalPack, 1) ;
		packStat = true;
	}
	if(blisterStat){				//inform the pressRoom to stop sending materials
		// send output 1 to Busy3;
		sendOutput( msg.time(), Busy3, 1) ;
	}
	if(!blisterStat){			//inform the pressRoom to start sending materials
		// send output 0 to Busy3;
		sendOutput( msg.time(), Busy3, 0) ;
	}

	return *this;

}

BlisterRoom::~BlisterRoom()
{
	//TODO: add destruction code here. Free distribution memory, etc. 
}
