TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/main.cpp \
    src/Ant.cpp \
    src/AntHill.cpp \
    src/Block.cpp \
    src/BlockAir.cpp \
    src/BlockDirt.cpp \
    src/BlockFood.cpp \
    src/BlockStorage.cpp \
    src/Engine.cpp \
    src/Entite.cpp \
    src/IA.cpp \
    src/IAPathFinding.cpp \
    src/MathHelp.cpp \
    src/TileMap.cpp \
    src/WorldGen.cpp \
    src/BaseBlockSrc/BaseBlock.cpp \
    src/BaseBlockSrc/BaseBlockAir.cpp \
    src/BaseBlockSrc/BaseBlockDirt.cpp \
    src/BaseBlockSrc/BaseBlockFood.cpp \
    src/BaseBlockSrc/BaseBlockGallery.cpp \
    src/BaseBlockSrc/BaseBlockStone.cpp \
    src/BaseBlockSrc/BaseBlockStorage.cpp \
    src/BlockSrc/BlockGallery.cpp \
    src/BlockSrc/BlockStone.cpp \
    src/EntityTypeSrc/AntWorker.cpp \
    src/EntityTypeSrc/AntEgg.cpp \
    src/EntityTypeSrc/AntQueen.cpp \
    src/StateSrc/State.cpp \
    src/StateSrc/StateQueen.cpp \
    src/StateSrc/StateWorker.cpp

HEADERS += \
    include/Ant.h \
    include/AntHill.h \
    include/Block.h \
    include/BlockAir.h \
    include/BlockDirt.h \
    include/BlockFood.h \
    include/BlockStorage.h \
    include/Engine.h \
    include/Entite.h \
    include/IA.h \
    include/IAPathFinding.h \
    include/MathHelp.h \
    include/ResourceHolder.h \
    include/TileMap.h \
    include/WorldGen.h \
    include/BaseBlockHeader/BaseBlock.h \
    include/BaseBlockHeader/BaseBlockAir.h \
    include/BaseBlockHeader/BaseBlockDirt.h \
    include/BaseBlockHeader/BaseBlockFood.h \
    include/BaseBlockHeader/BaseBlockGallery.h \
    include/BaseBlockHeader/BaseBlockStone.h \
    include/BaseBlockHeader/BaseBlockStorage.h \
    include/BlockHeader/BlockGallery.h \
    include/BlockHeader/BlockStone.h \
    include/EntityTypesHeader/AntWorker.h \
    include/EntityTypesHeader/AntEgg.h \
    include/EntityTypesHeader/AntQueen.h \
    include/StateHeader/State.h \
    include/StateHeader/StateQueen.h \
    include/StateHeader/StateWorker.h


INCLUDEPATH += D:\Users\Kvykv\Projet\C++\Fourmis


LIBS += -LD:/Programs/SFML/lib

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += D:/Programs/SFML/include
DEPENDPATH += D:/Programs/SFML/include
