################################################################################
#
# rtl8821au
#
################################################################################

RTL8821AU_VERSION = b65dcf4105641716d16f3a6c96507fdd9c1862b4
RTL8821AU_SITE = $(call github,aircrack-ng,rtl8812au,$(RTL8821AU_VERSION))
RTL8821AU_LICENSE = GPL-2.0
RTL8821AU_LICENSE_FILES = LICENSE

RTL8821AU_MODULE_MAKE_OPTS = \
	CONFIG_RTL8812A=y \
	CONFIG_RTL8821A=y \
	CONFIG_RTL8814A=n \
	CONFIG_RTL8812AU=m \
	KVER=$(LINUX_VERSION_PROBED) \
	USER_EXTRA_CFLAGS="-DCONFIG_$(call qstrip,$(BR2_ENDIAN))_ENDIAN \
		-Wno-error"

$(eval $(kernel-module))
$(eval $(generic-package))
