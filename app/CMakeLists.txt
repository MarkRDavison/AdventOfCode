SET(AppMain "advent-of-code")

ADD_EXECUTABLE(${AppMain} "main.cpp" )
SET_PROPERTY(TARGET ${AppMain} PROPERTY CXX_STANDARD 17)
SET_PROPERTY(TARGET ${AppMain} PROPERTY CXX_STANDARD_REQUIRED ON)
TARGET_LINK_LIBRARIES(${AppMain} PRIVATE advent-of-code-core)
TARGET_LINK_LIBRARIES(${AppMain} PRIVATE advent-of-code-year2015)
TARGET_LINK_LIBRARIES(${AppMain} PRIVATE advent-of-code-year2016)
TARGET_LINK_LIBRARIES(${AppMain} PRIVATE advent-of-code-year2017)
TARGET_LINK_LIBRARIES(${AppMain} PRIVATE advent-of-code-year2018)
TARGET_LINK_LIBRARIES(${AppMain} PRIVATE advent-of-code-year2019)
TARGET_LINK_LIBRARIES(${AppMain} PRIVATE advent-of-code-year2020)
TARGET_LINK_LIBRARIES(${AppMain} PUBLIC zeno)

ADD_CUSTOM_COMMAND(TARGET ${AppMain} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:${AppMain}>/data)