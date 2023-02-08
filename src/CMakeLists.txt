set(HEADER_FILES
    "${UnStdLibrary_SOURCE_DIR}/include/unstd/Array.hpp"
    "${UnStdLibrary_SOURCE_DIR}/include/unstd/Vector.hpp"
    "${UnStdLibrary_SOURCE_DIR}/include/unstd/Iterator.hpp"
    )

add_library(unstd_library INTERFACE ${HEADER_FILES})

target_include_directories(unstd_library INTERFACE ../include)

target_compile_features(unstd_library INTERFACE cxx_std_20)

source_group(
    TREE "${PROJECT_SOURCE_DIR}/include"
    PREFIX "Header Files"
    FILES ${HEADER_FILES}
    )
