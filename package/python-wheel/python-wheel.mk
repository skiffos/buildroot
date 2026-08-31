################################################################################
#
# python-wheel
#
################################################################################

PYTHON_WHEEL_VERSION = 0.47.0
PYTHON_WHEEL_SOURCE = wheel-$(PYTHON_WHEEL_VERSION).tar.gz
PYTHON_WHEEL_SITE = https://files.pythonhosted.org/packages/39/62/75f18a0f03b4219c456652c7780e4d749b929eb605c098ce3a5b6b6bc081
PYTHON_WHEEL_SETUP_TYPE = flit
PYTHON_WHEEL_LICENSE = MIT
PYTHON_WHEEL_LICENSE_FILES = LICENSE.txt
PYTHON_WHEEL_CPE_ID_VENDOR = wheel_project
PYTHON_WHEEL_CPE_ID_PRODUCT = wheel

$(eval $(host-python-package))
