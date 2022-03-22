################################################################################
#
# containerd
#
################################################################################

# 1.6.1 w/ compatibility with go1.18
CONTAINERD_VERSION = 977cb8bef06ea5c2e8c1a88e1308580ba95360d7
CONTAINERD_SITE = $(call github,containerd,containerd,$(CONTAINERD_VERSION))
CONTAINERD_LICENSE = Apache-2.0
CONTAINERD_LICENSE_FILES = LICENSE
CONTAINERD_CPE_ID_VENDOR = linuxfoundation
CONTAINERD_CPE_ID_PRODUCT = containerd

CONTAINERD_GOMOD = github.com/containerd/containerd

CONTAINERD_LDFLAGS = \
	-X $(CONTAINERD_GOMOD)/version.Version=$(CONTAINERD_VERSION)

CONTAINERD_BUILD_TARGETS = \
	cmd/containerd \
	cmd/containerd-shim \
	cmd/containerd-shim-runc-v1 \
	cmd/containerd-shim-runc-v2 \
	cmd/ctr

CONTAINERD_INSTALL_BINS = $(notdir $(CONTAINERD_BUILD_TARGETS))

ifeq ($(BR2_PACKAGE_LIBAPPARMOR),y)
CONTAINERD_DEPENDENCIES += libapparmor
CONTAINERD_TAGS += apparmor
endif

ifeq ($(BR2_PACKAGE_LIBSECCOMP),y)
CONTAINERD_DEPENDENCIES += libseccomp host-pkgconf
CONTAINERD_TAGS += seccomp
endif

ifeq ($(BR2_PACKAGE_CONTAINERD_DRIVER_BTRFS),y)
CONTAINERD_DEPENDENCIES += btrfs-progs
else
CONTAINERD_TAGS += no_btrfs
endif

$(eval $(golang-package))
