SET(MAIN_NAME lineSweep)
SET(TESTING_NAME lineSweepTest)

set(SOURCES_STRECKEN
    p3_lib.h
    line_sweep.cpp
)

set(SOURCES_TESTING
    p3_lib.h
    line_sweep_test.cpp
)

add_executable(${MAIN_NAME} ${SOURCES_STRECKEN})
add_executable(${TESTING_NAME} ${SOURCES_TESTING})
