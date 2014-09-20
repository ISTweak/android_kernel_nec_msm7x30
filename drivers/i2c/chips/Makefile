#
# Makefile for miscellaneous I2C chip drivers.
#
# Do not add new drivers to this directory! It is DEPRECATED.
#
# Device drivers are better grouped according to the functionality they
# implement rather than to the bus they are connected to. In particular:
# * Hardware monitoring chip drivers go to drivers/hwmon
# * RTC chip drivers go to drivers/rtc
# * I/O expander drivers go to drivers/gpio
#
#/***********************************************************************/
#/* Modified by                                                         */
#/* (C) NEC CASIO Mobile Communications, Ltd. 2011                      */
#/***********************************************************************/






obj-$(CONFIG_SENSORS_MT9T013)	+= mt9t013.o


obj-y	+= sensors_common.o
obj-y	+= gp2ap012a00f.o
obj-y	+= akm8977.o
obj-y	+= akm8977_table.o
obj-y	+= akm8977_queue.o













obj-y		+= i2c_fsa928x.o







ifeq ($(CONFIG_I2C_DEBUG_CHIP),y)
EXTRA_CFLAGS += -DDEBUG
endif

