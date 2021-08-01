ifndef COMMON_MK_INCLUDED
COMMON_MK_INCLUDED := 1

# コンマ、スペース文字
# see: https://www.gnu.org/software/make/manual/html_node/Syntax-of-Functions.html#Syntax-of-Functions
ch_comma :=,
ch_empty :=
ch_space :=$(ch_empty) $(ch_empty)

# Makefile が存在するパス
makefile_root := $(dir $(realpath $(firstword $(MAKEFILE_LIST))))

# make を実行している Host OS 名
ifeq ($(OS),Windows_NT)
	host_os_name := windows
else
	uname_s := $(shell uname -s)
	ifeq ($(uname_s),Darwin)
		host_os_name := darwin
	else ifeq ($(uname_s),Linux)
		host_os_name := linux
	else
		host_os_name := $(uname_s)
	endif
endif

# 実行ファイルの拡張子
ifeq ($(host_os_name),windows)
	ext_exe := .exe
else
	ext_exe :=
endif

# Windows 実行時は Powershell 7 (pwsh.exe) を使う
# see: https://stackoverflow.com/questions/61754413/set-powershell-core-as-a-default-gnu-make-shell-on-windows-linux
ifeq ($(host_os_name),windows)
	SHELL := pwsh.exe
	.SHELLFLAGS := -Command
endif

# 基本的なコマンド
ifeq ($(host_os_name),windows)
	cmd_cmake   := cmake
else
	cmd_cmake   := cmake
endif

endif #COMMON_MK_INCLUDED
