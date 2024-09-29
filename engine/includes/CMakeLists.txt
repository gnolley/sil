set(SIL_COR_INCLUDES 
	"${CMAKE_SOURCE_DIR}/engine/includes/"
	${Vulkan_INCLUDE_DIRS}
)

target_include_directories(${ENGINE_SRC_TARGET} PUBLIC ${SIL_COR_INCLUDES})