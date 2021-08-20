from ctypes import *

ams_0015_D = 0x15
ams_1000_D = 0x10
# ams_0015_DB = 0x30
ams_0015_DB = 0x78

try:
    ams_read = CDLL("/home/pi/pressure/AMS5812-1000-D/C/ams.so")
#    if(pwm_error_code != 0):
#        print("Error in pwm_init with error code :" + string(pwm_error_code))
except:
    print("Error in AMS file opening")
data_1 = 0.0


while(1):

	data_1 = ams_read.read_pressure(ams_0015_DB)
#	data_2 = ams_read.read_pressure(ams_1000_D)
#	data_3 = ams_read.read_pressure(ams_0015_DB)
	print ( "pressure_0015db  =  " + str(data_1/1000.0))
