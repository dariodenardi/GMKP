# GMKP

## Requirements

* CPLEX must be installed, of course. Academics can obtain it via the [IBM Academic Initiative](https://developer.ibm.com/academic/).
* IDE C++ (e.g. Visual Studio)

### Configuration Visual Studio for CPLEX Libraries

Right click on project -- Property

C/C++ -- Additional include directories:
```
C:\Program Files\IBM\ILOG\CPLEX_Studio129\cplex\include
C:\Program Files\IBM\ILOG\CPLEX_Studio129\concert\include
```

C/C++ -- Preprocessor:
```
WIN32
_CONSOLE
IL_STD
_CRT_SECURE_NO_WARNINGS
```

Linker -- Input:
```
C:\Program Files\IBM\ILOG\CPLEX_Studio129\cplex\lib\x86_windows_vs2012\stat_mda\cplex1260.lib
C:\Program Files\IBM\ILOG\CPLEX_Studio129\cplex\lib\x86_windows_vs2012\stat_mda\ilocplex.lib
C:\Program Files\IBM\ILOG\CPLEX_Studio129\concert\lib\x86_windows_vs2012\stat_mda\concert.lib
```

Code Generation -- For 64 bit windows: code generation:
```
Multi-threaded DLL (/MD)
```

## Structure

## License

The present work is distributed under the terms of ghe GNU General Public License v3 (see the `LICENSE` file).