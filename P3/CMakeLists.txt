SET(MAIN_NAME strecken)
SET(TESTING_NAME testing)

set(SOURCES_STRECKEN
    p1_lib.h
    strecken.cpp
)

set(SOURCES_TESTING
    p1_lib.h
    testing.cpp
)

add_executable(${MAIN_NAME} ${SOURCES_STRECKEN})
add_executable(${TESTING_NAME} ${SOURCES_TESTING})
