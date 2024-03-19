################################################################################
#
# daemonize
#
################################################################################

DAEMONIZE_VERSION = 1.7.8
DAEMONIZE_SITE = $(call github,bmc,daemonize,release-$(DAEMONIZE_VERSION))
DAEMONIZE_LICENSE = BSD-3-Clause
DAEMONIZE_LICENSE_FILES = LICENSE.md

$(eval $(autotools-package))
