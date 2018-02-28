add_library(fun.data INTERFACE)
target_include_directories(fun.data INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE::include/fun/data>)
set_target_properties(fun.data PROPERTIES
  INTERFACE_COMPILE_FEATURES cxx_std_17
  INTERFACE_COMPILE_OPTIONS "-fconcepts")

function(fun_add_test name source)
  add_executable(${name} ${source})
  target_link_libraries(${name} doctest fun.data)
  add_test(NAME fun_${name} COMMAND ${name})
endfunction()

fun_add_test(array_test ${CMAKE_CURRENT_SOURCE_DIR}/array_test.cpp)
fun_add_test(maybe_test ${CMAKE_CURRENT_SOURCE_DIR}/maybe_test.cpp)
fun_add_test(either_test ${CMAKE_CURRENT_SOURCE_DIR}/either_test.cpp)
