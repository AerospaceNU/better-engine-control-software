set(UTILS_LIST
        ECSUtils.cpp
        HoriECSStates.cpp
        consts.cpp
        ECSState.cpp
        )

add_library(utils-and-constants ${UTILS_LIST})
target_link_libraries(utils-and-constants PUBLIC
        redlines)