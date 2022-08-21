################################################################################
#
# crun
#
################################################################################

CRUN_VERSION = 1.5
CRUN_SITE = $(call github,containers,crun,$(CRUN_VERSION))
CRUN_DEPENDENCIES = host-pkgconf libocispec yajl
CRUN_LICENSE = GPL-2.0+ (crun binary), LGPL-2.1+ (libcrun)
CRUN_LICENSE_FILES = COPYING COPYING.libcrun

CRUN_AUTORECONF = YES

ifeq ($(BR2_PACKAGE_LIBSECCOMP),y)
CRUN_DEPENDENCIES += libseccomp
else
CRUN_CONF_OPTS += --disable-seccomp
endif

CRUN_CONF_OPTS += --enable-embedded-yajl=no

define CRUN_GEN_VERSION
	echo "$(CRUN_VERSION)" > $(@D)/.version
endef
CRUN_PRE_BUILD_HOOKS += CRUN_GEN_VERSION

$(eval $(autotools-package))
