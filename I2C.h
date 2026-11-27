#include<lpc17xx.h>
#include<stdint.h>

#define I2C0 LPC_I2C0
#define SDA0 (1 << 22)
#define SCL0 (1 << 24)
#define CLL 5
#define CLH 5
#define I2C0_EN (1 << 6)
#define I2C0_Start_Bit (1 << 5)
#define I2C0_INTR (1 << 3)
#define I2C0_Stop_Bit (1 << 4)




void I2C_init(void);
uint8_t I2C_start(void);
void I2C_stop(void);
