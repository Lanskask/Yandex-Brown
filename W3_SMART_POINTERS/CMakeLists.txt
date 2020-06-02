project(W3_SMART_POINTERS)

add_executable(my_object_pool my_object_pool.cpp)
#add_executable(object_pool object_pool.cpp)
add_executable(object_pool_test object_pool_test.cpp)
add_executable(unique_ptr_exprs unique_ptr_exprs.cpp)
add_executable(object_pool_unique_ptr
        object_pool_unique_ptr.cpp
        object_pool_unique_ptr_test.cpp)
add_executable(my_object_pool_un_ptr
        my_object_pool_un_ptr.cpp
        my_object_pool_un_ptr_test.cpp)
