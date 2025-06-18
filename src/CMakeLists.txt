# add executable
#add_executable(main main.cpp)

add_library(isobmff
    AV01.cpp
    AVC1.cpp
    AVCC-NALUnit.cpp
    AVCC.cpp
    BinaryDataStream.cpp
    BinaryFileStream.cpp
    BinaryStream.cpp
    Box.cpp
    CDSC.cpp
    COLR.cpp
    config.h.in
    Container.cpp
    ContainerBox.cpp
    CTTS.cpp
    DIMG.cpp
    DisplayableObject.cpp
    DisplayableObjectContainer.cpp
    DREF.cpp
    File.cpp
    FRMA.cpp
    FTYP.cpp
    FullBox.cpp
    HDLR.cpp
    HVC1.cpp
    HVCC-Array-NALUnit.cpp
    HVCC-Array.cpp
    HVCC.cpp
    IINF.cpp
    ILOC-Item-Extent.cpp
    ILOC-Item.cpp
    ILOC.cpp
    ImageGrid.cpp
    INFE.cpp
    IPCO.cpp
    IPMA-Entry-Association.cpp
    IPMA-Entry.cpp
    IPMA.cpp
    IREF.cpp
    IROT.cpp
    ISPE.cpp
    Matrix.cpp
    MDHD.cpp
    META.cpp
    MP4A.cpp
    MVHD.cpp
    Parser.cpp
    PITM.cpp
    PIXI-Channel.cpp
    PIXI.cpp
    SCHM.cpp
    SingleItemTypeReferenceBox.cpp
    STSD.cpp
    STSS.cpp
    STTS.cpp
    THMB.cpp
    TKHD.cpp
    URL.cpp
    URN.cpp
    Utils.cpp
    WIN32.cpp

)

target_include_directories(isobmff PUBLIC ../include)
if (WIN32)
  target_link_libraries(isobmff PUBLIC wsock32 ws2_32)
endif()

# https://cmake.org/cmake/help/latest/guide/tutorial/index.html#adding-a-version-number-and-configured-header-file
configure_file(config.h.in config.h)

# this allows the 'config.h' file to be used throughout the program
target_include_directories(isobmff PUBLIC "${CMAKE_CURRENT_BINARY_DIR}")
