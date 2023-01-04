# Submodule handling
function(check_submodule_exists name path)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.git" AND
       NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${path}/.git")
        message(FATAL_ERROR
                "The ${name} git submodule is not initialized.\n"
                "Please run the following commands in the source directory (${PROJECT_SOURCE_DIR}):\n"
                "    git submodule update --init --recursive\n")
    endif()
endfunction()
