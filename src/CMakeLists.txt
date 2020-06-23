set(GB_SRCS
  "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/loguru.cpp"
)

add_executable(gb ${GB_SRCS})
target_link_libraries(gb pthread dl)
target_compile_definitions(gb PRIVATE LOGURU_WITH_STREAMS)
