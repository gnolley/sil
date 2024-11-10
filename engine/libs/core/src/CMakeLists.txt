set(CORE_LIB_SRC 
 "Debug/Logger.cpp"  
 "Config/RenderingFeatures.cpp"
)

add_library(${CORE_LIB_TARGET} STATIC ${CORE_LIB_SRC})

target_include_directories(${CORE_LIB_TARGET} PUBLIC ${CORE_INCLUDE_DIR})

setup_target(${CORE_LIB_TARGET})