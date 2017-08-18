////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2008, Massachusetts Institute of Technology              //
// Copyright (c) 2010-2013, Giulio Paci <giuliopaci@gmail.com>            //
// Copyright (c) 2013, Jakub Wilk  <jwilk@debian.org>                     //
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

#ifndef ZFILE_H
#define ZFILE_H

#include <fcntl.h>
#include <cstdio>
#include <string>
#include <cstring>
#include <stdexcept>
#include <sstream>

#ifndef O_BINARY
#define O_BINARY 0
#endif

namespace mitlm {

class ZFile {
protected:
    FILE *      _file;
    std::string _filename;
    std::string _mode;

public:
    ZFile(const char *filename, const char *mode="r") {
        if (mode == NULL || (mode[0] != 'r' && mode[0] != 'w'))
            throw std::runtime_error("Invalid mode");

        _filename = filename;
	if(mode[0] == 'r')
	{
            _mode = O_BINARY ? "rb" : "r";
	}
	else if(mode[0] == 'w')
	{
            _mode = O_BINARY ? "wb" : "w";
	}
        ReOpen();
    }
    ~ZFile() { if (_file) fclose(_file); }

    void ReOpen() {
        const char *mode = _mode.c_str();
        // Assume uncompressed
        _file = fopen(_filename.c_str(), mode);
        if (_file == NULL)
            throw std::runtime_error("Cannot open file");
    }

    operator FILE *() const { return _file; }
};

}

#endif // ZFILE_H
