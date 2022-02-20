################################################################################
#
# rtklib
#
################################################################################

RTKLIB_VERSION = 620fa2873ce9182ab3ceab223170a3a2b7c3d651
RTKLIB_SITE = $(call github,rtklibexplorer,RTKLIB,$(RTKLIB_VERSION))
RTKLIB_LICENSE = BSD-2-Clause
RTKLIB_LICENSE_FILES = license.txt

RTKLIB_APPS = \
	$(if $(BR2_PACKAGE_RTKLIB_CONVBIN),convbin) \
	$(if $(BR2_PACKAGE_RTKLIB_POS2KML),pos2kml) \
	$(if $(BR2_PACKAGE_RTKLIB_RNX2RTKP),rnx2rtkp) \
	$(if $(BR2_PACKAGE_RTKLIB_RTKRCV),rtkrcv) \
	$(if $(BR2_PACKAGE_RTKLIB_STR2STR),str2str)

define RTKLIB_BUILD_CMDS
	find $(@D) -name '*.a' | xargs rm -f
	# TODO: Requires fortran compiler. Build conditional on RNX2RTKP.
	# $(TARGET_MAKE_ENV) $(MAKE) -C $(@D)/lib/iers/gcc \
	#  	CC="$(TARGET_CC)" \
	#  	F77="$(TARGET_FC)"
	$(foreach app,$(RTKLIB_APPS),\
		$(TARGET_MAKE_ENV) $(MAKE) -C $(@D)/app/consapp/$(app)/gcc \
			CC="$(TARGET_CC)"
	)
endef

define RTKLIB_INSTALL_TARGET_CMDS
	$(foreach app,$(RTKLIB_APPS), \
		$(INSTALL) -m 0755 $(@D)/app/consapp/$(app)/gcc/$(app) \
			$(TARGET_DIR)/usr/bin/$(app)
	)
endef

$(eval $(generic-package))
