file(REMOVE_RECURSE
  "libGFXLib.a"
  "libGFXLib.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/GFXLib.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
