// -*- mode: C++ -*-
//
// Copyright (c) 2007, 2008, 2009, 2010, 2011, 2015, 2017 The University of Utah
// All rights reserved.
//
// This file is part of `csmith', a random generator of C programs.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//   * Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistributions in binary form must reproduce the above copyright
//     notice, this list of conditions and the following disclaimer in the
//     documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

//
// This file was derived from a random program generator written by Bryan
// Turner.  The attributions in that file was:
//
// Random Program Generator
// Bryan Turner (bryan.turner@pobox.com)
// July, 2005
//

// ---------------------------------------
// Platform-Specific code to get a unique seed value (usually from the tick counter, etc)
//

#if HAVE_CONFIG_H
#  include <config.h>
#endif

#include "platform.h"
#include <stdlib.h>
#include <random>
#if HAVE_BSD_STDLIB_H
#  include <bsd/stdlib.h>
#endif

///////////////////////////////////////////////////////////////////////////////

// If this platform does not have `arc4random_buf', define a static,
// platform-specific function `read_time' so that we can set the random seed
// from the current time.
//

uint64_t platform_gen_seed() {
std::random_device rd;
std::uniform_int_distribution<uint64_t> gen;
return gen(rd);
}

//////////// platform specific mkdir /////////////////

#ifndef WIN32
#  include <sys/stat.h>
#  include <unistd.h>
#else
#  include <direct.h>
#endif
#include <cerrno>

bool create_dir(const char *dir)
{
#ifndef WIN32
	if (mkdir(dir, 0770) == -1) {
#else
	if (mkdir(dir) == -1) {
#endif
		return (errno == EEXIST) ? true : false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////

// Local Variables:
// c-basic-offset: 4
// tab-width: 4
// End:

// End of file.
