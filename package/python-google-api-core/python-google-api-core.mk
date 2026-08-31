################################################################################
#
# python-google-api-core
#
################################################################################

PYTHON_GOOGLE_API_CORE_VERSION = 2.30.3
PYTHON_GOOGLE_API_CORE_SOURCE = google_api_core-$(PYTHON_GOOGLE_API_CORE_VERSION).tar.gz
PYTHON_GOOGLE_API_CORE_SITE = https://files.pythonhosted.org/packages/16/ce/502a57fb0ec752026d24df1280b162294b22a0afb98a326084f9a979138b
PYTHON_GOOGLE_API_CORE_SETUP_TYPE = setuptools
PYTHON_GOOGLE_API_CORE_LICENSE = Apache-2.0
PYTHON_GOOGLE_API_CORE_LICENSE_FILES = LICENSE

$(eval $(python-package))
