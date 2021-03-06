#
# Module for finding Assimp
#
# The module will define:
# Assimp_FOUND - True if Assimp development files were found
# ASSIMP_INCLUDE_DIR - Assimp include directories
# ASSIMP_LIBRARY_RELEASE - Assimp libraries to link in release configuration
# ASSIMP_LIBRARY_DEBUG - Assimp libraries to link in debug configuration
# ASSIMP_DLL_RELEASE - Assimp DLL library (Windows only)
# ASSIMP_DLL_DEBUG - Assimp DLL library (Windows only)
#
# Assimp target will be created for cmake 3.0.0 and newer
#


# try config-based find first
# (Assimp version 3.1.1 includes config file, but no import target is created)
find_package(${CMAKE_FIND_PACKAGE_NAME} ${${CMAKE_FIND_PACKAGE_NAME}_FIND_VERSION} CONFIG QUIET)


if(${CMAKE_FIND_PACKAGE_NAME}_FOUND)

   # adjust variable names according to GPUEngine customs
   # and clean cache from non-sense stuff (config file is poorly written as of version 3.1.1)
   #
   # Yes but others may depend on it so removing the unsets for AssimpModelLoader's sake --forry 11.1.2017
   set(ASSIMP_INCLUDE_DIR "${ASSIMP_INCLUDE_DIRS}" CACHE PATH "Assimp include directory" FORCE)
   #unset(ASSIMP_INCLUDE_DIRS)
   #unset(ASSIMP_LIBRARIES)
   unset(ASSIMP_LIBRARY_SUFFIX CACHE)

   # Assimp bug workaround: include path is detected to be /usr/lib/include (wrong) instead
   # of /usr/include (correct), seen on Assimp 3.2, Kubuntu 16.04.
   # Workaround redetects include dir in the standard way.
   if(NOT EXISTS "${ASSIMP_INCLUDE_DIR}")
      unset(ASSIMP_INCLUDE_DIR CACHE)
      find_path(ASSIMP_INCLUDE_DIR assimp/mesh.h
         HINTS ${ASSIMP_ROOT_DIR}
         PATH_SUFFIXES include
         DOC "Assimp include directory"
      )
   endif()

else()

   # find Assimp includes
   find_path(ASSIMP_INCLUDE_DIR assimp/mesh.h
      HINTS ${ASSIMP_ROOT_DIR}
      PATH_SUFFIXES include
      DOC "Assimp include directory"
   )

endif()


# find Assimp libraries
find_library(ASSIMP_LIBRARY_RELEASE assimp
   HINTS ${ASSIMP_ROOT_DIR}
   PATH_SUFFIXES lib
   DOC "Assimp release library"
)
find_library(ASSIMP_LIBRARY_DEBUG assimpd NAMES assimp
   HINTS ${ASSIMP_ROOT_DIR}
   PATH_SUFFIXES lib
   DOC "Assimp debug library (optional)"
)

if(WIN32)

   # find Assimp DLLs
   find_file(ASSIMP_DLL_RELEASE assimp.dll
      HINTS ${ASSIMP_ROOT_DIR}
      PATH_SUFFIXES bin
      DOC "Assimp release DLL"
   )
   find_file(ASSIMP_DLL_DEBUG assimpd.dll NAMES assimp.dll
      HINTS ${ASSIMP_ROOT_DIR}
      PATH_SUFFIXES bin
      DOC "Assimp debug DLL (optional)"
   )

endif()


# substitute RELEASE and DEBUG libraries if one is missing
if(NOT ASSIMP_LIBRARY_RELEASE AND ASSIMP_LIBRARY_DEBUG)
   set(ASSIMP_LIBRARY_RELEASE ${ASSIMP_LIBRARY_DEBUG})
endif()
if(NOT ASSIMP_LIBRARY_DEBUG AND ASSIMP_LIBRARY_RELEASE)
   set(ASSIMP_LIBRARY_DEBUG ${ASSIMP_LIBRARY_RELEASE})
endif()


# set *_FOUND flag
if(ASSIMP_INCLUDE_DIR AND ASSIMP_LIBRARY_RELEASE)
   set(${CMAKE_FIND_PACKAGE_NAME}_FOUND True)
endif()


# create target
if(${CMAKE_FIND_PACKAGE_NAME}_FOUND AND NOT TARGET ${CMAKE_FIND_PACKAGE_NAME})
   if(NOT ${CMAKE_MAJOR_VERSION} LESS 3)
      add_library(${CMAKE_FIND_PACKAGE_NAME} SHARED IMPORTED)
      if(WIN32)
         set_target_properties(${CMAKE_FIND_PACKAGE_NAME} PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${ASSIMP_INCLUDE_DIR}"
            IMPORTED_LOCATION_DEBUG "${ASSIMP_DLL_DEBUG}"
            IMPORTED_LOCATION_RELEASE "${ASSIMP_DLL_RELEASE}"
            IMPORTED_IMPLIB_DEBUG "${ASSIMP_LIBRARY_DEBUG}"
            IMPORTED_IMPLIB_RELEASE "${ASSIMP_LIBRARY_RELEASE}"
         )
      else()
         set_target_properties(${CMAKE_FIND_PACKAGE_NAME} PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${ASSIMP_INCLUDE_DIR}"
            IMPORTED_LOCATION_DEBUG "${ASSIMP_LIBRARY_DEBUG}"
            IMPORTED_LOCATION_RELEASE "${ASSIMP_LIBRARY_RELEASE}"
         )
      endif()
   endif()
endif()
