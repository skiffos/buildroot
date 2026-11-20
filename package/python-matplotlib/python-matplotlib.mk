################################################################################
#
# python-matplotlib
#
################################################################################

PYTHON_MATPLOTLIB_VERSION = 3.10.9
PYTHON_MATPLOTLIB_SOURCE = matplotlib-$(PYTHON_MATPLOTLIB_VERSION).tar.gz
PYTHON_MATPLOTLIB_SITE = https://files.pythonhosted.org/packages/63/1b/4be5be87d43d327a0cf4de1a56e86f7f84c89312452406cf122efe2839e6
PYTHON_MATPLOTLIB_LICENSE = Python-2.0
PYTHON_MATPLOTLIB_LICENSE_FILES = LICENSE/LICENSE
PYTHON_MATPLOTLIB_DEPENDENCIES = \
	freetype \
	host-pkgconf \
	host-python-certifi \
	host-python-numpy \
	host-python-setuptools-scm \
	libpng \
	python-cycler \
	python-pybind \
	qhull
PYTHON_MATPLOTLIB_CONF_OPTS = \
	-Dmacosx=false \
	-Dsystem-freetype=true \
	-Dsystem-qhull=true
PYTHON_MATPLOTLIB_CONF_ENV += \
	_PYTHON_SYSCONFIGDATA_NAME=$(PKG_PYTHON_SYSCONFIGDATA_NAME) \
	PYTHONPATH=$(PYTHON3_PATH)

ifeq ($(BR2_PACKAGE_PYTHON_MATPLOTLIB_QT),y)
PYTHON_MATPLOTLIB_DEPENDENCIES += python-pyqt5
endif

$(eval $(meson-package))
