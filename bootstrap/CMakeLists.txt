
add_executable(${BOOTSTRAP_TARGET} "main.cpp")
setup_target(${BOOTSTRAP_TARGET})

target_include_directories(${BOOTSTRAP_TARGET} PRIVATE ${CMAKE_BINARY_DIR}/configured_files/include)

target_link_libraries(${BOOTSTRAP_TARGET} PRIVATE 
	${ENGINE_SRC_TARGET}
)