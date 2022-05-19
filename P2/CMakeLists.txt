SET(MAIN_NAME bundesland)
SET(TESTING_NAME testing)

set(SOURCES_BUNDESLAND
    bundesland.cpp
)

set(SOURCES_TESTING
    testing.cpp
)

add_executable(${MAIN_NAME} ${SOURCES_BUNDESLAND})
# add_executable(${TESTING_NAME} ${SOURCES_TESTING})

install(TARGETS ${MAIN_NAME}
        CONFIGURATIONS Debug
        RUNTIME DESTINATION ./)
