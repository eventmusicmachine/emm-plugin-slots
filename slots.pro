DEFINES += SLOTS_LIBRARY

QT += widgets

EMM_SOURCE_TREE = "../emm"

include(../emm/emmplugin.pri)

LIBS += -l$$qtLibraryName(ExtensionSystem, 4.5.0)

HEADERS += \
    slots_global.h \
    slotsplugin.h \
    slotcomponentfactory.h \
    slotcomponentwidget.h \
    generalsettingsfactory.h \
    generalsettingspage.h \
    layer.h \
    layertablemodel.h \
    slotwidget.h \
    layerselectiontoolbar.h \
    slot.h \
    slotconfigurationdialog.h

SOURCES += \
    slotsplugin.cpp \
    slotcomponentfactory.cpp \
    slotcomponentwidget.cpp \
    generalsettingspage.cpp \
    layer.cpp \
    layertablemodel.cpp \
    slotwidget.cpp \
    layerselectiontoolbar.cpp \
    slot.cpp \
    slotconfigurationdialog.cpp

FORMS += \
    slotcomponentwidget.ui \
    slotwidget.ui \
    slotconfigurationdialog.ui \
    generalsettingspage.ui

DISTFILES += \
    slots.json

OTHER_FILES += \
    README.md \
    LICENSE

RESOURCES += \
    resources.qrc
