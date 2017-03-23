/*
 * main.cpp
 *
 *  Created on: Mar 17, 2017
 *      Author: root
 */

#include "mbed.h"

//#include "mbed_memory_status.h"

/* defining the symbols for the heap size and start in order to enable the load and store of the value
in the bigger SRAM (SRAM1) of the STM32L476RG*/
//#define HEAP_START 0x2000C000
//#define HEAP_SIZE 0xC000
//#define INITIAL_SP 0x10000188

static AnalogIn adcA2 (A2);
static AnalogIn adcA3 (A3);
static AnalogIn adcA4 (A4);
static AnalogIn adcA5 (A5);
static uint16_t samples[8000];
//uint16_t* samples = new uint16_t[8000];
DigitalOut led (D13);
static Thread thrA2, thrA3, thrA4, thrA5;

enum ADC_freq_t {
	FREQ_350KHZ = 0,
	FREQ_100KHZ = 7,
	FREQ_50KHZ = 16,
	FREQ_20KHZ = 47
};

void read_A2() {
	adcA2.fast_read(samples,2000, FREQ_350KHZ);
}

void read_A3() {
	adcA3.fast_read(samples+2000,2000, FREQ_100KHZ);
}

void read_A4() {
	adcA4.fast_read(samples+4000,2000, FREQ_50KHZ);
}

void read_A5() {
	adcA5.fast_read(samples+6000,2000, FREQ_20KHZ);
}


int main (int argc, char** argv){
led=0;
//	float *samples= (float*)malloc(16384*sizeof(float));
//	int dec, units;
//uint16_t *samples=(uint16_t*)malloc(16384*sizeof(uint16_t));

led=1;

thrA2.start(read_A2);
thrA3.start(read_A3);
thrA4.start(read_A4);
thrA5.start(read_A5);


thrA2.join();
thrA3.join();
thrA4.join();
thrA5.join();

//adc.fast_read(samples,8000);
//adcA0.fast_read(samples+4000,8000);

printf("\nchannel A2\n\n");

	for(int i = 0; i<8000; i++){
//		dec=(int)samples[i];
//		units=(int)((samples[i]-dec)*10000);
//		printf("%d,%04d\n",dec,units);
		if (i==2000)	printf("\nchannel A3\n\n");
		if (i==4000)	printf("\nchannel A4\n\n");
		if (i==6000)	printf("\nchannel A5\n\n");

		//samples[i]=((samples[i] << 4) & (uint16_t)0xFFF0) | ((samples[i] >> 8) & (uint16_t)0x000F);
		samples[i]=((samples[i] << 4) & (uint16_t)0xFFF0);
		//samples[i]=((samples[i] & (uint16_t)0xFFF0)>>4) & 0x0FFF;
		printf("%d\n",(int)(samples[i]*0.051));
		//printf("ciaociao\n");
	}
	return 0;
}

