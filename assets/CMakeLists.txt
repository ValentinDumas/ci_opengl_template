# There are 3 building cases:
#   - STANDALONE MODE, GENERATING EXECUTABLE        assets are moved to a bin folder belonging to the projet. The binary folder contains the ready-to-use application + assets
#   - STANDALONE MODE, NOT GENERATING EXECUTABLE    assets are moved to a bin folder in the cmake binary path. Idem, but does not contain a ready-to-use executable
#   - ONLINE MODE (not generating executable)       assets

# ------------------------------------------------------------------------------
# Assets (images): copy assets to CMake binary output directory
# ------------------------------------------------------------------------------
function(CopyAssets source_path destination_path)
    file(GLOB_RECURSE ASSETS ${source_path}/*) # assets folder (root's fullpath)
    foreach (asset_source ${ASSETS})
        string(REGEX MATCH "CMakeLists.txt" cmakelist ${asset_source})
        if(NOT (cmakelist MATCHES "CMakeLists.txt"))
            #message(${source_path})
            string(REPLACE ${source_path} ${destination_path} asset_destination ${asset_source})
            #message(${asset_destination})
            configure_file(${asset_source} ${asset_destination})
            #message("")
        endif()
    endforeach ()
endfunction()

if((NOT ONLINE_MODE) AND BUILD_EXECUTABLE) # standalone AND build executable
    CopyAssets("${CMAKE_SOURCE_DIR}/assets" "${CMAKE_SOURCE_DIR}/bin/assets")
endif()

if((NOT ONLINE_MODE) AND (NOT BUILD_EXECUTABLE)) # standalone AND no executable
    CopyAssets(${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/bin/assets)
endif()

if(ONLINE_MODE) # online --> move assets to CMake's default binary folder
    CopyAssets(${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets)
endif()