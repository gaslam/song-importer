cmake_minimum_required(VERSION 3.5)

project(SongImporterLib LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(SongImporterLib SHARED
  SongImporterLib_global.h
  InputValidator.cpp
  InputValidator.h
  FolderValidator.h FolderValidator.cpp
  FileValidator.h FileValidator.cpp
  FileUtils.h
  OperationResult.h
  FileReceiver.h FileReceiver.cpp
  SongList.h SongList.cpp
)

target_compile_definitions(SongImporterLib PRIVATE SONGIMPORTERLIB_LIBRARY)



list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/ThirdParty/zlib/lib")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/ThirdParty/zlib/include")

target_include_directories(SongImporterLib PRIVATE ${ZLIB_INCLUDE_DIR})
target_link_directories(SongImporterLib PRIVATE ${ZLIB_LIBRARY})
find_package(ZLIB REQUIRED)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/ThirdParty/quazip/lib/cmake/QuaZip-Qt6-1.5")

find_package(QuaZip-Qt6 REQUIRED)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/ThirdParty/taglib/lib/cmake/taglib")
find_package(TagLib REQUIRED)

target_link_libraries(SongImporterLib PUBLIC ZLIB::ZLIB QuaZip::QuaZip TagLib::tag)
target_link_libraries(SongImporterLib PRIVATE Qt${QT_VERSION_MAJOR}::Core)
