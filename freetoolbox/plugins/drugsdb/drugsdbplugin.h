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
 *       NAME <MAIL@ADDRESS.COM>                                           *
 ***************************************************************************/
#ifndef FREEICD_DRUGSDBPLUGIN_H
#define FREEICD_DRUGSDBPLUGIN_H

#include <extensionsystem/iplugin.h>

/**
 * \file drugsdbplugin.h
 * \author Eric MAEKER <eric.maeker@gmail.com>
 * \version 0.1.0
 * \date 27 Oct 2010
*/


namespace DrugsDB {
namespace Internal {

class DrugsDbPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
public:
    DrugsDbPlugin();
    ~DrugsDbPlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();

    ExtensionSystem::IPlugin::ShutdownFlag aboutToShutdown();

};

} // namespace Internal
} // namespace DrugsDbCreator

#endif // FREEICD_COREPLUGIN_H
