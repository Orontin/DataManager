cmake_minimum_required(VERSION 3.19)
project(datamanager LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Sql)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(datamanager
    WIN32 MACOSX_BUNDLE
    main.cpp

    database/database.h
    database/database.cpp

    database/structs/data.h
    database/structs/login.h
    database/structs/mail.h
    database/structs/telephone.h
    database/structs/twofactor.h
    database/structs/secret.h
    database/structs/password.h
    database/structs/logins.h
    database/structs/mails.h
    database/structs/passwords.h
    database/structs/secrets.h
    database/structs/telephones.h
    database/structs/twofactors.h
    database/structs/datas.h


    widgets/mainwindow.h
    widgets/mainwindow.cpp
    widgets/mainwindow.ui

    models/datamodel.h
    models/datamodel.cpp
    database/structs/abstract.h

    aes/qaesencryption.h
    aes/qaesencryption.cpp
)

target_link_libraries(datamanager PRIVATE Qt::Core Qt::Widgets Qt::Sql)
target_link_libraries(datamanager PRIVATE Qt6::Core)
target_link_libraries(datamanager PRIVATE Qt6::Widgets)
target_link_libraries(datamanager PRIVATE Qt6::Core)
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
