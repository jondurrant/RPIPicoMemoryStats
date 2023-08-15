/*
 * StackMeter.h
 *
 * Stack Telemetry
 *
 * Set global definition STACK_METER_ON for usage
 * If this definition is not turned on then the compiler should optimise out the code
 *
 *  Created on: 15 Aug 2023
 *      Author: jondurrant
 */

#ifndef STACKMEASUREMENT_SRC_STACKMETER_H_
#define STACKMEASUREMENT_SRC_STACKMETER_H_

#include <pico/stdlib.h>
#include <cstdint>

class StackMeter {
public:
	StackMeter();
	virtual ~StackMeter();

	/***
	 * Return the default instance of StackMeter
	 * @return
	 */
	static StackMeter *getInstance();

	/***
	 * Sample current stack u sage
	 */
	void sample();

	/***
	 * Print out stack information
	 */
	void print();

	/***
	 * Return the maximum stack usage in bytes
	 * @return
	 */
	uint32_t getMaxStack();

	/***
	 * Return the current stack usage in bytes
	 * @return
	 */
	uint32_t getCurrentStack();

private:
#ifdef 	STACK_METER_ON
	static StackMeter *pSelf;
	uint32_t xMaxStack = 0;
#endif // STACK_METER_ON
};

#endif /* STACKMEASUREMENT_SRC_STACKMETER_H_ */
