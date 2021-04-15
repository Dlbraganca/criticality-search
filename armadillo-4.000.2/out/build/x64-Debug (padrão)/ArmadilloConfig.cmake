# - Config file for the Armadillo package
# It defines the following variables
#  ARMADILLO_INCLUDE_DIRS - include directories for Armadillo
#  ARMADILLO_LIBRARY_DIRS - library directories for Armadillo (normally not used!)
#  ARMADILLO_LIBRARIES    - libraries to link against

# Tell the user project where to find our headers and libraries
set(ARMADILLO_INCLUDE_DIRS "F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2;F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2/out/build/x64-Debug (padrão)")
set(ARMADILLO_LIBRARY_DIRS "F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2/out/build/x64-Debug (padrão)")

# Our library dependencies (contains definitions for IMPORTED targets)
include("F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2/out/build/x64-Debug (padrão)/ArmadilloLibraryDepends.cmake")

# These are IMPORTED targets created by ArmadilloLibraryDepends.cmake
set(ARMADILLO_LIBRARIES armadillo)

