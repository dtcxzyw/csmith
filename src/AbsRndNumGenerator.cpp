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

#include <random>
#if HAVE_CONFIG_H
#  include <config.h>
#endif

#include "AbsRndNumGenerator.h"

#include <cassert>
#include <cstdlib>

#include "DefaultRndNumGenerator.h"
#include "DFSRndNumGenerator.h"
#include "pcg-cpp/include/pcg_random.hpp"

using namespace std;

const char *AbsRndNumGenerator::hex1 = "0123456789ABCDEF";

const char *AbsRndNumGenerator::dec1 = "0123456789";

AbsRndNumGenerator::AbsRndNumGenerator()
{
	//Nothing to do
}

AbsRndNumGenerator::~AbsRndNumGenerator()
{
	//Nothing to do
}

/*
 * Factory method to create random number generators.
 */
AbsRndNumGenerator*
AbsRndNumGenerator::make_rndnum_generator(RNDNUM_GENERATOR impl, const uint64_t seed)
{
	AbsRndNumGenerator *rImpl = 0;

	AbsRndNumGenerator::seedrand(seed);
	switch (impl) {
		case rDefaultRndNumGenerator:
			rImpl = DefaultRndNumGenerator::make_rndnum_generator(seed);
			break;
		case rDFSRndNumGenerator:
			rImpl = DFSRndNumGenerator::make_rndnum_generator();
			break;
		default:
			assert(!"unknown random generator");
			break;
	}

	return rImpl;
}

static pcg64 engine;

void
AbsRndNumGenerator::seedrand(const uint64_t seed )
{
	engine.seed(seed);
}

unsigned long
AbsRndNumGenerator::genrand(void)
{
	std::uniform_int_distribution<unsigned long> gen;
	return gen(engine);
}

std::string
AbsRndNumGenerator::RandomHexDigits( int num )
{
	std::string str;
	while ( num-- )
	{
		str += hex1[genrand()%16];
	}

	return str;
}

std::string
AbsRndNumGenerator::RandomDigits( int num )
{
	std::string str;
	while ( num-- )
	{
		str += dec1[genrand()%10];
	}

	return str;
}

const char *
AbsRndNumGenerator::get_hex1()
{
	return AbsRndNumGenerator::hex1;
}

const char *
AbsRndNumGenerator::get_dec1()
{
	return AbsRndNumGenerator::dec1;
}

