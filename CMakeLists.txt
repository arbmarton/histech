cmake_minimum_required(VERSION 3.9)
project(3dhistech)


set(HEADER_FILES
	include/Cache.h
	include/List.h
	include/Picture.h
	include/Utilities.h
)

set(SOURCE_FILES
	src/Cache.cpp
	src/List.cpp
	src/main.cpp
)

add_executable(${PROJECT_NAME}
			   ${HEADER_FILES}
			   ${SOURCE_FILES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
						   ${CMAKE_CURRENT_LIST_DIR}/include
)


			
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

# Parallel compilation and C++17
if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /MP")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4554")
endif(MSVC)


# Clang format setup
# http://mariobadr.com/using-clang-format-to-enforce-style.html
find_program(CLANG_FORMAT_EXE NAMES "clang-format")
if(NOT CLANG_FORMAT_EXE)
	message(STATUS "clang-format not found.")
else()
	message(STATUS "clang-format found: ${CLANG_FORMAT_EXE}")
	set(DO_CLANG_FORMAT "${CLANG_FORMAT_EXE}" "-i -style=file")
endif()

function(prepend var prefix)
	set(listVar "")
	
	foreach(f ${ARGN})
	  list(APPEND listVar "${prefix}/${f}")
	endforeach()
	
	set(${var} "${listVar}" PARENT_SCOPE)
endfunction()

if(CLANG_FORMAT_EXE)
	prepend(FILES_TO_FORMAT ${CMAKE_CURRENT_SOURCE_DIR} ${HEADER_FILES} ${SOURCE_FILES})
	
	add_custom_target(
		CLANG_FORMAT
		COMMAND ${CLANG_FORMAT_EXE} -i -style=file ${FILES_TO_FORMAT}
	)
endif()