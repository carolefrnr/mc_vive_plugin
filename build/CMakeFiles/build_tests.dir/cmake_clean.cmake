file(REMOVE_RECURSE
  "doc/VivePlugin.doxytag"
  "doc/doxygen-html"
  "doc/doxygen.log"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/build_tests.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
