
# Find all cpp files in current directory
file(GLOB CPP_SOURCES "*.cpp")

# Create an executable for each cpp file
foreach(source_file ${CPP_SOURCES})
    # Get filename without extension
    get_filename_component(target_name ${source_file} NAME_WE)
    
    # Create executable with .exe extension
    add_executable(${target_name}.exe ${source_file})
    
    # Set properties
    set_target_properties(${target_name}.exe PROPERTIES 
        COMPILE_FLAGS "${COMPILE_FLAGS}"
        LINK_FLAGS "${LINK_FLAGS}")
endforeach()


