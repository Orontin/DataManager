cmake_minimum_required(VERSION 3.19)
project(datamanager LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Sql)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(datamanager
    WIN32 MACOSX_BUNDLE
    main.cpp
    database/database.h
    database/database.cpp
    structs/data.h
    structs/login.h
    structs/mail.h
    structs/telephone.h
    structs/twofactor.h
    structs/secret.h
    structs/password.h
)

target_link_libraries(datamanager PRIVATE Qt::Core Qt::Widgets Qt::Sql)
target_link_libraries(datamanager PRIVATE Qt6::Core)

include(GNUInstallDirs)

install(TARGETS datamanager
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET datamanager
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
