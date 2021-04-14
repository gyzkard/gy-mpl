file(GLOB test-sources CONFIGURE_DEPENDS *.cpp)

add_custom_target(gympl-test)

enable_testing()

foreach (source IN LISTS test-sources)
  get_filename_component(test "${source}" NAME_WE)

  add_executable(gympl-test-${test} ${source} ${ARGN})
  add_test(gympl-test-${test} gympl-test-${test})

  set_property(TARGET gympl-test-${test} PROPERTY CXX_STANDARD ${GYMPL_CPP_STD})
  target_compile_features(gympl-test-${test} INTERFACE cxx_std_11)
  target_link_libraries(gympl-test-${test} PRIVATE gympl)
  add_dependencies(gympl-test gympl-test-${test})
endforeach()
