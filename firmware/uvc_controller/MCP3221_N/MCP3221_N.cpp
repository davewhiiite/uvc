
#include "MCP3221_N.h"

//Create instance
MCP3221_N::MCP3221_N(PinName sda, PinName scl, float supplyVoltage, uint8_t N) : i2c(sda, scl), _supplyVoltage(supplyVoltage), _numSamples(N)
{
}

//destroy instance
MCP3221_N::~MCP3221_N()
{
}

float MCP3221_N::read()
{

//You cannot write to an MCP3221, it has no writable registers.
//MCP3221 also requires an ACKnowledge between each byte sent, before it will send the next byte. So we need to be a bit manual with how we talk to it.
//It also needs an (NOT) ACKnowledge after the second byte or it will keep sending bytes (continuous sampling)
//
//From the datasheet.
//
//I2C.START
//Send 8 bit device/ part address to open conversation.   (See .h file for part explanation)
//read a byte (with ACK)
//read a byte (with NAK)
//I2C.STOP

    uint32_t avg_sample =0x00;
    uint16_t adc_sample[8]={0,0,0,0,0,0,0,0};
    uint8_t index=0x00;
    
    /* Get the N ADC samples */
    for (index=0x00; index<_numSamples; index++)
    {
        /* ADC start conv */    
        i2c.start();
        int acknowledged = i2c.write(MCP3221_CONVERSE); //send a byte to start the conversation. It should be acknowledged.
        _data[0] = i2c.read(1);  //read a byte. acknowledge when we have it.
        _data[1] = i2c.read(0);  //read the second byte. (n)acknowledge when we have it to stop the flow.
        i2c.stop();
        /* Wait end of conversion */
        
        //convert to 12 bit.
        uint16_t _12_bit_var; // 2 bytes
        char _4_bit_MSnibble = _data[0]; // 1 byte, example 0000 1000
        char _8_bit_LSByte = _data[1];   // 1 byte, example 1111 0000

        _12_bit_var = ((0x0F & _4_bit_MSnibble) << 8) | _8_bit_LSByte;   //example 100011110000
 
        /* Store ADC samples*/
        adc_sample[index] = _12_bit_var;
    }
    
    
    /* Add the N ADC samples */
    for (index=0; index<_numSamples; index++)
    {
        avg_sample += adc_sample[index];
    }

    /* Compute the average of N ADC samples */
    avg_sample /= _numSamples;

    /* convert avg_sample to raw voltage, return voltage as float */
    return  (_supplyVoltage/4096) * avg_sample;
}

