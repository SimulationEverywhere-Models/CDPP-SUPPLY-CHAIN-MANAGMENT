// $Id: ggaddebug.h,v 1.1 2001/04/15 15:43:19 Ale Exp $

#ifndef __GGADDEBUG_H__
#define __GGADDEBUG_H__

#include <iostream>

#define D(EX) if( GgadGetDebugLevel() > 0 ) { \
  std::cout << "GGAD DEBUG: " << __FILE__ << "(" << __LINE__ << ") " << #EX << ": " << EX << std::endl; }

#define DM(EX) if( GgadGetDebugLevel() > 0 ) { \
               std::cout << "GGAD DEBUG: " << __FILE__ << "(" << __LINE__ << ") " << EX << std::endl; }

#define DL(level,EX) if( GgadGetDebugLevel() >= level ) { \
               std::cout << "GGAD DEBUG: " << __FILE__ << "(" << __LINE__ << ") " << EX << std::endl; }

int GgadGetDebugLevel();
void GgadSetDebugLevel(int);

#endif // __GGADDEBUG_H__
