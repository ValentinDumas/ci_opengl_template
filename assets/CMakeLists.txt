# ------------------------------------------------------------------------------
# Assets (images): copy assets to CMake binary output directory
# ------------------------------------------------------------------------------
file(GLOB_RECURSE ASSETS_IMAGES ${CMAKE_SOURCE_DIR}/assets/images/*)
foreach(asset_image ${ASSETS_IMAGES})
    #message(${asset_image})
    file(COPY ${asset_image} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/images) # note: bin dir is set to project root
endforeach(asset_image)

# ------------------------------------------------------------------------------
# Assets (shaders): copy shaders to CMake binary output directory
# ------------------------------------------------------------------------------
file(GLOB_RECURSE ASSETS_SHADERS ${CMAKE_SOURCE_DIR}/assets/shaders/*)
foreach(asset_shader ${ASSETS_SHADERS})
    #message(${asset_shader})
    file(COPY ${asset_shader} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/shaders) # note: bin dir is set to project root
endforeach(asset_shader)