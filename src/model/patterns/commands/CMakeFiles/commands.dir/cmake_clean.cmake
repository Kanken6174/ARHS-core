file(REMOVE_RECURSE
  "libcommands.a"
  "libcommands.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/commands.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
