
#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#define IO_ERROR_AMS -998
#define FILE_OPEN_ERROR_AMS -999
float Pmax = 1.5;
float Pmin = 0;
float Digout_max = 29491.0;
float Digout_min = 3277.0;
int read_pressure(int);


int read_pressure(int address)
{
	int file;
	char *bus = "/dev/i2c-1";
//	while(1){
	if((file = open(bus, O_RDWR)) < 0)
	{
		printf("Failed to open the bus. \n");
	//	exit(1);
		return FILE_OPEN_ERROR_AMS;
	}

	printf(" Adrress = %d" , address);
	switch(address)
	{
		case 0x15 : Pmax = 1.5;Pmin = 0;break;
		case 0x10 : Pmax = 100;Pmin = 0;break;
		case 0x30 : Pmax = 1.5;Pmin = -1.5;break;
	        case 0x78 : Pmax = 1.5;Pmin = 0;break;
                case 0x16 : Pmax = 1.5;Pmin = 0;break;
                case 0x17 : Pmax = 1.5;Pmin = 0;break;
                case 0x18 : Pmax = 1.5;Pmin = 0;break;
	//	default : return 11;break;
	}


	// Get I2C device, AMS5812 I2C address is 0x78(120)
	ioctl(file, I2C_SLAVE, address);

	// Read 4 bytes of data
	// pressure msb, pressure lsb, temp msb, temp lsb
	char data[4] = {0};
	if(read(file, data, 4) != 4)
	{
		printf("Error : Input/Output error \n");
		return IO_ERROR_AMS;
	}

		// Convert the data
		float Sensp = (Digout_max-Digout_min )/(Pmax - Pmin);
		float pressure = (data[0] * 256 + data[1]);
//		float temp = (data[2] * 256 + data[3]);

		pressure = ((pressure - Digout_min) / Sensp) + Pmin;
	//	float cTemp = ((temp - 3277.0) / ((26214.0) / 110.0)) - 25.0;
	//	float fTemp = (cTemp * 1.8 ) + 32;
		pressure = pressure * 70.307 * 1000;
		// Output data to screen
	//	printf("Pressure is : %.2f CmH2O\n", pressure);// *70.307);
	//	printf("Temperature in Celsius : %.2f C\n", cTemp);
	//	printf("Temperature in Fahrenheit : %.2f F\n", fTemp);

//		usleep(50000);
		return (pressure);

}
