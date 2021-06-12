/* 
 * UVC Controller Firmware
 * (C) Dave White, PE - July 2020
 * 
 * Architecture: 32-bit ARM Cortex M7 STM32F746ZG 
 * Platform: ST Microelectronics Nucleo-F746ZG
 * OS: ARM Mbed OS v6.2
 *
 */

#include "mbed.h"
#include "mbed_version.h"
#include "MCP3221_N.h"
//#include "rtos.h"
#include <math.h>
#include "RANDINT.h"

#define FIRMWARE_VERSION "R20200801H"
#define SENSOR_GAIN 4.13f // mW/V 

DigitalOut led1(LED1); // green LED on board indicates successful exposure loop / irradiance sequence
// DigitalOut led2(LED2);
DigitalOut led3(LED3); // use RED on board LED to indicate a failed exposure loop / irradiance sequence

// Total dose config bits - "c" denotes the complement, since active low.
DigitalIn b0c(D0);
DigitalIn b1c(D1);
DigitalIn b2c(D2);
DigitalIn b3c(D3);

// start / stop button I/O - "c" denotes the complement, since active low.
DigitalIn startc(D6);
DigitalIn stopc(D7);



// control pins
DigitalOut coil(D4); // coil is the lamp relay coil = turns on the UVC lamps.
DigitalOut indicator(D5); // indicator is the RED 24V LED indicator that blinks when the lamps are on.
DigitalOut loopCounter(D8); // will toggle this to measure the time interval in exposure proc's while loop.

//Serial pc(USBTX, USBRX); // tx, rx
static BufferedSerial serial_port(USBTX, USBRX);

MCP3221_N adc(PB_9, PB_8, 5.0, 4); // MCP3221 adc(p9, p10, 5.0); //sda, scl, supplyVoltage, N # samples

// function that reports whether the START button is pressed (active low)
extern bool StartKeyPressed() {
    if (!startc) {
        return true;
    }
    else {
        return false;
    }
}

void exposure(DigitalOut *indicator, DigitalOut *coil, DigitalIn *stop, float *dose_target, int *batch_no) {
    // initialize the parameters
    float gain = SENSOR_GAIN ;
    int sample_count = 0;
    float dose_avg = 0.0;
    float dose_received = 0.0;
    float voltage_raw = 0.0;
    *indicator = 1;
    *coil = 1;
   	loopCounter = 0;
    int exposureControlFlag = 0;

    // print out the initial conditions
    // printf("%X,%d,%4.2f,%4.2f,%4.2f,%4.2f,%4.2f,%d\r\n", *batch_no,sample_count,voltage_raw,*dose_target,gain,dose_avg,dose_received,exposureControlFlag);

    while ( dose_received < *dose_target ) {
    	// toggle loop counter so you can measure the period of this sequence with a scope
    	loopCounter = !loopCounter;

		// delivers 1 sec of exposure
		ThisThread::sleep_for(995ms); // 1000ms - ADC acquision time
        *indicator = !*indicator;
        sample_count += 1;

	    // then takes the measurements
        voltage_raw = adc.read(); // units are volts
        dose_received += gain * voltage_raw ; // mW-sec / cm2
        dose_avg = dose_received / sample_count; // P = E / t = mW / cm2

        if (!*stop) {
            // print the final conditions to serial out
            printf("%X,%d,%4.2f,%4.2f,%4.2f,%4.2f,%4.2f,%d\r\n", *batch_no,sample_count,voltage_raw,*dose_target,gain,dose_avg,dose_received,exposureControlFlag);
            // print error message
            printf("Irradiance sequence manually aborted. \r\n");
            exposureControlFlag = 1;
            *indicator = 1;
            led3 = 1;
            break;
        }

    	if (sample_count > 300) {
            // print the final conditions to serial out
            printf("%X,%d,%4.2f,%4.2f,%4.2f,%4.2f,%4.2f,%d\r\n", *batch_no,sample_count,voltage_raw,*dose_target,gain,dose_avg,dose_received,exposureControlFlag);
            // print error message
    	    printf("Irradiance sequence timed out (300 sec) and aborted.\r\n");
    	    exposureControlFlag = 2;
    	    *indicator = 1;
    	    led3 = 1;
    	    break;
    	}

    	// sensor health checks
    	if (sample_count > 3 && ( (voltage_raw == 0) | (dose_avg > 5.0) )) {
    		if (voltage_raw == 0) {
                // print the final conditions to serial out
                printf("%X,%d,%4.2f,%4.2f,%4.2f,%4.2f,%4.2f,%d\r\n", *batch_no,sample_count,voltage_raw,*dose_target,gain,dose_avg,dose_received,exposureControlFlag);
    			printf("Sensor is not detecting any light. Inspect sensor and lamps. \r\n");
    			*indicator = 1;
    			led3 = 1;
    			exposureControlFlag = 3;
    		}
    		if (dose_avg > 5.0) {
    			// print the final conditions to serial out
                printf("%X,%d,%4.2f,%4.2f,%4.2f,%4.2f,%4.2f,%d\r\n", *batch_no,sample_count,voltage_raw,*dose_target,gain,dose_avg,dose_received,exposureControlFlag);
                // print error message
                printf("Sensor value is out of range (too high). Dose average = %f mW-sec/cm2 after %d samples. \r\n",dose_avg, sample_count);
    			*indicator = 1;
    			led3 = 1;
    			exposureControlFlag = 4;
    		}
    		break;
    	}

    }

    //deactivate light circuit and LED indicator
    //*indicator = 0;
    *coil = 0;

    if (exposureControlFlag == 0) {
    	*indicator = 0;
    	led1 = 1;

        // print the final conditions to serial out
        printf("%X,%d,%4.2f,%4.2f,%4.2f,%4.2f,%4.2f,%d\r\n", *batch_no,sample_count,voltage_raw,*dose_target,gain,dose_avg,dose_received,exposureControlFlag);
    
    }
}

int main()
{
    int b0, b1, b2, b3;
    float dose_target;
    int batch_no;

    // Set desired properties (9600-8-N-1).
    serial_port.set_baud(9600);
    serial_port.set_format(
        /* bits */ 8,
        /* parity */ BufferedSerial::None,
        /* stop bit */ 1
    );

    printf("Firmware version %s using MBED OS %d. Starting up... \r\n", FIRMWARE_VERSION, MBED_VERSION);
    ThisThread::sleep_for(1000ms);

    b0 = !b0c; // 2^0 bit
    b1 = !b1c; // 2^1 bit
    b2 = !b2c; // 2^2 bit
    b3 = !b3c;  // 10x or 100x setting

    // sets the total dose to be received by the test sample
    dose_target = pow(10.0, (b3 + 1)) * ( 4.0 * b2 + 2.0 * b1 + 1.0 * b0 + 1.0 ); // range 10-800 mW-sec/cm2 
    printf("Total dose setting: %f mW-sec/cm^2 \r\n", dose_target);

    ThisThread::sleep_for(1000ms);
    
    printf("UVC sensor gain (mW/V): %f \r\n", SENSOR_GAIN);

    ThisThread::sleep_for(1000ms);

    printf("Begin printing session output data...\r\n");
    ThisThread::sleep_for(1000ms);
    // print the header line of the data file
    printf("batch_no,t_sec,adc_volts,target_dose,scale_factor,dose_average,dose_total,exit_status\r\n");
                
    bool StartKeyPrimed = false;

    while(1) {

        ThisThread::sleep_for(25ms); // not a multiple of 50 or 60Hz (16ms or 20ms = not good for EMI!)

        if(StartKeyPressed()) {

            if(StartKeyPrimed) {
            	// clears all LED indicators
            	led1 = 0;
            	led3 = 0;
            	indicator = 0;

                batch_no = randIntGen();

                // starts the irradiance sequence
                exposure(&indicator, &coil, &stopc, &dose_target, &batch_no);

                // reset the primed flag
                StartKeyPrimed = false;

            }
            else {
                StartKeyPrimed = true;
            }
        }

    }
}
