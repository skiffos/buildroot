################################################################################
#
# python-filelock
#
################################################################################

PYTHON_FILELOCK_VERSION = 3.29.0
PYTHON_FILELOCK_SOURCE = filelock-$(PYTHON_FILELOCK_VERSION).tar.gz
PYTHON_FILELOCK_SITE = https://files.pythonhosted.org/packages/b5/fe/997687a931ab51049acce6fa1f23e8f01216374ea81374ddee763c493db5
PYTHON_FILELOCK_SETUP_TYPE = hatch
PYTHON_FILELOCK_LICENSE = MIT
PYTHON_FILELOCK_LICENSE_FILES = LICENSE
PYTHON_FILELOCK_DEPENDENCIES = host-python-hatch-vcs

$(eval $(python-package))
