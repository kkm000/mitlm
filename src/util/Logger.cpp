////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2008, Massachusetts Institute of Technology              //
// All rights reserved.                                                   //
//                                                                        //
// Redistribution and use in source and binary forms, with or without     //
// modification, are permitted provided that the following conditions are //
// met:                                                                   //
//                                                                        //
//     * Redistributions of source code must retain the above copyright   //
//       notice, this list of conditions and the following disclaimer.    //
//                                                                        //
//     * Redistributions in binary form must reproduce the above          //
//       copyright notice, this list of conditions and the following      //
//       disclaimer in the documentation and/or other materials provided  //
//       with the distribution.                                           //
//                                                                        //
//     * Neither the name of the Massachusetts Institute of Technology    //
//       nor the names of its contributors may be used to endorse or      //
//       promote products derived from this software without specific     //
//       prior written permission.                                        //
//                                                                        //
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS    //
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT      //
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  //
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT   //
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,  //
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT       //
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  //
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  //
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT    //
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  //
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   //
////////////////////////////////////////////////////////////////////////////

#include <cstdarg>
#include <cstdio>
#include "Logger.h"

namespace mitlm {

////////////////////////////////////////////////////////////////////////////////

#ifdef NDEBUG
    int  Logger::_verbosity = 0;
    bool Logger::_timestamp = false;
#else
    int  Logger::_verbosity = 1;
    bool Logger::_timestamp = true;
#endif
clock_t Logger::_startTime = clock();
FILE*   Logger::_err_file = stderr;

void Logger::Log(int level, const char *fmt, ...) {
    if (_verbosity >= level) {
	if ( _err_file != NULL ) {
            va_list args;
            va_start(args, fmt);
            if (_timestamp) 
	        fprintf(_err_file, "%.3f\t", (double)(clock() - _startTime) / CLOCKS_PER_SEC);
            vfprintf(_err_file, fmt, args);
            va_end(args);
            fflush(_err_file);
	}
    }
}

void Logger::Warn(int level, const char *fmt, ...) {
    if (_verbosity >= level) {
        va_list args;
	if ( _err_file != NULL ) {
            va_start(args, fmt);
            fprintf(_err_file, "WARNING: ");
            if (_timestamp) 
                fprintf(_err_file, "%.3f\t", (double)(clock() - _startTime) / CLOCKS_PER_SEC);
            vfprintf(_err_file, fmt, args);
            va_end(args);
            fflush(_err_file);
	}
    }
}

void Logger::Error(int level, const char *fmt, ...) {
    if (_verbosity >= level) {
        va_list args;
	if ( _err_file != NULL ) {
            va_start(args, fmt);
            fprintf(_err_file, "ERROR: ");
            if (_timestamp) 
                fprintf(_err_file, "%.3f\t", (double)(clock() - _startTime) / CLOCKS_PER_SEC);
            vfprintf(_err_file, fmt, args);
            va_end(args);
            fflush(_err_file);
	}
    }
}

}
