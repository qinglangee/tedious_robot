
# needBuild 0:不编译  1:需要编译 
function (link_third_part target thirdPartName includeFold needBuild)
    if(${needBuild} LESS 1)
        add_library(${thirdPartName} STATIC IMPORTED)
        set_property(TARGET ${thirdPartName} PROPERTY IMPORTED_LOCATION ${PROJECT_BINARY_DIR}/thirdpart/${thirdPartName}/${thirdPartName}.lib)  
        # set_property(TARGET sqlite3 PROPERTY IMPORTED_LOCATION ${PROJECT_BINARY_DIR}/thirdpart/sqlite3/sqlite3.lib)

    else()
        add_subdirectory(thirdpart/${thirdPartName})
    endif()
    
    target_link_libraries(${target} ${thirdPartName})
    target_include_directories(${target} PUBLIC ${PROJECT_SOURCE_DIR}/thirdpart/${thirdPartName}/${includeFold})
 
endfunction ()

function(link_zhlib needBuild)
    if(${needBuild} LESS 1)
        add_library(zhlib STATIC IMPORTED)
        set_property(TARGET zhlib PROPERTY IMPORTED_LOCATION ${PROJECT_BINARY_DIR}/zhlib/zhlib.lib) 
    else()
        add_subdirectory(zhlib)
    endif()

    target_link_libraries(app zhlib)
    target_include_directories(app PUBLIC zhlib/include)
endfunction()


# test
# argument_tester(arg0 arg1 arg2 arg3)