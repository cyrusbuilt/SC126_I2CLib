#include "sc126i2c.h"

void I2C_Start() {
	// Initialise I2C control port.
    outp(I2C_PORT, I2C_QUIES);
    
    // Set SDA low
    outp(I2C_PORT, I2C_DC_LH);

    // Set SCL low
    outp(I2C_PORT, I2C_DC_LL);
}

void I2C_Stop()
{
    // Set SCL high
    outp(I2C_PORT, I2C_DC_LH);

    // Set SDA high
    outp(I2C_PORT, I2C_DC_HH);
}

unsigned char I2C_Read(char ack_flag)
{
    unsigned char byte_read = 0;
    char count = 0;
    unsigned char temp_data = 0;

    // Set SDA high
    outp(I2C_PORT, I2C_DC_HL);

    // Get 8 bits for data
    for (count = 7; count >= 0; count--) {
        // Set SCL high
        outp(I2C_PORT, I2C_DC_HH);
        
        temp_data = inp(I2C_PORT) & I2C_SDA_RD;
        if (temp_data > 0) {
            byte_read += (1 << count);
        }

        // Set SCL low
        outp(I2C_PORT, I2C_DC_HL);
    }
    
    // Set SDA low
    outp(I2C_PORT, I2C_DC_LL);
    
    // check ack flag
    if (ack_flag == 0) {
        // Set SDA high
        outp(I2C_PORT, I2C_DC_HL);

        // Set SCL high
        outp(I2C_PORT, I2C_DC_HH);

        // Set SCL low
        outp(I2C_PORT, I2C_DC_HL);
    }
    else {
        // Set SCL high
        outp(I2C_PORT, I2C_DC_LH);

        // Set SCL low
        outp(I2C_PORT, I2C_DC_LL);
    }

    return byte_read;    
}

uint8_t I2C_Write(unsigned char data) {
    char count = 0;
    unsigned char temp_data = 0;

    // Get 8 bits for data
    for (count = 7; count >= 0; count--) {
        // Is the current bit set to high
        if ((data & (1 << count)) > 0) {
            // Set SDA high
            outp(I2C_PORT, I2C_DC_HL);

            // Set SCL high 
            outp(I2C_PORT, I2C_DC_HH);

            // Set SCL low
            outp(I2C_PORT, I2C_DC_HL);
        }
        else {
            // Set SDA low
            outp(I2C_PORT, I2C_DC_LL);

            // Set SCL high
            outp(I2C_PORT, I2C_DC_LH);

            // Set SCL low
            outp(I2C_PORT, I2C_DC_LL);
        }
    }

    // Check for acknowledgement
    // Set SDA high
    outp(I2C_PORT, I2C_DC_HL);

    // Set SCL high
    outp(I2C_PORT, I2C_DC_HH);

    temp_data = inp(I2C_PORT) & I2C_SDA_RD;

    // Set SCL low
    outp(I2C_PORT, I2C_DC_HL);

    if (temp_data == 1) {
        return ERR_NOACK;    
    }
    
	return ERR_NONE;
}
