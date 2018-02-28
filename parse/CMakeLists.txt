add_library(fun.parse INTERFACE)
target_include_directories(fun.parse INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE::include/fun/parse>)
set_target_properties(fun.parse PROPERTIES
  INTERFACE_COMPILE_FEATURES cxx_std_17
  INTERFACE_COMPILE_OPTIONS "-fconcepts")

add_executable(parse_test
  ${CMAKE_CURRENT_SOURCE_DIR}/parse_test.cpp)
target_link_libraries(parse_test
  doctest
  fun.parse
  fun.data)
add_test(NAME fun_parse_test COMMAND parse_test)
