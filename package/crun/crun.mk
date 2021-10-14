################################################################################
#
# crun
#
################################################################################

# TODO:
# - .version file needs to be created in advance
# - libocispec: needs separate package probably

CRUN_VERSION = 1.2
CRUN_SITE = $(call github,containers,crun,$(CRUN_VERSION))
CRUN_DEPENDENCIES = host-pkgconf yajl
CRUN_LICENSE = GPL-2.0+ (crun binary), LGPL-2.1+ (libcrun)
CRUN_LICENSE_FILES = COPYING COPYING.libcrun

CRUN_AUTORECONF = YES

ifeq ($(BR2_PACKAGE_LIBSECCOMP),y)
CRUN_DEPENDENCIES += libseccomp
else
CRUN_CONF_OPTS += --disable-seccomp
endif

$(eval $(autotools-package))
