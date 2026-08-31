################################################################################
#
# python-hiredis
#
################################################################################

PYTHON_HIREDIS_VERSION = 3.3.1
PYTHON_HIREDIS_SOURCE = hiredis-$(PYTHON_HIREDIS_VERSION).tar.gz
PYTHON_HIREDIS_SITE = https://files.pythonhosted.org/packages/97/d6/9bef6dc3052c168c93fbf7e6c0f2b12c45f0f741a2d30fd919096774343a
PYTHON_HIREDIS_SETUP_TYPE = setuptools
PYTHON_HIREDIS_LICENSE = MIT, BSD-3-Clause
PYTHON_HIREDIS_LICENSE_FILES = LICENSE vendor/hiredis/COPYING

$(eval $(python-package))
