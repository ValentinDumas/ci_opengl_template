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
            string(REPLACE "${source_path}" "${destination_path}" asset_destination ${asset_source})
            string(REPLACE "/" "\\" asset_source_formatted ${asset_source})
            string(REPLACE "/" "\\" asset_destination_formatted ${asset_destination})
            configure_file(${asset_source_formatted} ${asset_destination_formatted})
            #message("")
        endif()
    endforeach ()
endfunction()

function(MoveFolderToTarget assets_source_path target_name assets_path_relative_to_target)
    add_custom_command(TARGET ${target_name}
            PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${assets_source_path}
            $<TARGET_FILE_DIR:${target_name}>\\${assets_path_relative_to_target})
endfunction()

function(MoveAssetsToTarget assets_source_path target_name)
    MoveFolderToTarget(${assets_source_path} ${target_name} assets)
endfunction()

if((NOT ONLINE_MODE) AND BUILD_EXECUTABLE) # standalone AND build executable
    CopyAssets("${CMAKE_SOURCE_DIR}\\assets" "${CMAKE_SOURCE_DIR}\\bin\\assets")
endif()

if((NOT ONLINE_MODE) AND (NOT BUILD_EXECUTABLE)) # standalone AND no executable
    CopyAssets("${CMAKE_SOURCE_DIR}\\assets" "${CMAKE_BINARY_DIR}\\bin\\assets")
endif()