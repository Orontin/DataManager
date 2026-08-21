cmake_minimum_required(VERSION 3.20)
project(datamanager VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Sql)

qt_standard_project_setup()

qt6_add_executable(datamanager
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

target_link_libraries(datamanager PRIVATE Qt6::Core Qt6::Widgets Qt6::Sql)
