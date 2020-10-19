################################################################################
#
# Chromium
#
################################################################################

CHROMIUM_VERSION = 88.0.4296.2
CHROMIUM_SITE = $(call github,chromium,chromium,$(CHROMIUM_VERSION))
CHROMIUM_LICENSE = BSD-Style
CHROMIUM_LICENSE_FILES = LICENSE
CHROMIUM_DEPENDENCIES = atk at-spi2-core at-spi2-atk alsa-lib cairo ffmpeg \
			flac fontconfig freetype harfbuzz host-clang host-ninja host-nodejs \
			host-pkgconf host-python icu jpeg libdrm libglib2 libkrb5 libnss libpng libxml2 libxslt \
			minizip opus ncurses pango snappy webp xlib_libXcomposite xlib_libXScrnSaver \
			xlib_libXcursor xlib_libXrandr zlib compiler-rt

CHROMIUM_TOOLCHAIN_CONFIG_PATH = $(shell pwd)/package/chromium/toolchain

CHROMIUM_OPTS = \
	custom_toolchain=\"//build/toolchain/linux/unbundle:default\" \
	host_toolchain=\"//build/toolchain/linux/unbundle:host\" \
	v8_snapshot_toolchain=\"//build/toolchain/linux/unbundle:host\" \
	is_clang=true \
	clang_use_chrome_plugins=false \
	treat_warnings_as_errors=false \
	use_gnome_keyring=false \
	linux_use_bundled_binutils=false \
	use_sysroot=false \
	target_cpu=\"$(BR2_PACKAGE_CHROMIUM_TARGET_ARCH)\" \
	enable_nacl=false \
	enable_swiftshader=false \
	enable_linux_installer=false \
	is_official_build=true \
	use_custom_libcxx=false \
	clang_use_default_sample_profile=false \
	is_cfi=false \
	pkg_config=\"PKG_CONFIG_PATH="$(STAGING_DIR)/usr/lib/pkgconfig:$(STAGING_DIR)/usr/share/pkgconfig" $(HOST_DIR)/usr/bin/pkgconf\" \
	use_system_libjpeg=true \
	use_system_libpng=true \
	use_system_harfbuzz=true \
	use_system_freetype=true

CHROMIUM_SYSTEM_LIBS = \
	ffmpeg \
	flac \
	fontconfig \
	freetype \
	harfbuzz-ng \
	libdrm \
	libjpeg \
	libpng \
	libvpx \
	libwebp \
	libxml \
	libxslt \
	openh264 \
	opus \
	re2 \
	snappy \
	yasm \
	zlib

ifeq ($(BR2_i386)$(BR2_x86_64),y)
CHROMIUM_SYSTEM_LIBS += yasm
CHROMIUM_DEPENDENCIES += host-yasm
endif

# tcmalloc has portability issues
CHROMIUM_OPTS += use_allocator=\"none\"

ifneq (BR2_PACKAGE_GTK2,y)
CHROMIUM_DEPENDENCIES += libgtk3
else
CHROMIUM_DEPENDENCIES += libgtk2
CHROMIUM_OPTS += gtk_version=2
endif

# V8 snapshots require compiling V8 with the same word size as the target
# architecture, which means the host needs to have that toolchain available.
#
# Additionally, v8_context_snapshot_generator requires host-ffmpeg, which
# doesn't currently build.
CHROMIUM_OPTS += v8_use_snapshot=false

ifeq ($(BR2_CCACHE),y)
CHROMIUM_OPTS += cc_wrapper=\"ccache\"
endif

# LLD is unsupported on i386, and fails during linking
ifeq ($(BR2_i386)$(BR2_mips)$(BR2_mipsel)$(BR2_mips64)$(BR2_mips64el),y)
CHROMIUM_OPTS += use_lld=false
# Disable gold as well, to force usage of our toolchain's ld.bfd
CHROMIUM_OPTS += use_gold=false
else
CHROMIUM_DEPENDENCIES += host-lld
CHROMIUM_OPTS += use_lld=true
endif

ifeq ($(BR2_ENABLE_DEBUG),y)
CHROMIUM_OPTS += is_debug=true
else
CHROMIUM_OPTS += is_debug=false
CHROMIUM_OPTS += blink_symbol_level=0
endif

ifeq ($(BR2_PACKAGE_CUPS),y)
CHROMIUM_DEPENDENCIES += cups
CHROMIUM_OPTS += use_cups=true
else
CHROMIUM_OPTS += use_cups=false
endif

ifeq ($(BR2_PACKAGE_CHROMIUM_PROPRIETARY_CODECS),y)
CHROMIUM_OPTS += proprietary_codecs=true ffmpeg_branding=\"Chrome\"
endif

ifeq ($(BR2_PACKAGE_PCIUTILS),y)
CHROMIUM_DEPENDENCIES += pciutils
CHROMIUM_OPTS += use_libpci=true
else
CHROMIUM_OPTS += use_libpci=false
endif

ifeq ($(BR2_PACKAGE_PULSEAUDIO),y)
CHROMIUM_DEPENDENCIES += pulseaudio
CHROMIUM_OPTS += use_pulseaudio=true
else
CHROMIUM_OPTS += use_pulseaudio=false
endif

#ifeq ($(BR2_TOOLCHAIN_EXTERNAL),y)
#CHROMIUM_TARGET_LDFLAGS += --gcc-toolchain=$(TOOLCHAIN_EXTERNAL_INSTALL_DIR)
#else
#CHROMIUM_TARGET_LDFLAGS += --gcc-toolchain=$(HOST_DIR)
#endif

# This is required for compatibility with host-icu, which is configured
# with --disable-renaming
#CHROMIUM_HOST_CXXFLAGS += -DU_DISABLE_RENAMING=1

#CHROMIUM_TARGET_CFLAGS += $(CHROMIUM_TARGET_LDFLAGS)
#CHROMIUM_TARGET_CXXFLAGS += $(CHROMIUM_TARGET_CFLAGS)

define CHROMIUM_CONFIGURE_CMDS
	# Allow building against system libraries in official builds
	( cd $(@D); \
		sed -i 's/OFFICIAL_BUILD/GOOGLE_CHROME_BUILD/' \
			tools/generate_shim_headers/generate_shim_headers.py \
	)

	mkdir -p $(@D)/third_party/node/linux/node-linux-x64/bin
	ln -sf $(HOST_DIR)/bin/node $(@D)/third_party/node/linux/node-linux-x64/bin/

	# Use python2 by default
	mkdir -p $(@D)/bin
	ln -sf $(HOST_DIR)/usr/bin/python2 $(@D)/bin/python

	( cd $(@D); \
		$(TARGET_MAKE_ENV) \
		build/linux/unbundle/replace_gn_files.py \
			--system-libraries $(CHROMIUM_SYSTEM_LIBS) \
	)

	( cd $(@D); \
		$(TARGET_MAKE_ENV) \
		BUILD_CC="clang" \
		BUILD_CXX="clang++" \
		BUILD_AR="$(HOSTAR)" \
		BUILD_NM="$(HOSTNM)" \
		BUILD_CFLAGS="$(HOST_CFLAGS)" \
		BUILD_CXXFLAGS="$(HOST_CXXFLAGS)" \
		BUILD_LDFLAGS="$(HOST_LDFLAGS)" \
		CC="clang" \
		CXX="clang++" \
		AR="ar" \
		NM="nm" \
		CFLAGS="$(TARGET_CFLAGS)" \
		CXXFLAGS="$(TARGET_CXXFLAGS)" \
		LDFLAGS="$(TARGET_LDFLAGS)" \
		gn gen out/Release --args="$(CHROMIUM_OPTS)" \
			--script-executable=$(HOST_DIR)/bin/python2 \
	)
endef

define CHROMIUM_BUILD_CMDS
	( cd $(@D); \
		$(TARGET_MAKE_ENV) \
		PATH=$(@D)/bin:$(BR_PATH) \
		ninja -j$(PARALLEL_JOBS) -C out/Release chrome chrome_sandbox chromedriver \
	)
endef

define CHROMIUM_INSTALL_TARGET_CMDS
	$(INSTALL) -D $(@D)/out/Release/chrome $(TARGET_DIR)/usr/lib/chromium/chromium
	$(INSTALL) -Dm4755 $(@D)/out/Release/chrome_sandbox \
		$(TARGET_DIR)/usr/lib/chromium/chrome-sandbox
	cp $(@D)/out/Release/{chrome_{100,200}_percent,resources}.pak \
		$(@D)/out/Release/chromedriver \
		$(TARGET_DIR)/usr/lib/chromium/
	$(INSTALL) -Dm644 -t $(TARGET_DIR)/usr/lib/chromium/locales \
		$(@D)/out/Release/locales/*.pak
endef

$(eval $(generic-package))
