#
# Amazon SimpleDB C bindings
#
# Created by Peter Macko
#
# Copyright 2009
#      The President and Fellows of Harvard College.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. Neither the name of the University nor the names of its contributors
#    may be used to endorse or promote products derived from this software
#    without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#

include mk/defs.mk


#
# Build output
#

BUILD_DIR := build


#
# Make-related flags
#

SHELL := /bin/bash
CC := gcc


#
# Libraries
#

# Curl

CURL_INCLUDE_FLAGS := $(shell curl-config --cflags)
CURL_LINKER_FLAGS := 
CURL_LIBRARIES := $(shell curl-config --libs)

# LibXML

XML_INCLUDE_FLAGS := $(shell xml2-config --cflags)
XML_LINKER_FLAGS := 
XML_LIBRARIES := $(shell xml2-config --libs)

# Combine the flags

LIB_INCLUDE_FLAGS := $(CURL_INCLUDE_FLAGS) $(XML_INCLUDE_FLAGS)
LIB_LINKER_FLAGS := -L/usr/lib $(CURL_LINKER_FLAGS) $(XML_LINKER_FLAGS)
LIB_LIBRARIES := $(CURL_LIBRARIES) $(XML_LIBRARIES) -lssl


#
# Create flags
#

DEBUG_FLAGS := -ggdb -D_DEBUG

INCLUDE_FLAGS := $(LIB_INCLUDE_FLAGS) -Iinclude
COMPILER_FLAGS := -O2

LINKER_FLAGS := $(LIB_LINKER_FLAGS)
LIBRARIES := $(LIB_LIBRARIES)
