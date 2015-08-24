################################################################################
#
# crew
#
################################################################################

CREW_VERSION = 0.4.0
CREW_SITE = $(call github,paralin,crew,v$(CREW_VERSION))
CREW_DEPENDENCIES = docker-engine perl
CREW_LICENSE_FILES = LICENSE

define CREW_INSTALL_TARGET_CMDS
	mkdir -p $(TARGET_DIR)/var/lib/crew/
	cp -r $(@D)/plugins/ $(TARGET_DIR)/var/lib/crew/
	$(INSTALL) -m 0755 $(@D)/crew $(TARGET_DIR)/usr/bin/crew
endef

define CREW_USERS
	crew -1 crew -1 * /home/crew /bin/bash docker Crew system user
endef

$(eval $(generic-package))
