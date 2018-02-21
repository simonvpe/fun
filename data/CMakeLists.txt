add_library(fun.data INTERFACE)
target_include_directories(fun.data INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE::include/fun/data>)
set_target_properties(fun.data PROPERTIES
  INTERFACE_COMPILE_FEATURES cxx_std_17
  INTERFACE_COMPILE_OPTIONS "-fconcepts")

add_executable(array_test
  ${CMAKE_CURRENT_SOURCE_DIR}/array_test.cpp)
target_link_libraries(array_test
  doctest
  fun.data)
add_test(NAME fun_array_test COMMAND array_test)
