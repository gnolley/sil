set(PLAYBOOK_LIB_SRC "Playbook.cpp")

add_library(${PLAYBOOK_LIB_TARGET} STATIC PLAYBOOK_LIB_SRC)
target_include_directories(${PLAYBOOK_LIB_TARGET} PUBLIC "${PLAYBOOK_LIB_DIR}/includes/")

setup_target(${PLAYBOOK_LIB_TARGET})