# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Omegacam_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Omegacam_autogen.dir\\ParseCache.txt"
  "Omegacam_autogen"
  )
endif()
