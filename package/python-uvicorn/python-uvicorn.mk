################################################################################
#
# python-uvicorn
#
################################################################################

PYTHON_UVICORN_VERSION = 0.46.0
PYTHON_UVICORN_SOURCE = uvicorn-$(PYTHON_UVICORN_VERSION).tar.gz
PYTHON_UVICORN_SITE = https://files.pythonhosted.org/packages/1f/93/041fca8274050e40e6791f267d82e0e2e27dd165627bd640d3e0e378d877
PYTHON_UVICORN_SETUP_TYPE = hatch
PYTHON_UVICORN_LICENSE = BSD-3-Clause
PYTHON_UVICORN_LICENSE_FILES = LICENSE.md
PYTHON_UVICORN_CPE_ID_VENDOR = encode
PYTHON_UVICORN_CPE_ID_PRODUCT = uvicorn

$(eval $(python-package))
