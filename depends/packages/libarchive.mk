package=libarchive
$(package)_version=3.7.2
$(package)_download_path=https://github.com/libarchive/libarchive/releases/download/v$($(package)_version)
$(package)_file_name=$(package)-$($(package)_version).tar.gz
$(package)_sha256_hash=df404eb7222cf30b4f8f93828677890a2986b66ff8bf39dac32a804e96ddf104
$(package)_config_opts=--disable-shared --enable-static --prefix=$(host_prefix) --host=$(HOST)
$(package)_config_opts+=--disable-bsdtar --disable-bsdcat --disable-bsdcpio --disable-bsdunzip --without-bz2lib --without-expat --without-iconv
$(package)_config_opts+=CFLAGS="$($(package)_cflags) -fPIC"
$(package)_conf_tool=./configure
$(package)_dependencies=zlib

define $(package)_set_vars
  $(package)_config_env=LD_LIBRARY_PATH="$(host_prefix)/lib" CPPFLAGS="-I$(host_prefix)/include" LDFLAGS="-L$(host_prefix)/lib"
  $(package)_config_env+=AR="$($(package)_ar)" RANLIB="$($(package)_ranlib)" CC="$($(package)_cc)"
  $(package)_config_opts += --disable-dependency-tracking --enable-option-checking
endef

define $(package)_config_cmds
  echo '=== config for $(package):' && \
  echo '$($(package)_config_env) $($(package)_conf_tool) $($(package)_config_opts)' && \
  echo '=== ' && \
  $($(package)_config_env) $($(package)_conf_tool) $($(package)_config_opts)
endef

define $(package)_build_cmds
  $(MAKE)
endef

define $(package)_stage_cmds
  echo 'Staging dir: $($(package)_staging_dir)$(host_prefix)/' && \
  $(MAKE) DESTDIR=$($(package)_staging_dir) install
endef

define $(package)_postprocess_cmds
  rm -rf share/man lib/*.la
endef
