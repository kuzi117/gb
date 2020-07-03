add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/mem")

set(SIM_SRCS
  "${CMAKE_CURRENT_SOURCE_DIR}/Simulator.cpp"
  ${MEM_SRCS}
  PARENT_SCOPE
)
