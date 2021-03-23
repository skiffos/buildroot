################################################################################
#
# nerdctl
#
################################################################################

NERDCTL_VERSION = 1.4.4
NERDCTL_SITE = $(call github,containerd,containerd,v$(NERDCTL_VERSION))
NERDCTL_LICENSE = Apache-2.0
NERDCTL_LICENSE_FILES = LICENSE

NERDCTL_GOMOD = github.com/containerd/nerdctl
NERDCTL_LDFLAGS = \
	-X $(NERDCTL_GOMOD)/pkg/version.Version=$(NERDCTL_VERSION)

$(eval $(golang-package))
