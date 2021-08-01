include build/makefile/common.mk

#---------------------------------------------------------------------
# make パラメータ (実行時に変更可能なもの)
#---------------------------------------------------------------------

# 0: Release, 1: Debug
DEBUG ?= 0

# ビルドに使用する docker イメージ
#
# 指定したイメージを使ってビルドを行う。
# 未定義(空)のときは docker を使わずホスト環境で実行する。
DOCKER ?=

# ツールチェイン
ifeq ($(host_os_name),windows)
	ifneq ($(DOCKER),)
		TOOLCHAIN ?= x86_64-gcc
	else
		TOOLCHAIN ?= x64-msvc142
	endif
else
	TOOLCHAIN ?= x86_64-gcc
endif

#---------------------------------------------------------------------
# プロジェクトパラメータ
#---------------------------------------------------------------------

# プロジェクト名
PROJECT_NAME := errors_cpp11


#---------------------------------------------------------------------
# 変数定義
#---------------------------------------------------------------------

include build/makefile/docker_build.mk

# 出力先ディレクトリルート
out_root ?= $(patsubst %/,%,$(makefile_root))/_out/

# 出力サブディレクトリ名
out_subdir ?= $(if $(docker_build),$(docker_image_name),native)
ifneq ($(DEBUG),0)
	out_subdir := $(out_subdir)-debug
endif

# 出力先ディレクトリパス
out_dir := $(patsubst %/,%,$(out_root))/$(out_subdir)/

# テスト実行ファイル名
ifeq ($(docker_build),1)
	test_app_name := test_$(PROJECT_NAME)
else
	test_app_name := test_$(PROJECT_NAME)$(ext_exe)
endif

# cmake ソース/バイナリディレクトリ
ifeq ($(docker_build),1)
	source_dir := $(docker_workdir)
	binary_dir := $(patsubst %/,%,$(docker_workdir))/_out/$(out_subdir)/
else
	source_dir := $(makefile_root)
	binary_dir := $(out_dir)
endif

# cmake Debug/Release フラグ
ifeq ($(DEBUG),0)
	cmake_build_type := Release
else
	cmake_build_type := Debug
endif

# TOOLCHAIN 毎の設定
ifeq ($(TOOLCHAIN),x86_64-gcc)
	cmake_g_opt := -G "Unix Makefiles"
else ifeq ($(TOOLCHAIN),i686-gcc)
	cmake_g_opt := -G "Unix Makefiles" -DHOST64_M32=1
else ifeq ($(TOOLCHAIN),x86_64-clang)
	cmake_g_opt := -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=$(patsubst %/,%,$(source_dir))/build/cmake/toolchain-clang.cmake
else ifeq ($(TOOLCHAIN),i686-clang)
	cmake_g_opt := -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=$(patsubst %/,%,$(source_dir))/build/cmake/toolchain-clang.cmake -DHOST64_M32=1
else ifeq ($(TOOLCHAIN),x64-msvc140)
	cmake_g_opt := -G "Visual Studio 14 2015" -A x64
else ifeq ($(TOOLCHAIN),win32-msvc140)
	cmake_g_opt := -G "Visual Studio 14 2015" -A Win32
else ifeq ($(TOOLCHAIN),x64-msvc142)
	cmake_g_opt := -G "Visual Studio 16 2019" -A x64
else ifeq ($(TOOLCHAIN),win32-msvc142)
	cmake_g_opt := -G "Visual Studio 16 2019" -A Win32
else
	$(error TOOLCHAIN='$(TOOLCHAIN)' is not supported in this Makefile.)
endif

# Visual Studio generator の時はビルド dll, exe の出力先が違う
ifneq ($(findstring msvc,$(TOOLCHAIN)),)
	exe_out_prefix := $(cmake_build_type)/
endif


#---------------------------------------------------------------------
# ゴール
#---------------------------------------------------------------------

.DEFAULT_GOAL := all

.PHONY: all
all: build test

.PHONY: configure
configure:
	$(cmd_cmake) -E make_directory $(out_dir)
	$(cmd_docker_run) $(cmd_cmake) -S $(source_dir) -B $(binary_dir) -DCMAKE_BUILD_TYPE=$(cmake_build_type) $(cmake_g_opt)

.PHONY: build
build: configure
	$(cmd_docker_run) $(cmd_cmake) --build $(binary_dir) --config $(cmake_build_type)

.PHONY: test
test: build
	$(cmd_docker_run) $(cmd_cmake) --build $(binary_dir) --config $(cmake_build_type) --target test
	$(cmd_docker_run) $(patsubst %/,%,$(binary_dir))/$(exe_out_prefix)$(test_app_name)

.PHONY: clean
clean:
	-$(cmd_cmake) -E remove_directory $(out_root)

#---------------------------------------------------------------------
# ルール
#---------------------------------------------------------------------

# % で指定したサブディレクトリの CMakeLists.txt をビルドする
cmake_build_subdir/%: build
	$(cmd_docker_run) $(cmd_cmake) --build $(patsubst %/,%,$(binary_dir))/$* --config $(cmake_build_type)

