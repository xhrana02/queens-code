cmake_minimum_required(VERSION 3.8)

set(PROJECT_NAME "QueensRegicide")
set(APP_NAME "QueensRegicide")

project(${PROJECT_NAME})

set(CMAKE_AUTORCC ON )
set(CMAKE_AUTOUIC ON )
set(CMAKE_AUTOMOC ON )

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules;${CMAKE_MODULE_PATH}")

find_package(Qt5 REQUIRED Quick QuickWidgets)
find_package(QtImageLoader REQUIRED HINTS ${CMAKE_SOURCE_DIR}/addons/QtImageLoader/cmake)
find_package(AssimpModelLoader REQUIRED HINTS ${CMAKE_SOURCE_DIR}/addons/AssimpModelLoader/cmake)
find_package(GPUEngine REQUIRED geGL geSG)

set(SRC_ROOT "${CMAKE_SOURCE_DIR}/src")
set(SRC_FILES "")
set(INCLUDE_DIRS "")

add_subdirectory(src)
list(APPEND SRC_FILES ${src_SRC_FILES})
list(APPEND INCLUDE_DIRS ${src_INCLUDE_DIRS})

message("Located source files:")
FOREACH(_FILE ${SRC_FILES})
    message("- ${_FILE}")
ENDFOREACH()
message("Located include directories:")
FOREACH(_DIRE ${INCLUDE_DIRS})
    message("- ${_DIRE}")
ENDFOREACH()

source_group(TREE ${SRC_ROOT} PREFIX "src" FILES ${SRC_FILES})

add_executable(${APP_NAME} ${SRC_FILES})

target_include_directories(${APP_NAME} PUBLIC ${INCLUDE_DIRS})

target_link_libraries(${APP_NAME} Qt5::Quick Qt5::QuickWidgets geGL geSG AssimpModelLoader QtImageLoader)

set_target_properties(${APP_NAME} PROPERTIES COMPILE_DEFINITIONS "APP_RESOURCES=\"Data\""
                                             VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)")

set_property(TARGET ${APP_NAME} PROPERTY FOLDER "${APP_NAME}")

add_custom_command(TARGET ${APP_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory     "${CMAKE_SOURCE_DIR}/libs/$<CONFIG>"
                                                "$<TARGET_FILE_DIR:QueensRegicide>"
                                                    
    COMMAND ${CMAKE_COMMAND} -E copy_directory     "${CMAKE_SOURCE_DIR}/resources"
                                                "$<TARGET_FILE_DIR:QueensRegicide>/Data"
)