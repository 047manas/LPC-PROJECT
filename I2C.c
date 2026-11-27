#include "I2C.h"

void I2C_init(void)
{

    // default I2C0 is powered 

    // PCLK also we go default with 1MHz

    // configuring p0.27 and .28 for SDA0 and SCL0
    LPC_PINCON->PINSEL1 |= SDA0;
    LPC_PINCON->PINSEL1 |= SCL0;

    // went through sensor datasheet so best is go with 100kHz so for that 
    // divide with 10 in PCLK so we get it and 10 can be splited as 5 + 5 for CLL and CLH

    I2C0->I2SCLL = CLL;
    I2C0->I2SCLH = CLH;

    // enabling I2C interface 

    I2C0->I2CONSET = I2C0_EN;

}

uint8_t I2C_start(void)
{
    uint8_t start_status;
    // setting start bit 
    I2C0->I2CONSET = I2C0_Start_Bit;

    // clearing interupt flag to load start in the register and give latest status 
    I2C0->I2CONCLR = I2C0_INTR;

    // checking is the start bit set or not using the flag
    while((I2C0->I2CONSET & I2C0_INTR) == 0);

    // check is start condition transmitted

    if(I2C0->I2STAT == start_sent || I2C0->I2SAT == rep_start_sent)
    {

        start_status = 1;

    }
    else
    {

        start_status = 0;
        // clearing status flag as failer is going to retry again 
        I2C0->I2CONCLR = I2C0_INTR;

    }

    // clearing start
    I2C0->I2CONCLR = I2C0_Start_Bit;

    return start_status;

}

void I2C_stop(void)
{

    // Transmit STOP bit 4 in I2CONSET
    I2C0->I2CONSET = I2C0_Stop_Bit;

    I2C0->I2CONCLR = I2C0_INTR;

    // wait for stop condition to be transmitted
    while((I2C0->I2CONSET & I2C0_Stop_Bit) != 0);
    
    
}

uint8_t I2C_write(uint8_t input_data)
{

    I2C0->I2DAT = input_data;

    I2C0->I2CONCLR = I2C0_INTR;

    // wait for data condition to be transmitted
    while((I2C0->I2CONSET & I2C0_INTR) == 0);

    return I2C0->I2STAT; 
    
}
