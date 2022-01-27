################################################################################
#
# buildah
#
################################################################################

BUILDAH_VERSION = 1.30.0
BUILDAH_SITE = $(call github,containers,buildah,v$(BUILDAH_VERSION))

BUILDAH_LICENSE = Apache-2.0
BUILDAH_LICENSE_FILES = LICENSE

BUILDAH_DEPENDENCIES = libgpgme

BUILDAH_CPE_ID_VENDOR = buildah_project
BUILDAH_CPE_ID_PRODUCT = buildah

BUILDAH_TAGS = \
	cgo \
	exclude_graphdriver_aufs \
	exclude_graphdriver_btrfs \
	exclude_graphdriver_devicemapper \
	exclude_graphdriver_zfs
BUILDAH_BUILD_TARGETS = cmd/buildah
BUILDAH_GOMOD = github.com/containers/buildah

BUILDAH_LDFLAGS = \
	-X $(BUILDAH_GOMOD)/cmd/buildah.GitCommit=v$(BUILDAH_VERSION) \
	-X $(BUILDAH_GOMOD)/define.Version=v$(BUILDAH_VERSION)

BUILDAH_INSTALL_BINS = $(notdir $(BUILDAH_BUILD_TARGETS))

define BUILDAH_INSTALL_CONFIG
	$(INSTALL) -D -m 644 $(@D)/contrib/buildroot/policy.json \
		$(TARGET_DIR)/etc/containers/policy.json
endef

BUILDAH_POST_INSTALL_TARGET_HOOKS += BUILDAH_INSTALL_CONFIG

HOST_BUILDAH_BUILD_TARGETS = $(BUILDAH_BUILD_TARGETS)
HOST_BUILDAH_TAGS = $(BUILDAH_TAGS)
HOST_BUILDAH_LDFLAGS = $(BUILDAH_LDFLAGS)
HOST_BUILDAH_INSTALL_BINS = $(BUILDAH_INSTALL_BINS)

$(eval $(golang-package))
$(eval $(host-golang-package))
