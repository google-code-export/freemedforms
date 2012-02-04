/***************************************************************************
 *  The FreeMedForms project is a set of free, open source medical         *
 *  applications.                                                          *
 *  (C) 2008-2012 by Eric MAEKER, MD (France) <eric.maeker@gmail.com>      *
 *  All rights reserved.                                                   *
 *                                                                         *
 *  This program is free software: you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with this program (COPYING.FREEMEDFORMS file).                   *
 *  If not, see <http://www.gnu.org/licenses/>.                            *
 ***************************************************************************/
/***************************************************************************
 *   Main Developper : Eric MAEKER, <eric.maeker@gmail.com>                *
 *   Contributors :                                                        *
 *       NAME <MAIL@ADRESS>                                                *
 *       NAME <MAIL@ADRESS>                                                *
 ***************************************************************************/
#ifndef PRINTERPREFERENCES_H
#define PRINTERPREFERENCES_H

#include <coreplugin/ioptionspage.h>

#include "ui_printerpreferences.h"

#include <QPointer>
#include <QObject>

/**
 * \file printerpreferences.h
 * \author Eric MAEKER <eric.maeker@gmail.com>
 * \version 0.3.0
 * \date 30 Jan 2010
*/

namespace Core {
class ISettings;
}

namespace Print {
namespace Internal {

class PrinterPreferencesWidget : public QWidget, private Ui::PrinterPreferences
{
    Q_OBJECT
    Q_DISABLE_COPY(PrinterPreferencesWidget)

public:
    explicit PrinterPreferencesWidget(QWidget *parent = 0);
    void setDatasToUi();

    static void writeDefaultSettings(Core::ISettings *s);

public Q_SLOTS:
    void saveToSettings(Core::ISettings *s = 0);
    void on_selectFolderButton_clicked();

protected:
    virtual void changeEvent(QEvent *e);
};


class PrinterPreferencesPage : public Core::IOptionsPage
{
    Q_OBJECT
public:
    PrinterPreferencesPage(QObject *parent = 0);
    ~PrinterPreferencesPage();

    QString id() const;
    QString name() const;
    QString category() const;
    QString title() const;

    void resetToDefaults();
    void checkSettingsValidity();
    void applyChanges();
    void finish();

    QString helpPage() {return "parametrer.html";}

    static void writeDefaultSettings(Core::ISettings *s) {PrinterPreferencesWidget::writeDefaultSettings(s);}

    QWidget *createPage(QWidget *parent = 0);
private:
    QPointer<PrinterPreferencesWidget> m_Widget;
};

}  // End Internal
}  // End Printer

#endif // PRINTERPREFERENCES_H
