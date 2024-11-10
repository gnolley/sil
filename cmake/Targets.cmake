set(ENGINE_SRC_TARGET Soliloquy)
set(ENGINE_DIR ${CMAKE_SOURCE_DIR}/engine)
set(BOOTSTRAP_TARGET Sil-Bootstrapper)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/engine/libs)

set(COOK_TOOL_TARGET Sil-Stagehand)
set(COOK_TOOL_DIR ${CMAKE_SOURCE_DIR}/tools/stagehand)

set(CORE_LIB_TARGET Sil-Core)
set(CORE_LIB_DIR ${LIB_DIR}/core)
set(CORE_INCLUDE_DIR ${CORE_LIB_DIR}/includes)

set(MEZZANINE_LIB_TARGET Sil-Mezzanine)
set(MEZZANINE_LIB_DIR ${LIB_DIR}/mezzanine)
set(MEZZANINE_INCLUDE_DIR ${MEZZANINE_LIB_DIR}/includes)

set(PLAYBOOK_LIB_TARGET Sil-Playbook)
set(PLAYBOOK_LIB_DIR ${LIB_DIR}/playbook)
set(PLAYBOOK_INCLUDE_DIR ${PLAYBOOK_LIB_DIR}/includes)

set(BUILD_BUILTIN_ASSETS_TARGET StagehandBuildBuiltin)