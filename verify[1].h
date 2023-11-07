// ============================================================================ //
//																				//
//							   VERIFY HEADER									//
//																				//
//						   Written by: Marc Nye									//
//						Last Modified: Dec 21, 2011								//
//																				//
// ============================================================================ //
#ifndef VERIFY_H
#define VERIFY_H


#include <cassert>


#ifndef NDEBUG
	#define	verify( expression )	assert( expression )
#else
	#define	verify( expression )	expression
#endif


#endif