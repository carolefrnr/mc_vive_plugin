file(REMOVE_RECURSE
  "doc/VivePlugin.doxytag"
  "doc/doxygen-html"
  "doc/doxygen.log"
  "CMakeFiles/distcheck"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/distcheck.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
