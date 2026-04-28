################################################################################
#
# codex
#
################################################################################

CODEX_VERSION = 0670d8971a80e8890263380f4e7f04d529f55d72
CODEX_SITE = $(call github,openai,codex,$(CODEX_VERSION))
CODEX_LICENSE = Apache-2.0
CODEX_LICENSE_FILES = LICENSE
CODEX_DEPENDENCIES = host-pkgconf libcap openssl
CODEX_SUBDIR = codex-rs/cli
CODEX_CARGO_BUILD_OPTS = --package codex-cli --bin codex
CODEX_CARGO_INSTALL_OPTS = --bin codex

$(eval $(cargo-package))
