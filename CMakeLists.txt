project(wifi-manager)

cmake_minimum_required(VERSION 3.10)

set(SERVICE_NAME ${CMAKE_PROJECT_NAME}-service)

include_directories(
    include/
)

add_executable(${SERVICE_NAME}
    impl/service/src/main.cpp
    impl/service/src/PasswordGenerator.cpp
    impl/service/src/WifiInitter.cpp
    impl/service/src/shell/Shell.cpp
)

target_include_directories(${SERVICE_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/impl/service/include
)

find_package(Threads REQUIRED)

target_link_libraries(${SERVICE_NAME}
    Threads::Threads
)

target_include_directories( ${SERVICE_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/impl/service/include
)

target_compile_features(${SERVICE_NAME} PRIVATE cxx_std_17)
