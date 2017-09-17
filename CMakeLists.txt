#files

file(GLOB EssexEngineLibIsoMap_HEADERS
    "src/Libs/IsoMap/*.h"
)
file(GLOB EssexEngineLibIsoMap_SRC
    ${EssexEngineLibIsoMap_HEADERS}
    "src/Libs/IsoMap/*.cpp"
)

#setup headers

file(COPY ${EssexEngineLibIsoMap_HEADERS} DESTINATION "${CMAKE_BINARY_DIR}/lib/include/EssexEngineLibIsoMap/")

#setup build

add_library(EssexEngineLibIsoMap SHARED ${EssexEngineLibIsoMap_SRC})
target_link_libraries(EssexEngineLibIsoMap EssexEngineCore)
target_link_libraries(EssexEngineLibIsoMap EssexEngineGfxDaemon)
target_link_libraries(EssexEngineLibIsoMap EssexEngineJsonDaemon)
target_link_libraries(EssexEngineLibIsoMap EssexEngineScriptDaemon)
target_link_libraries(EssexEngineLibIsoMap EssexEngineFileSystemDaemon)