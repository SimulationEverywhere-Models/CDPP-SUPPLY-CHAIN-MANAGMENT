/*******************************************************************
*
*  Auto Generated File
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  This registration file is used to describe the atomic models that can be used to compose coupled models.
*
*
*******************************************************************/

#include "modeladm.h"
#include "mainsimu.h"
#include "queue.h"      // class Queue
#include "generat.h"    // class Generator
#include "cpu.h"        // class CPU
#include "transduc.h"   // class Transducer
#include "trafico.h"    // class Trafico

// Our header files
#include "FactoryWarehouse.h"	// class FactoryWarehouse
#include "FactoryAdministrator.h"	// class FactoryAdministrator
#include "PowderRoom.h"	// class PowderRoom
#include "PressRoom.h"	// class PressRoom
#include "BlisterRoom.h"	// class BlisterRoom
#include "PackRoom.h"	// class PackRoom

void MainSimulator::registerNewAtomics()
{
	// Register Built-in models
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Queue>() , "Queue" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Generator>() , "Generator" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<CPU>() , "CPU" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Transducer>() , "Transducer" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Trafico>() , "Trafico" ) ;

	// Register custom models
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<FactoryWarehouse>() , "FactoryWarehouse" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<FactoryAdministrator>() , "FactoryAdministrator" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<PowderRoom>() , "PowderRoom" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<PressRoom>() , "PressRoom" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<BlisterRoom>() , "BlisterRoom" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<PackRoom>() , "PackRoom" ) ;
}
