cmake_minimum_required(VERSION 3.19)
cmake_policy(VERSION 3.19)

#### Initialize Mbed OS build system. ####
######################################################################################################
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#[[ Set path of mbed_app.json (necessary at all times) ]]
set(MBED_APP_JSON_PATH mbed_app.json5)

###--------------------------------------------------------------------------------------------------- 
#[[ This part is dedicated for custom targets only! Settings below activate targets from
    custom_targets.json5 and upload method config, otherwise lines below should be commented. ]]

#[[ Here set path for custom_targets.json5 (this is our default) ]]
set(CUSTOM_TARGETS_JSON_PATH custom_targets/custom_targets.json5)

#[[ Here you can set path for custom upload config.
    You may delete this line if you don't wish to use Mbed CE upload methods
    in your project.]]
set(CUSTOM_UPLOAD_CFG_PATH custom_targets/CustomUploadMethods.cmake)

   
### End of block
######################################################################################################

### Include Mbed toolchain setup file
include(mbed-os/tools/cmake/mbed_toolchain_setup.cmake)
set(MBED_OUTPUT_EXT "" CACHE STRING "" FORCE)
######################################################################################################
### Block of including project folders

###--------------------------------------------------------------------------------------------------
## Add another subdirectory, for example subdirectory of a library (if needed)
#add_subdirectory(YourLibrary)


### End of block
######################################################################################################

### Set up your project name (necessary everytime)
project(mbed-ce-deep-sleep
        VERSION 0.0.1
        LANGUAGES C CXX ASM)

### Include Mbed project setup file
include(mbed_project_setup)

#[[ Add custom targets subdir first, before mbed-os!]]
add_subdirectory(custom_targets)

###--------------------------------------------------------------------------------------------------
## Add mbed-os subdirectory next (necessary everytime)
add_subdirectory(mbed-os)

### add executable (necessary everytime)
add_executable(${CMAKE_PROJECT_NAME} main.cpp)

######################################################################################################
### Link libraries block
#[[For more about this configuration visit wiki page MbedOS-configuration
https://github.com/mbed-ce/mbed-os/wiki/MbedOS-configuration#configuration-via-cmake-files]]

# Link Mbed OS core library. This is called mbed-os when using the Mbed RTOS, and mbed-baremetal when using
# the bare metal version. This if statement checks to see which is in use and links it.
# Important: The mbed-os and mbed-baremetal libraries are object libraries, so they should ONLY be
# linked to executables, not to other libraries. Libraries should link to `mbed-core-flags` instead.
if("MBED_CONF_TARGET_APPLICATION_PROFILE=bare-metal" IN_LIST MBED_CONFIG_DEFINITIONS)
    target_link_libraries(${PROJECT_NAME} PRIVATE mbed-baremetal)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE mbed-os)
endif()

### link user library (if needed)
#target_link_libraries(${CMAKE_PROJECT_NAME} YourLibrary) 


### Set post build (necessary everytime)
mbed_set_post_build(${CMAKE_PROJECT_NAME})

#[[ Note: if you wish to use a custom linker script instead of the default Mbed one for
   your target, you can do that with mbed_set_post_build(${CMAKE_PROJECT_NAME} path/to/linker_script.ld) ]]


### End of block
######################################################################################################



