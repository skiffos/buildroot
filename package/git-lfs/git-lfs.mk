################################################################################
#
# host-git-lfs
#
################################################################################

HOST_GIT_LFS_VERSION = v2.9.2
HOST_GIT_LFS_SITE = https://github.com/git-lfs/git-lfs/archive
HOST_GIT_LFS_SOURCE = $(HOST_GIT_LFS_VERSION).tar.gz
HOST_GIT_LFS_LICENSE = MIT, Apache2.0, BSD-2-Clause, BSD-3-Clause, ISC
HOST_GIT_LFS_LICENSE_FILES = \
	LICENSE.md \
	vendor/golang.org/x/sys/LICENSE \
	vendor/golang.org/x/net/LICENSE \
	vendor/golang.org/x/sync/LICENSE \
	vendor/golang.org/x/text/LICENSE \
	vendor/github.com/inconshreveable/mousetrap/LICENSE \
	vendor/github.com/stretchr/testify/LICENSE \
	vendor/github.com/spf13/pflag/LICENSE \
	vendor/github.com/spf13/cobra/LICENSE.txt \
	vendor/github.com/git-lfs/wildmatch/LICENSE.md \
	vendor/github.com/git-lfs/go-ntlm/ntlm/md4/LICENSE \
	vendor/github.com/git-lfs/go-netrc/LICENSE \
	vendor/github.com/git-lfs/gitobj/LICENSE.md \
	vendor/github.com/davecgh/go-spew/LICENSE \
	vendor/github.com/rubyist/tracerx/LICENSE \
	vendor/github.com/pkg/errors/LICENSE \
	vendor/github.com/alexbrainman/sspi/LICENSE \
	vendor/github.com/olekukonko/ts/LICENCE \
	vendor/github.com/ssgelm/cookiejarparser/LICENSE.md \
	vendor/github.com/mattn/go-isatty/LICENSE \
	vendor/github.com/xeipuuv/gojsonpointer/LICENSE-APACHE-2.0.txt \
	vendor/github.com/xeipuuv/gojsonreference/LICENSE-APACHE-2.0.txt \
	vendor/github.com/xeipuuv/gojsonschema/LICENSE-APACHE-2.0.txt \
	vendor/github.com/pmezard/go-difflib/LICENSE

HOST_GIT_LFS_BIN_NAME = git-lfs
HOST_GIT_LFS_INSTALL_BINS = $(HOST_GIT_LFS_BIN_NAME)

$(eval $(host-golang-package))
