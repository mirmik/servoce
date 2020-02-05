cmake_minimum_required(VERSION 3.5.1)
project(servoce)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CC_STANDARD 11)

file(GLOB HEADERS 
	include/servoce/*.h
)

file(GLOB SOURCES 
	src/b64.cpp      
	src/curve3.cpp   
	src/face.cpp         
	src/interactive_object.cpp  
	src/opencascade_types.cpp  
	src/prs3d.cpp   
	src/shape_view.cpp  
	src/view.cpp
	src/boolops.cpp  
	src/convert.cpp   
	src/geombase.cpp  
	src/geomprops.cpp  
	src/solid.cpp       
	src/topo.cpp   
	src/viewer.cpp
	src/camera.cpp   
	src/curve2.cpp           
	src/scene.cpp   
	src/surface.cpp     
	src/trans.cpp  
	src/wire.cpp
)

file(GLOB SOURCES_TEST 
	utests/*.cpp
)

add_executable(servoce_test ${SOURCES_TEST})
add_library(servoce SHARED ${SOURCES})

target_include_directories(servoce_test PRIVATE . $ENV{OCCT_INCLUDE} src include)
target_include_directories(servoce PRIVATE . $ENV{OCCT_INCLUDE} src include)

target_link_libraries(servoce_test servoce)
target_link_libraries(servoce_test gtest)
target_link_libraries(servoce_test pthread)

target_link_libraries(servoce 
	nos
	igris
	TKernel
	TKMath
	TKG2d
	TKG3d
	TKBRep
	TKGeomBase
	TKGeomAlgo
	TKTopAlgo
	TKPrim
	TKBO
	TKBool
	TKOffset
	TKService
	TKV3d
	TKOpenGl
	TKFillet
	TKSTL
	TKBin
	TKShHealing
	TKMesh
	TKHLR
)

if (UNIX AND NOT APPLE)
	install(TARGETS ${PROJECT_NAME}
		LIBRARY DESTINATION /usr/lib
	)

	install(DIRECTORY ${PROJECT_NAME}
    	    DESTINATION /usr/local/include
    	    PATTERN "*HIDE*" EXCLUDE
   	)
endif()


if (APPLE)
	install(TARGETS ${PROJECT_NAME}
		LIBRARY DESTINATION /usr/local/lib
	)

	install(DIRECTORY ${PROJECT_NAME}
    	    DESTINATION /usr/local/include
    	    PATTERN "*HIDE*" EXCLUDE
   	)
endif()

enable_testing()
add_test(NAME servoce_test COMMAND servoce_test)