# ------------------------------------------------------------------------------
# File: CMakeLists.txt
# Created by Spark on 28/04/2019.
# ------------------------------------------------------------------------------

# [Building Process]
# There are 3 building cases:
#   - STANDALONE MODE, GENERATING EXECUTABLE        assets are moved to a bin folder belonging to the projet. The binary folder contains the ready-to-use application + assets
#   - STANDALONE MODE, NOT GENERATING EXECUTABLE    assets are moved to a bin folder in the cmake binary path. Idem, but does not contain a ready-to-use executable
#   - ONLINE MODE (not generating executable)       assets

# ------------------------------------------------------------------------------
# Copy assets
# ------------------------------------------------------------------------------
# Note: The destination is determined by the configuration of the current build process.
if((NOT ONLINE_MODE) AND BUILD_EXECUTABLE_IN_PROJECT_TREE) # standalone AND build executable
    CopyAssets("${CMAKE_SOURCE_DIR}\\assets" "${CMAKE_SOURCE_DIR}\\bin\\assets")
endif()

if((NOT ONLINE_MODE) AND (NOT BUILD_EXECUTABLE_IN_PROJECT_TREE)) # standalone AND no executable
    CopyAssets("${CMAKE_SOURCE_DIR}\\assets" "${CMAKE_BINARY_DIR}\\bin\\assets")
endif()