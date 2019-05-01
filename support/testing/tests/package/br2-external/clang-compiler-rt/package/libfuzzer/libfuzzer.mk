################################################################################
#
# libfuzzer
#
################################################################################

LIBFUZZER_VERSION = 64e4d9aa19a8d33b61882154addbf8419d7416e1
LIBFUZZER_SITE = $(call github,google,fuzzer-test-suite,$(LIBFUZZER_VERSION))
LIBFUZZER_LICENSE = Apache-2.0
LIBFUZZER_LICENSE_FILES = LICENSE
LIBFUZZER_DEPENDENCIES = compiler-rt

define LIBFUZZER_BUILD_CMDS
	$(HOST_DIR)/bin/clang++ -mcpu=cortex-a53 --sysroot=$(STAGING_DIR) \
		-B $(HOST_DIR)/opt/ext-toolchain -fsanitize=address,fuzzer \
		$(@D)/tutorial/fuzz_me.cc \
		-o $(@D)/fuzz_me
endef

define LIBFUZZER_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 755 $(@D)/fuzz_me $(TARGET_DIR)/usr/bin/fuzz_me
endef

$(eval $(generic-package))
