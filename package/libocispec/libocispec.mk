################################################################################
#
# libocispec
#
################################################################################

LIBOCISPEC_VERSION = cd78b375dd19464a5c7f118cd0f86082e7424255
LIBOCISPEC_SITE = https://github.com/containers/libocispec
LIBOCISPEC_SITE_METHOD = git
LIBOCISPEC_GIT_SUBMODULES = YES
LIBOCISPEC_DEPENDENCIES = host-pkgconf yajl
LIBOCISPEC_LICENSE = GPL-3.0
LIBOCISPEC_LICENSE_FILES = COPYING

LIBOCISPEC_AUTORECONF = YES

LIBOCISPEC_INSTALL_STAGING = YES
LIBOCISPEC_INSTALL_TARGET = NO

ifeq ($(BR2_PACKAGE_LIBSECCOMP),y)
LIBOCISPEC_DEPENDENCIES += libseccomp
else
LIBOCISPEC_CONF_OPTS += --disable-seccomp
endif

LIBOCISPEC_CONF_OPTS += --enable-embedded-yajl=no

# TODO: libocispec does not install properly.
define LIBOCISPEC_INSTALL_STAGING_CMDS
endef

$(eval $(autotools-package))
