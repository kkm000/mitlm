# MIT Language Modeling Toolkit

This is **not** the official GitHub repository for the MITLM project.
The closest thing is apparently https://github.com/mitlm/mitlm.

Check the [README](README) file of the original version.

## Native Windows port

Ported from v0.4.2 by @kkm000 for Visual Studio 2015 and 2017.
[Diff changes](../../compare/master...windows-port).

### Build:
 * Open and build `src/mitlm.sln` (or msbuid from command line).
 * Locate the compiled binaries in `src/bin/{Debug,Release}`.

### Features removed and not suppoted:
 * BFGS and LBFGS optimization (Powell is the default).
 * Compressed files.

### Hacking
 * Take notice of the file [`src/mitlm.props`](src/mitlm.props).
   This file is included by all 4 project files. The rest is pretty
   much vanilla VS project/solution files.
