SET(MAIN_NAME lineSweep)
set (CMAKE_CXX_STANDARD 14)
set (CXX_STANDARD 14)


set(SOURCES_STRECKEN
    p3_lib.h
    line_sweep.cpp
)

add_executable(${MAIN_NAME} ${SOURCES_STRECKEN})
