################################################################################
#
# nerdctl
#
################################################################################

NERDCTL_VERSION = 0.7.3
NERDCTL_SITE = $(call github,containerd,nerdctl,v$(NERDCTL_VERSION))
NERDCTL_LICENSE = Apache-2.0
NERDCTL_LICENSE_FILES = LICENSE

NERDCTL_GOMOD = github.com/containerd/nerdctl
NERDCTL_LDFLAGS = \
	-X $(NERDCTL_GOMOD)/pkg/version.Version=$(NERDCTL_VERSION)

# pkg-golang does not support main.go at the root of the project
define NERDCTL_BUILD_CMDS
	cd $(@D); \
	$(HOST_GO_TARGET_ENV) \
		$(NERDCTL_GO_ENV) \
		$(GO_BIN) build -v $(NERDCTL_BUILD_OPTS) \
		-o $(@D)/bin/nerdctl \
		$(NERDCTL_GOMOD)
endef

$(eval $(golang-package))
