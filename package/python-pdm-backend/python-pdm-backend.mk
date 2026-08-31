################################################################################
#
# python-pdm-backend
#
################################################################################

PYTHON_PDM_BACKEND_VERSION = 2.4.8
PYTHON_PDM_BACKEND_SOURCE = pdm_backend-$(PYTHON_PDM_BACKEND_VERSION).tar.gz
PYTHON_PDM_BACKEND_SITE = https://files.pythonhosted.org/packages/7c/7e/6d441c8739a30820ec59517a88326789c201ae43a344b2ffb02fb2702d8e
PYTHON_PDM_BACKEND_SETUP_TYPE = pep517
PYTHON_PDM_BACKEND_LICENSE = MIT
PYTHON_PDM_BACKEND_LICENSE_FILES = LICENSE

$(eval $(host-python-package))
