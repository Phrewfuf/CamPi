#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#include <wiringPi.h>
#include <wiringPiSPI.h>

// The A-D convertor won't run at more than 1MHz @ 3.3v

#define	SPI_SPEED	1000000
#define	SPI_READ	      0
#define	SPI_WRITE	      1


/*
 * rtcset
 * 	set the date and time of the pcf2123
 *********************************************************************************
 */

void rtcset (const int chan, const int value)
{
  uint8_t spiData [2] ;
  uint8_t chanBits, dataBits ;

  if (chan == 0)
    chanBits = 0x30 ;
  else
    chanBits = 0xB0 ;

  chanBits |= ((value >> 4) & 0x0F) ;
  dataBits  = ((value << 4) & 0xF0) ;

  spiData [0] = chanBits ;
  spiData [1] = dataBits ;

  wiringPiSPIDataRW (SPI_WRITE, spiData, 2) ;
}


/*
 * rtcget
 *	Get the time and date from the pcf2123
 *********************************************************************************
 */

int gertboardAnalogRead (const int chan)
{
  uint8_t spiData [2] ;

  uint8_t chanBits ;

  if (chan == 0)
    chanBits = 0b11010000 ;
  else
    chanBits = 0b11110000 ;

  spiData [0] = chanBits ;
  spiData [1] = 0 ;

  wiringPiSPIDataRW (SPI_READ, spiData, 2) ;

  return ((spiData [0] << 7) | (spiData [1] >> 1)) & 0x3FF ;
}


/*
 * gertboardSPISetup:
 *	Initialise the SPI bus, etc.
 *********************************************************************************
 */

int rtcSPISetup (void)
{
  if (wiringPiSPISetup (SPI_READ, SPI_SPEED) < 0)
    return -1 ;

  if (wiringPiSPISetup (SPI_WRITE, SPI_SPEED) < 0)
    return -1 ;

  return 0 ;
}
