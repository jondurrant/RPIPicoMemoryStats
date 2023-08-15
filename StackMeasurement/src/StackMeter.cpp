/*
 * StackMeter.cpp
 *
 *  Created on: 15 Aug 2023
 *      Author: jondurrant
 */

#include "StackMeter.h"
#include "stdio.h"

#ifdef STACK_METER_ON
StackMeter *StackMeter::pSelf = NULL;
#endif

StackMeter::StackMeter() {
#ifdef STACK_METER_ON
		StackMeter::pSelf = this;
#endif
}

StackMeter::~StackMeter() {
	// NOP
}


/***
 * Sample current stack u sage
 */
void StackMeter::sample(){
#ifdef STACK_METER_ON
		uint32_t current = getCurrentStack();

		if (current > xMaxStack){
			xMaxStack = current;
		}
#endif
}

/***
 * Print out stack information
 */
void StackMeter::print(){
#ifdef STACK_METER_ON
		printf("Stack Max: %u bytes or %.2f KB\n", xMaxStack, (float)xMaxStack / 1024.0 );
#endif
}

/***
 * Return the maximum stack usage in bytes
 * @return
 */
uint32_t StackMeter::getMaxStack(){
#ifdef STACK_METER_ON
	return xMaxStack;
#else
	return 0;
#endif
}

/***
 * Return the current stack usage in bytes
 * @return
 */
uint32_t StackMeter::getCurrentStack(){
#ifdef STACK_METER_ON
	uint8_t a = 32;
	uint32_t current;

	//printf("Stack origin %u current %u\n", (uint32_t)&xMaxStack, (uint32_t)&a);
	current = (uint32_t)(&xMaxStack) - (uint32_t)(&a) ;
	return current;
#else
	return 0;
#endif
}


/***
 * Return the default instance of StackMeter
 * @return
 */
StackMeter *StackMeter::getInstance(){
#ifdef STACK_METER_ON
	return StackMeter::pSelf;
#else
	return NULL;
#endif
}
