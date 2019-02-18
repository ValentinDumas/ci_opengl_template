project(Glad) #Note: The glad version currently in use is the glad compatibility verison 3.3

include_directories(include)

add_library(glad_lib STATIC include/khrplatform.h include/glad/glad.h src/glad.c)