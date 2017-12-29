DEFINES += SLOTS_LIBRARY

QT += widgets

EMM_SOURCE_TREE = "../emm"
EMM_BUILD_TREE = "../build-emm-Desktop_Qt_5_9_2_GCC_64bit-Debug"

include(../emm/emmplugin.pri)

LIBS += -l$$qtLibraryName(ExtensionSystem, 4.5.0)

HEADERS += \
    slots_global.h \
    slotsplugin.h \
    slotcomponentfactory.h \
    slotcomponentwidget.h \
    generalsettingsfactory.h \
    generalsettingspage.h \
    generalsettingswidget.h \
    layer.h \
    layertablemodel.h \
    slotwidget.h \
    layerselectiontoolbar.h

SOURCES += \
    slotsplugin.cpp \
    slotcomponentfactory.cpp \
    slotcomponentwidget.cpp \
    generalsettingspage.cpp \
    generalsettingswidget.cpp \
    layer.cpp \
    layertablemodel.cpp \
    slotwidget.cpp \
    layerselectiontoolbar.cpp

FORMS += \
    slotcomponentwidget.ui \
    generalsettingswidget.ui \
    slotwidget.ui

DISTFILES += \
    slots.json

OTHER_FILES += \
    README.md \
    LICENSE

RESOURCES += \
    resources.qrc
