################################################################################
#
# rtl8192cu
#
################################################################################

RTL8192CU_VERSION = 7329ea8b80948f361f9b4bccc7ae49fa13a6b66f
RTL8192CU_SITE = $(call github,pvaret,rtl8192cu-fixes,$(RTL8192CU_VERSION))
RTL8192CU_LICENSE = GPLv2
RTL8192CU_MODULE_MAKE_OPTS = \
	CONFIG_RTL8192CU=m \
	KVER=$(LINUX_VERSION_PROBED) \
	USER_EXTRA_CFLAGS=-DCONFIG_$(call qstrip,$(BR2_ENDIAN))_ENDIAN

$(eval $(kernel-module))
$(eval $(generic-package))
