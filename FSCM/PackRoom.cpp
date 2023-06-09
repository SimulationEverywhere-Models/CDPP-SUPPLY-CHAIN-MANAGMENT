/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

/** include files **/
#include "PackRoom.h"           // base header
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator


/*******************************************************************
* Function Name: PackRoom
* Description: constructor
********************************************************************/
PackRoom::PackRoom( const string &name )
: Atomic( name ),
FinalPack( addInputPort( "FinalPack" ) ),
PMP_out( addOutputPort( "PMP_out" ) ),
Busy4( addOutputPort( "Busy4" ) ),
packRoom_time(8,0,0,0)
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
Model &PackRoom::initFunction()
{
	/*// [(!) Initialize common variables]
	this->elapsed = Time::Zero;
 	this->timeLeft = Time::Inf;
 	// this->sigma = Time::Inf; // stays in active state until an external event occurs;
 	this->sigma = Time::Zero; // force an internal transition in t=0;

 	// TODO: add init code here. (setting first state, etc)
 	
 	// set next transition
 	holdIn( active, this->sigma  ) ;*/
	pack=false;
	packStat=false;
	blister=0;

	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This method executes when an external event is received.
********************************************************************/
Model &PackRoom::externalFunction( const ExternalMessage &msg )
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
 	if(msg.port() == FinalPack){
		if(msg.value() == 1){
			blister=msg.value();
			packStat = true; // change to pack
			holdIn(active, 0);  // change to pack
		} else {
			// The blister room should never send any input other than 1.
			cout<<"The blister room should never send any input other than 1. "<<endl;
		}
	}
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: This method executes when the TA has expired, right after the outputFunction has finished.
* 			   The new state and TA should be set.
********************************************************************/
Model &PackRoom::internalFunction( const InternalMessage & )
{
	//TODO: implement the internal function here
	if(this->state() == active){
		if (packStat && !pack && (blister==1)){
			pack = true;
			holdIn(active, packRoom_time);  // change to pack
		}else{
			passivate();
		}
	} else {
		//this will never happen
		if(this->state() == passive){
			cout << "Error: Factory pack room internal function was called in passive state!" << endl;
		}
	}
	return *this;

}

/*******************************************************************
* Function Name: outputFunction
* Description: This method executes when the TA has expired. After this method the internalFunction is called.
*              Output values can be send through output ports
********************************************************************/
Model &PackRoom::outputFunction( const InternalMessage &msg )
{
	//TODO: implement the output function here
	// remember you can use sendOutput(time, outputPort, value) function.
	// sendOutput( msg.time(), out, 1) ;
	if(pack){
		pack=false;
		packStat=false;
		sendOutput( msg.time(), PMP_out, 1) ;
	}
	if(!packStat){			//inform the blisterRoom to start sending materials
		// send output 0 to Busy4;
		sendOutput( msg.time(), Busy4, 0) ;
	}
	if(packStat){			//inform the blisterRoom to start sending materials
		// send output 0 to Busy4;
		sendOutput( msg.time(), Busy4, 1) ;
	}
	

	return *this;

}

PackRoom::~PackRoom()
{
	//TODO: add destruction code here. Free distribution memory, etc. 
}
