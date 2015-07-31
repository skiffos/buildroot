################################################################################
# Linux Aufs extensions
#
# Patch the linux kernel with aufs extension
################################################################################

LINUX_EXTENSIONS += aufs-standalone

define AUFS_STANDALONE_PREPARE_KERNEL
	if test -d $(LINUX_DIR)/fs/aufs/; then \
		echo "Your kernel already supports AUFS. Not patching."; \
	else \
		$(APPLY_PATCHES) $(LINUX_DIR) $(AUFS_STANDALONE_SRCDIR) \
			$(AUFS_STANDALONE_MAJOR_VERSION)-kbuild.patch \
			$(AUFS_STANDALONE_MAJOR_VERSION)-base.patch \
			$(AUFS_STANDALONE_MAJOR_VERSION)-mmap.patch \
			$(AUFS_STANDALONE_MAJOR_VERSION)-standalone.patch ; \
	fi
	cp $(AUFS_STANDALONE_SRCDIR)/Documentation/ABI/testing/* $(LINUX_DIR)/Documentation/ABI/testing/
	cp -r $(AUFS_STANDALONE_SRCDIR)/Documentation/filesystems/aufs/ $(LINUX_DIR)/Documentation/filesystems/aufs/
	cp -r $(AUFS_STANDALONE_SRCDIR)/fs/aufs/ $(LINUX_DIR)/fs/
	cp $(AUFS_STANDALONE_SRCDIR)/include/uapi/linux/aufs_type.h $(LINUX_DIR)/include/uapi/linux/
endef
