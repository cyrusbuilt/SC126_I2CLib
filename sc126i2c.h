#ifndef _SC126_I2C_H
#define _SC126_I2C_H

#include <sys/compiler.h>
#include <conio.h>
#include <stdio.h>

/* Bus master boards supported are SC126 and SC137 */
#define SC137

#ifdef SC126 /* Not tested yet */
#define MESSAGE "Using SC126 I2C Master\n"
#define I2C_PORT    0x0C
#define I2C_SDA_RD  0x80
#define I2C_QUIES   0x8D

#define I2C_DC_LL   0x00
#define I2C_DC_LH   0x01
#define I2C_DC_HL   0x80
#define I2C_DC_HH   0x81
#endif

#ifdef SC137
#define MESSAGE "Using SC137 I2C Master\n"
#define I2C_PORT    0x28  /* 0x20 is the standard port for the SC137 */
#define I2C_SDA_RD  0x80
#define I2C_QUIES   0x81

#define I2C_DC_LL   0x00
#define I2C_DC_LH   0x01
#define I2C_DC_HL   0x80
#define I2C_DC_HH   0x81
#endif

#ifdef SC144
#define MESSAGE "Using SC144 I2C Master\n"
#define I2C_PORT    0x0C
#define I2C_SDA_RD  0x80
#define I2C_QUIES   0x81

#define I2C_DC_LL   0x00
#define I2C_DC_LH   0x01
#define I2C_DC_HL   0x80
#define I2C_DC_HH   0x81
#endif

/* Other boards */
/* TC74 */
#define TC74_ADDR (0x4D << 1)

/* PCF8574 */
#define PCF_IN      0x7F
#define PCF_OUT     0x7E

#define ACK         1
#define NACK        0

#define ERR_NONE    0
#define ERR_JAM     1
#define ERR_NOACK   2
#define ERR_TOUT    3

extern void __LIB__ I2C_Start();
extern void __LIB__ I2C_Stop();
extern unsigned char __LIB__ I2C_Read(char ack_flag);
extern uint8_t __LIB__ I2C_Write(unsigned char data);

#endif