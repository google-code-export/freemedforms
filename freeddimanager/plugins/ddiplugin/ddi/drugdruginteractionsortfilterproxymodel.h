/***************************************************************************
 *  The FreeMedForms project is a set of free, open source medical         *
 *  applications.                                                          *
 *  (C) 2008-2014 by Eric MAEKER, MD (France) <eric.maeker@gmail.com>      *
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
 *  Main Developer: Eric MAEKER, MD <eric.maeker@gmail.com>                *
 *  Contributors:                                                          *
 *       NAME <MAIL@ADDRESS.COM>                                           *
 *       NAME <MAIL@ADDRESS.COM>                                           *
 ***************************************************************************/
#ifndef DDIMANAGER_DDIPLUGIN_DRUGDRUGINTERACTIONSORTFILTERPROXYMODEL_H
#define DDIMANAGER_DDIPLUGIN_DRUGDRUGINTERACTIONSORTFILTERPROXYMODEL_H

#include <ddiplugin/ddi_exporter.h>
#include <QSortFilterProxyModel>

/**
 * \file drugdruginteractionsortfilterproxymodel.h
 * \author Eric Maeker
 * \version 0.10.0
 * \date 21 Oct 2013
*/

namespace DDI {
class DDI_EXPORT DrugDrugInteractionSortFilterProxyModel : public QSortFilterProxyModel
{
public:
    explicit DrugDrugInteractionSortFilterProxyModel(QObject *parent = 0);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &parent) const;
};
}  // namespace DDI

#endif // DDIMANAGER_DDIPLUGIN_DRUGDRUGINTERACTIONSORTFILTERPROXYMODEL_H
