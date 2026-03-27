cmake_minimum_required(VERSION 3.5)

project(SongImporterExe VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Svg)

set(CMAKE_AUTORCC ON)

qt_standard_project_setup(REQUIRES 6.8)
 set(app_icon "")

 if(WIN32)
     set(app_icon "${CMAKE_CURRENT_SOURCE_DIR}/Resources/SongImporter.rc")
 endif()

qt_add_executable(appSongImporterExe
    main.cpp ${app_icon} Resources/resources.qrc
)


qt_add_qml_module(appSongImporterExe
    URI SongImporterExe
    QML_FILES
        Main.qml
        QML_FILES InputDialog.qml
        QML_FILES FolderInput.qml
        QML_FILES FileInput.qml
        QML_FILES ExportFormPage.qml
        RESOURCES Resources/resources.qrc
        QML_FILES ImporterDropArea.qml
        QML_FILES SongTable.qml
        QML_FILES
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appSongImporterExe PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appSongImporterExe
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_include_directories(appSongImporterExe
    PUBLIC ${CMAKE_SOURCE_DIR}/SongImporterLib
)

target_link_libraries(appSongImporterExe
    PRIVATE SongImporterLib Qt6::Quick Qt6::Svg
)



include(GNUInstallDirs)
install(TARGETS appSongImporterExe
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
