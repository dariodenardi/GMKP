# GMKP

### Requirements
- Visual Studio
- ILOG CPLEX Optimization Studio

### Configuration Visual Studio

Right click on project -- Property

C/C++ -- Additional include directories:
```
C:\Program Files (x86)\IBM\ILOG\CPLEX_Studio_Preview126\cplex\include
C:\Program Files (x86)\IBM\ILOG\CPLEX_Studio_Preview126\concert\include
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
C:\Program Files (x86)\IBM\ILOG\CPLEX_Studio_Preview126\cplex\lib\x86_windows_vs2012\stat_mda\cplex1260.lib
C:\Program Files (x86)\IBM\ILOG\CPLEX_Studio_Preview126\cplex\lib\x86_windows_vs2012\stat_mda\ilocplex.lib
C:\Program Files (x86)\IBM\ILOG\CPLEX_Studio_Preview126\concert\lib\x86_windows_vs2012\stat_mda\concert.lib
```

Code Generation -- For 64 bit windows: code generation:
```
Multi-threaded DLL (/MD)
```
