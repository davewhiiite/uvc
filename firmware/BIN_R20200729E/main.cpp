#include "mbed.h"
#include "MCP3221_navg.h"
//#include "rtos.h"
#include <math.h>

DigitalOut led1(LED1);
DigitalOut led2(LED2);

// Scale factor config bits
DigitalIn b0c(D0);
DigitalIn b1c(D1);
DigitalIn b2c(D2);
DigitalIn b3c(D3);

// start / stop button I/O
DigitalIn startc(D6);
DigitalIn stopc(D7);

int batch_no = 1;

// control pins
DigitalOut ctrl(D4);
DigitalOut active(D5);

//Serial pc(USBTX, USBRX); // tx, rx
static BufferedSerial serial_port(USBTX, USBRX);

MCP3221_navg adc(PB_9, PB_8, 5.0, 4); // MCP3221 adc(p9, p10, 5.0); //sda, scl, supplyVoltage, N # samples

// function that reports whether the START button is pressed (active low)
extern bool StartKeyPressed() {
    if (!startc) {
        return true;
    }
    else {
        return false;
    }
}

void exposure(DigitalOut *active, DigitalOut *coil, DigitalIn *stop, float *qrad, float *sensor_gain, int *batch_no) {
    // initialize the parameters
    float dose = *qrad;
    float gain = *sensor_gain;
    int sample_count = 0;
    float dose_avg = 0.0;
//    float dose_interval = 0.0;
    float dose_received = 0.0;
    float voltage_raw = 0.0;
    *active = 1;
    *coil = 1;

    // print out the initial conditions
    printf("batch_no,t_sec,adc_volts,target_dose,scale_factor,dose_average,dose_total\r\n");
    printf("%d,%d,%4.2f,%4.2f,%4.2f,%4.2f,%4.2f\r\n", *batch_no,sample_count,voltage_raw,dose,gain,dose_avg,dose_received);

    while ( dose_received < dose ) {
	   // delivers 1 sec of exposure
	   ThisThread::sleep_for(1000ms);
        *active = !*active;
        sample_count += 1;

	    // then takes the measurements
        voltage_raw = adc.read(); // units are volts
        // dose_interval = gain * voltage_raw ; // mW / cm2 x 1 sec
        dose_received += gain * voltage_raw ; // mW-sec / cm2
        dose_avg = dose_received / sample_count; // P = E / t = mW / cm2

        if (!*stop) {
            printf("Irradiance sequence aborted. \r\n");
            break;
        }

    	if (sample_count > 300) {
    	    printf("Irradiance sequence timed out (300 sec) and aborted.\r\n");
    	    break;
    	}

    }

    //deactivate light circuit and LED indicator
    *active = 0;
    *coil = 0;

    // print the final conditions to serial out
    printf("%d,%d,%4.2f,%4.2f,%4.2f,%4.2f,%4.2f\r\n", *batch_no,sample_count,voltage_raw,dose,gain,dose_avg,dose_received);

    //increment the batch number
    *batch_no += 1;
}

int main()
{
    int b0, b1, b2, b3;
    float qrad, sensor_gain;

    // Set desired properties (9600-8-N-1).
    serial_port.set_baud(9600);
    serial_port.set_format(
        /* bits */ 8,
        /* parity */ BufferedSerial::None,
        /* stop bit */ 1
    );

    printf("UVC controller firmware version R20200729E. Starting up... \r\n");
    ThisThread::sleep_for(1000ms);
    b0 = !b0c; // 2^0 bit
    b1 = !b1c; // 2^1 bit
    b2 = !b2c; // 2^2 bit
    b3 = !b3c;  // 10x or 100x setting

    // sets the total dose to be received by the test sample
    qrad = pow(10.0, (b3 + 1)) * ( 4.0 * b2 + 2.0 * b1 + 1.0 * b0 + 1.0 ); // range 10-800 mW-sec/cm2 
    printf("Total dose setting: %f mW-sec/cm^2 \r\n", qrad);

    ThisThread::sleep_for(1000ms);
    sensor_gain = 4.13; // mW/V
    printf("UVC sensor gain (mW/V): %f \r\n", sensor_gain);

    ThisThread::sleep_for(1000ms);

    bool StartKeyPrimed = false;


    while(1) {

        ThisThread::sleep_for(25ms); // not a multiple of 50 or 60Hz (16ms or 20ms = not good for EMI!)

        if(StartKeyPressed()) {

            if(StartKeyPrimed) {

                // starts the irradiance sequence
                exposure(&active, &ctrl, &stopc, &qrad, &sensor_gain, &batch_no);

                // reset the primed flag
                StartKeyPrimed = false;

            }
            else {
                StartKeyPrimed = true;
            }
        }

    }
}
