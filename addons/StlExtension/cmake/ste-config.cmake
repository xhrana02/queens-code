# Internal library - STL Extension.
# Collection of algorithms and data structures that are missing in C++ STL.

set(STE_NAME "ste")
set(STE_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/..")

#If target was already defined then return. Perhaps it was included from another package.
IF(TARGET ${STE_NAME})
   return()
ENDIF()

 
set(HEADER_FILES
   ${STE_ROOT_DIR}/ste/concepts.h
   ${STE_ROOT_DIR}/ste/concepts_undef.h
   ${STE_ROOT_DIR}/ste/stl_extension.h
   ${STE_ROOT_DIR}/ste/DAG.h
)

set(SOURCE_FILES)


add_library(${STE_NAME} INTERFACE) # ${HEADER_FILES} ${SOURCE_FILES})
target_include_directories(${STE_NAME} INTERFACE ${STE_ROOT_DIR})

#message("STE ${STE_ROOT_DIR}")