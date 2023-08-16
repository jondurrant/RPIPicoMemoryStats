/*
 * main.cpp
 *
 * Test program to show heap monitoring
 *
 *  Created on: 15 Aug 2023
 *      Author: jondurrant
 */

#include "pico/stdlib.h"
#include <stdio.h>
#include <cstdlib>

#define BLOCK_SIZE 512

#define MMALLOC measureMalloc
#define MFREE measureFree

size_t measureMallocCount = 0;
size_t measureFreeCount     = 0;
size_t measureMallocBytes  = 0;
void *measureMalloc(size_t bytes){
	void * ptr = malloc(bytes);
	size_t *sizePtr=((size_t *) ptr)-1;
	measureMallocBytes += *sizePtr;
	measureMallocCount++;
	return ptr;
}

void measureFree(void * ptr){
	size_t *sizePtr=((size_t *) ptr)-1;
	measureFreeCount++;
	measureMallocBytes -= *sizePtr;
	free(ptr);
}

void printHeapStats(){
	printf("Heap: %u (%.2f KB). Malloc Calls: %u Free Calls: %u\n",
			measureMallocBytes,
			(float)measureMallocBytes/1024.0,
			measureMallocCount,
			measureFreeCount
			);
}







void allocBlock(int32_t *pBlock[],  uint start, uint end){
	for (uint i=start; i < end; i++){
		pBlock[i] = (int32_t *)MMALLOC(sizeof(int32_t));
		*pBlock[i] = 0x5555555;
	}
}


void freeBlock(int32_t **pBlock, uint start, uint end){
	for (uint i=start; i < end; i++){
			MFREE(pBlock[i]);
			pBlock[i] = NULL;
	}
}






int main(){
	int32_t *pA[BLOCK_SIZE];
	int32_t *pB[BLOCK_SIZE];
	int32_t *pC[BLOCK_SIZE];

	stdio_init_all();
	sleep_ms(2000);
	printf("GO\n");
	printHeapStats();

	allocBlock(pA,  0,  BLOCK_SIZE);
	printf("Block A: ");
	printHeapStats();
	allocBlock(pB, 0,  BLOCK_SIZE);
	printf("Block B: ");
	printHeapStats();
	allocBlock(pC,  0,  BLOCK_SIZE);
	printf("Block C: ");
	printHeapStats();

	for (uint i= 10; i < BLOCK_SIZE; i+=10){

		freeBlock(pA, i-10, i);
		freeBlock(pB, i-10, i);
		freeBlock(pC, i-10, i);
		printf("Free chunk: ");
		printHeapStats();

		allocBlock(pA, i-10, i);
		allocBlock(pB, i-10, i);
		allocBlock(pC, i-10, i);
		printf("Alloc Chunk: ");
		printHeapStats();

	}
	printHeapStats();


	printf("DONE\n");


		for (;;){
			sleep_ms(1000);
		}

}






