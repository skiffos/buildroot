################################################################################
#
# genuinetools-img
#
################################################################################

GENUINETOOLS_IMG_VERSION = 0.5.11
GENUINETOOLS_IMG_SITE = $(call github,genuinetools,img,v$(GENUINETOOLS_IMG_VERSION))

GENUINETOOLS_IMG_LICENSE = MIT
GENUINETOOLS_IMG_LICENSE_FILES = LICENSE

GENUINETOOLS_IMG_DEPENDENCIES = host-pkgconf
GENUINETOOLS_IMG_GOMOD = github.com/genuinetools/img

GENUINETOOLS_IMG_TAGS = cgo noembed
GENUINETOOLS_IMG_LDFLAGS = \
	-X $(GENUINETOOLS_IMG_GOMOD)/version.VERSION="$(GENUINETOOLS_IMG_VERSION)"

HOST_GENUINETOOLS_IMG_TAGS = $(GENUINETOOLS_IMG_TAGS)
HOST_GENUINETOOLS_IMG_LDFLAGS = $(GENUINETOOLS_IMG_LDFLAGS)

HOST_GENUINETOOLS_IMG_BIN_NAME = genuinetools-img
HOST_GENUINETOOLS_IMG_INSTALL_BINS = $(HOST_GENUINETOOLS_IMG_BIN_NAME)

$(eval $(golang-package))
$(eval $(host-golang-package))
