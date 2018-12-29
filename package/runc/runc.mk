################################################################################
#
# runc
#
################################################################################

RUNC_VERSION = 6635b4f0c6af3810594d2770f662f34ddc15b40d
RUNC_SITE = $(call github,opencontainers,runc,$(RUNC_VERSION))
RUNC_LICENSE = Apache-2.0
RUNC_LICENSE_FILES = LICENSE

RUNC_WORKSPACE = Godeps/_workspace

RUNC_LDFLAGS = -X main.gitCommit=$(RUNC_VERSION)

RUNC_TAGS = cgo static_build

ifeq ($(BR2_PACKAGE_LIBSECCOMP),y)
RUNC_TAGS += seccomp
RUNC_DEPENDENCIES += libseccomp host-pkgconf
endif

$(eval $(golang-package))
