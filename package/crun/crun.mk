################################################################################
#
# crun
#
################################################################################

CRUN_VERSION = 1.5
CRUN_SITE = https://github.com/containers/crun
CRUN_SITE_METHOD = git
CRUN_GIT_SUBMODULES = YES
CRUN_DEPENDENCIES = host-pkgconf yajl
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
	$(MAKE) -C $(@D) git-version.h
endef
CRUN_PRE_BUILD_HOOKS += CRUN_GEN_VERSION

$(eval $(autotools-package))
