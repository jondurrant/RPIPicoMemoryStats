/*
 * main.cpp
 *
 * Test program to show stack monitoring
 *
 *  Created on: 15 Aug 2023
 *      Author: jondurrant
 */

#include "pico/stdlib.h"
#include <stdio.h>

#include "StackMeter.h"


/***
 * Recurse function to test usage of Stack Memory
 * @param depth
 * @return
 */
int recurse(uint depth){
		int32_t a = 20;
		int32_t b = 27;
		int32_t c ;

		if (depth == 0){
				return (a+b);
		}

		c = a * b +  recurse(depth -1);

		StackMeter::getInstance()->sample();

		return c;
}


int main(){
		StackMeter meter;

		stdio_init_all();
		sleep_ms(2000);
		printf("GO\n");

		meter.sample();
		meter.print();

		recurse(1000);
		meter.print();

		recurse(50);
		meter.print();

		recurse(3000);
		meter.print();

		printf("DONE\n");


		for (;;){
			sleep_ms(1000);
		}

}






