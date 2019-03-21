# There are 3 building cases:
#   - STANDALONE MODE, GENERATING EXECUTABLE        assets
#   - STANDALONE MODE, NOT GENERATING EXECUTABLE
#   - ONLINE MODE (not generating executable)

# ------------------------------------------------------------------------------
# Assets (images): copy assets to CMake binary output directory
# ------------------------------------------------------------------------------

function(CopyAssets source_path destination_path)
    file(GLOB_RECURSE ASSETS ${source_path}/*) # assets folder (root's fullpath)
    foreach (asset ${ASSETS})
        message(${source_path})
#        file(COPY ${asset} DESTINATION ${)
        string(REPLACE ${source_path} ${destination_path} output ${asset})
        message(${output})

        message("")
    endforeach ()
endfunction()

if((NOT ONLINE_MODE) AND BUILD_EXECUTABLE) # standalone AND build executable
    CopyAssets("${CMAKE_SOURCE_DIR}/assets" "${CMAKE_SOURCE_DIR}/bin/assets")
else() # (standalone AND no executable) OR online
    #if(ONLINE_TESTS OR ((NOT ONLINE_TESTS) AND BUILD_EXECUTABLE))
    CopyAssets(${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/bin/assets)
endif()