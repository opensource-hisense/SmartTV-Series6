#
# Makefile for USB Core files and filesystem
#

# compatiblity with mstar
EXTRA_CFLAGS      += -Idrivers/mstar/usb

# compatiblity with mstar2
EXTRA_CFLAGS      += -Idrivers/mstar2/hal/$(CONFIG_MSTAR_CHIP_NAME)/usb

ccflags-$(CONFIG_USB_DEBUG) := -DDEBUG

usbcore-y := usb.o hub.o hcd.o urb.o message.o driver.o
usbcore-y += config.o file.o buffer.o sysfs.o endpoint.o
usbcore-y += devio.o notify.o generic.o quirks.o devices.o
usbcore-y += port.o bc-mstar.o mstar-lib.o

usbcore-$(CONFIG_PCI)		+= hcd-pci.o
usbcore-$(CONFIG_ACPI)		+= usb-acpi.o

obj-$(CONFIG_USB)		+= usbcore.o
