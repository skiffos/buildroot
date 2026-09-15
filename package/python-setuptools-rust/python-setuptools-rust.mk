################################################################################
#
# python-setuptools-rust
#
################################################################################

PYTHON_SETUPTOOLS_RUST_VERSION = 1.12.1
PYTHON_SETUPTOOLS_RUST_SOURCE = setuptools_rust-$(PYTHON_SETUPTOOLS_RUST_VERSION).tar.gz
PYTHON_SETUPTOOLS_RUST_SITE = https://files.pythonhosted.org/packages/0c/11/736cfe4ec795dbce001ebdcef5cab03de1727041c805c3a45c1bda9f54a1
PYTHON_SETUPTOOLS_RUST_SETUP_TYPE = setuptools
PYTHON_SETUPTOOLS_RUST_LICENSE = MIT
PYTHON_SETUPTOOLS_RUST_LICENSE_FILES = LICENSE
HOST_PYTHON_SETUPTOOLS_RUST_DEPENDENCIES = \
	host-python-semantic-version \
	host-python-setuptools-scm \
	host-rustc

$(eval $(host-python-package))
