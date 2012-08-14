# This file includes common sources between
# DrugsWidget plugins and freediams
INCLUDEPATH *= $${PWD}

DEFINES += DRUGS_LIBRARY

include($${PWD}/../fmf_plugins.pri)
include($${PWD}/drugsplugin_dependencies.pri )

# General
HEADERS += $${PWD}/drugs_exporter.h \
    $${PWD}/constants.h \
    $${PWD}/drugswidgetmanager.h \
    $${PWD}/drugswidget/atctreeviewer.h

SOURCES += $${PWD}/drugswidgetmanager.cpp \
    $${PWD}/drugswidget/atctreeviewer.cpp

# Dosage Dialog
HEADERS += $${PWD}/dosagedialog/mfDosageDialog.h \
    $${PWD}/dosagedialog/mfDosageCreatorDialog.h \
    $${PWD}/dosagedialog/mfDosageViewer.h

SOURCES += $${PWD}/dosagedialog/mfDosageDialog.cpp \
    $${PWD}/dosagedialog/mfDosageCreatorDialog.cpp \
    $${PWD}/dosagedialog/mfDosageViewer.cpp

FORMS += $${PWD}/dosagedialog/mfDosageDialog.ui \
    $${PWD}/dosagedialog/mfDosageCreatorDialog.ui \
    $${PWD}/dosagedialog/mfDosageViewer.ui

# DrugsWidget Preferences
HEADERS += \
#    $${PWD}/drugspreferences/mfDrugsPreferences.h \
    $${PWD}/drugspreferences/drugselectorpreferences.h \
    $${PWD}/drugspreferences/drugprintingpreferences.h \
    $${PWD}/drugspreferences/druggeneralpreferences.h \
    $${PWD}/drugspreferences/druguserpreferences.h \
    $${PWD}/drugspreferences/drugextrapreferences.h \
    $${PWD}/drugspreferences/databaseselectorwidget.h \
    $${PWD}/drugspreferences/protocolpreferencespage.h \
    $${PWD}/drugspreferences/drugenginespreferences.h

SOURCES += \
#    $${PWD}/drugspreferences/mfDrugsPreferences.cpp \
    $${PWD}/drugspreferences/drugselectorpreferences.cpp \
    $${PWD}/drugspreferences/drugprintingpreferences.cpp \
    $${PWD}/drugspreferences/druggeneralpreferences.cpp \
    $${PWD}/drugspreferences/druguserpreferences.cpp \
    $${PWD}/drugspreferences/drugextrapreferences.cpp \
    $${PWD}/drugspreferences/databaseselectorwidget.cpp \
    $${PWD}/drugspreferences/protocolpreferencespage.cpp \
    $${PWD}/drugspreferences/drugenginespreferences.cpp

FORMS += $${PWD}/drugspreferences/drugsextraoptionspage.ui \
    $${PWD}/drugspreferences/drugsviewoptionspage.ui \
    $${PWD}/drugspreferences/drugsuseroptionspage.ui \
    $${PWD}/drugspreferences/drugsprintoptionspage.ui \
    $${PWD}/drugspreferences/databaseselectorwidget.ui \
    $${PWD}/drugspreferences/drugselectorwidget.ui \
    $${PWD}/drugspreferences/protocolpreferencespage.ui \
    $${PWD}/drugspreferences/drugenginespreferences.ui

# DrugsWidgets
HEADERS += $${PWD}/drugswidget/druginfo.h \
    $${PWD}/drugswidget/druginfo_p.h \
    $${PWD}/drugswidget/drugselector.h \
    $${PWD}/drugswidget/prescriptionviewer.h \
    $${PWD}/drugswidget/drugscentralwidget.h \
    $${PWD}/drugswidget/textualprescriptiondialog.h \
    $${PWD}/drugswidget/dailyschemeviewer.h \
    $${PWD}/drugswidget/interactionsynthesisdialog.h \
    $${PWD}/drugswidget/dynamicalert.h
#    $${PWD}/drugswidget/druginteractionreport.h \

SOURCES += $${PWD}/drugswidget/druginfo.cpp \
    $${PWD}/drugswidget/drugselector.cpp \
    $${PWD}/drugswidget/prescriptionviewer.cpp \
    $${PWD}/drugswidget/drugscentralwidget.cpp \
    $${PWD}/drugswidget/textualprescriptiondialog.cpp \
    $${PWD}/drugswidget/dailyschemeviewer.cpp \
    $${PWD}/drugswidget/interactionsynthesisdialog.cpp \
    $${PWD}/drugswidget/dynamicalert.cpp
#    $${PWD}/drugswidget/druginteractionreport.cpp \

FORMS += $${PWD}/drugswidget/druginfo.ui \
    $${PWD}/drugswidget/drugselector.ui \
    $${PWD}/drugswidget/prescriptionviewer.ui \
    $${PWD}/drugswidget/drugscentralwidget.ui \
    $${PWD}/drugswidget/textualprescriptiondialog.ui \
    $${PWD}/drugswidget/dailyschemeviewer.ui \
    $${PWD}/drugswidget/interactionsynthesisdialog.ui \
    $${PWD}/drugswidget/dynamicalert.ui
#    $${PWD}/drugswidget/druginteractionreport.ui \

# translations
TRANSLATIONS += $${SOURCES_TRANSLATIONS_PATH}/mfDrugsWidget_fr.ts \
    $${SOURCES_TRANSLATIONS_PATH}/mfDrugsWidget_de.ts \
    $${SOURCES_TRANSLATIONS_PATH}/mfDrugsWidget_es.ts
