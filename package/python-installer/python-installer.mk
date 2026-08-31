################################################################################
#
# python-installer
#
################################################################################

PYTHON_INSTALLER_VERSION = 1.0.0
PYTHON_INSTALLER_SOURCE = installer-$(PYTHON_INSTALLER_VERSION).tar.gz
PYTHON_INSTALLER_SITE = https://files.pythonhosted.org/packages/5f/ef/230b70e66db6ab01d5cbb93329688ed1f06b2b0618a74925e36384ff0fba
PYTHON_INSTALLER_LICENSE = MIT
PYTHON_INSTALLER_LICENSE_FILES = LICENSE
PYTHON_INSTALLER_SETUP_TYPE = flit-bootstrap
HOST_PYTHON_INSTALLER_DEPENDENCIES = host-python-flit-core
HOST_PYTHON_INSTALLER_ENV = PYTHONPATH="$(@D)/src"

$(eval $(host-python-package))
