set(PLAYBOOK_LIB_SRC "Playbook.cpp" "SilId.cpp" "Asset.cpp")

add_library(${PLAYBOOK_LIB_TARGET} STATIC ${PLAYBOOK_LIB_SRC})
target_include_directories(${PLAYBOOK_LIB_TARGET} PUBLIC ${PLAYBOOK_INCLUDE_DIR})

find_package(xxHash CONFIG REQUIRED)
target_link_libraries(${PLAYBOOK_LIB_TARGET} PRIVATE xxHash::xxhash)

setup_target(${PLAYBOOK_LIB_TARGET})