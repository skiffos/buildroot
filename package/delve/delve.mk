################################################################################
#
# delve
#
################################################################################

DELVE_VERSION = 1.3.2
DELVE_SITE = $(call github,go-delve,delve,v$(DELVE_VERSION))

DELVE_LICENSE = MIT
DELVE_LICENSE_FILES = LICENSE

DELVE_DEPENDENCIES = host-pkgconf

DELVE_TAGS = cgo

DELVE_BUILD_TARGETS = github.com/go-delve/delve/cmd/dlv

DELVE_INSTALL_BINS = $(notdir $(DELVE_BUILD_TARGETS))

$(eval $(golang-package))
