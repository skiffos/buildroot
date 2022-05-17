################################################################################
#
# rtl8723ds
#
################################################################################

RTL8723DS_VERSION = 76146e85847beb2427b1d4958fa275822f2b04ab
RTL8723DS_SITE = $(call github,lwfinger,rtl8723ds,$(RTL8723DS_VERSION))

RTL8723DS_LICENSE = GPL-2.0
# RTL8723DS_LICENSE_FILES = COPYING

RTL8723DS_MODULE_MAKE_OPTS = \
	CONFIG_RTL8723DS=m \
	KVER=$(LINUX_VERSION_PROBED) \
	KSRC=$(LINUX_DIR)

$(eval $(kernel-module))
$(eval $(generic-package))
