SET(SRC main.cpp threadpool.cpp mutex.cpp task.cpp)
ADD_EXECUTABLE(pool_test ${SRC})
TARGET_LINK_LIBRARIES(pool_test pthread)
