# Install script for directory: F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2/out/install/x64-Debug (padrão)")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2/out/install/x64-Debug (padrão)/include/")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2/out/install/x64-Debug (padrão)/include" TYPE DIRECTORY FILES "F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2/out/build/x64-Debug (padrão)/build_tmp/include/" REGEX "/\\.svn$" EXCLUDE REGEX "/[^/]*\\.cmake$" EXCLUDE REGEX "/[^/]*\\~$" EXCLUDE REGEX "/[^/]*orig$" EXCLUDE)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2/out/install/x64-Debug (padrão)/lib/armadillo.lib")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2/out/install/x64-Debug (padrão)/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2/out/build/x64-Debug (padrão)/armadillo.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2/out/install/x64-Debug (padrão)/lib/armadillo.dll")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2/out/install/x64-Debug (padrão)/lib" TYPE SHARED_LIBRARY FILES "F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2/out/build/x64-Debug (padrão)/armadillo.dll")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2/out/install/x64-Debug (padrão)/share/Armadillo/CMake/ArmadilloLibraryDepends.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2/out/install/x64-Debug (padrão)/share/Armadillo/CMake/ArmadilloLibraryDepends.cmake"
         "F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2/out/build/x64-Debug (padrão)/CMakeFiles/Export/b92db4e3d2be53461d108f0fe90aa52e/ArmadilloLibraryDepends.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2/out/install/x64-Debug (padrão)/share/Armadillo/CMake/ArmadilloLibraryDepends-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2/out/install/x64-Debug (padrão)/share/Armadillo/CMake/ArmadilloLibraryDepends.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2/out/install/x64-Debug (padrão)/share/Armadillo/CMake/ArmadilloLibraryDepends.cmake")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2/out/install/x64-Debug (padrão)/share/Armadillo/CMake" TYPE FILE FILES "F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2/out/build/x64-Debug (padrão)/CMakeFiles/Export/b92db4e3d2be53461d108f0fe90aa52e/ArmadilloLibraryDepends.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2/out/install/x64-Debug (padrão)/share/Armadillo/CMake/ArmadilloLibraryDepends-debug.cmake")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2/out/install/x64-Debug (padrão)/share/Armadillo/CMake" TYPE FILE FILES "F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2/out/build/x64-Debug (padrão)/CMakeFiles/Export/b92db4e3d2be53461d108f0fe90aa52e/ArmadilloLibraryDepends-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2/out/install/x64-Debug (padrão)/share/Armadillo/CMake/ArmadilloConfig.cmake;F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2/out/install/x64-Debug (padrão)/share/Armadillo/CMake/ArmadilloConfigVersion.cmake")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2/out/install/x64-Debug (padrão)/share/Armadillo/CMake" TYPE FILE FILES
    "F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2/out/build/x64-Debug (padrão)/InstallFiles/ArmadilloConfig.cmake"
    "F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2/out/build/x64-Debug (padrão)/InstallFiles/ArmadilloConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "F:/UFF/IC2/Ck-Tuple Search/Projects-Visual Studio/armadillo-4.000.2/out/build/x64-Debug (padrão)/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
