package=libcurl
$(package)_version=8.2.1
$(package)_dependencies=openssl
$(package)_download_path=https://curl.haxx.se/download
$(package)_file_name=curl-$($(package)_version).tar.xz
$(package)_sha256_hash=dd322f6bd0a20e6cebdfd388f69e98c3d183bed792cf4713c8a7ef498cba4894
$(package)_config_opts=--disable-shared --enable-static --prefix=$(host_prefix) --host=$(HOST) --with-openssl
$(package)_config_opts+=--disable-manual --disable-ntlm-wb --with-random=/dev/urandom
$(package)_config_opts+=--disable-curldebug --disable-libcurl-option --disable-ldap --disable-ldaps
$(package)_config_opts+=--disable-dependency-tracking --enable-option-checking
$(package)_config_opts+=CFLAGS="$($(package)_cflags) -fPIC"
$(package)_conf_tool=./configure

define $(package)_set_vars
  $(package)_config_env=AR="$($(package)_ar)" RANLIB="$($(package)_ranlib)" CC="$($(package)_cc)"
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
  echo 'Staging dir: $($(package)_staging_dir)$(host_prefix)' && \
  $(MAKE) DESTDIR=$($(package)_staging_dir) install
endef

define $(package)_postprocess_cmds
  rm -rf share/man lib/*.la
endef
