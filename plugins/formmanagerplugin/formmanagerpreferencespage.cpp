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
#include "formmanagerpreferencespage.h"
#include "formfilesselectorwidget.h"
#include "episodebase.h"
#include "iformio.h"
#include "formmanager.h"
#include "constants_db.h"
#include "constants_settings.h"

#include <coreplugin/icore.h>
#include <coreplugin/isettings.h>
#include <coreplugin/constants_tokensandsettings.h>

#include <translationutils/constanttranslations.h>

#include <QHBoxLayout>

#include <QDebug>

#include "ui_formmanagerpreferenceswidget.h"
#include "ui_formpreferenceswidget.h"

using namespace Form;
using namespace Internal;
using namespace Trans::ConstantTranslations;

static inline Core::ISettings *settings() { return Core::ICore::instance()->settings(); }
static inline Form::Internal::EpisodeBase *episodeBase() {return Form::Internal::EpisodeBase::instance();}
static inline Form::FormManager *formManager() {return Form::FormManager::instance();}


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////    FormFileSelector    ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
FormPreferencesFileSelectorPage::FormPreferencesFileSelectorPage(QObject *parent) :
        IOptionsPage(parent), m_Widget(0)
{ setObjectName("FormPreferencesFileSelectorPage"); }

FormPreferencesFileSelectorPage::~FormPreferencesFileSelectorPage()
{
    if (m_Widget) delete m_Widget;
    m_Widget = 0;
}

QString FormPreferencesFileSelectorPage::id() const { return objectName(); }
QString FormPreferencesFileSelectorPage::name() const { return tkTr(Trans::Constants::SELECTOR); }
QString FormPreferencesFileSelectorPage::category() const { return tkTr(Trans::Constants::FORMS); }
QString FormPreferencesFileSelectorPage::title() const {return tr("Patient file form selector");}

void FormPreferencesFileSelectorPage::resetToDefaults()
{
    m_Widget->writeDefaultSettings(settings());
}

void FormPreferencesFileSelectorPage::applyChanges()
{
    if (!m_Widget) {
        return;
    }
    m_Widget->saveToSettings(settings());
}

void FormPreferencesFileSelectorPage::finish() { delete m_Widget; }

void FormPreferencesFileSelectorPage::checkSettingsValidity()
{
//    QHash<QString, QVariant> defaultvalues;
//    defaultvalues.insert(Utils::Constants::S_CHECKUPDATE, Utils::UpdateChecker::Check_AtStartup);
//    defaultvalues.insert(Core::Constants::S_USE_EXTERNAL_DATABASE, false);
//
//    foreach(const QString &k, defaultvalues.keys()) {
//        if (settings()->value(k) == QVariant())
//            settings()->setValue(k, defaultvalues.value(k));
//    }
//    settings()->sync();
}

QWidget *FormPreferencesFileSelectorPage::createPage(QWidget *parent)
{
    if (m_Widget)
        delete m_Widget;
    m_Widget = new FormPreferencesFileSelectorWidget(parent);
    return m_Widget;
}


FormPreferencesFileSelectorWidget::FormPreferencesFileSelectorWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::FormPreferencesFileSelectorWidget)
{
    ui->setupUi(this);
    ui->selector->setFormType(Form::FormFilesSelectorWidget::CompleteForms);
    connect(ui->useButton, SIGNAL(pressed()), this, SLOT(saveFormToBase()));
}

FormPreferencesFileSelectorWidget::~FormPreferencesFileSelectorWidget()
{
    delete ui;
}

void FormPreferencesFileSelectorWidget::saveFormToBase()
{
    if (ui->selector->selectedForms().isEmpty())
        return;
    Form::FormIODescription *descr = ui->selector->selectedForms().at(0);
    episodeBase()->setGenericPatientFormFile(descr->data(Form::FormIODescription::UuidOrAbsPath).toString());
    formManager()->readPmhxCategories(descr->data(Form::FormIODescription::UuidOrAbsPath).toString());
}

void FormPreferencesFileSelectorWidget::saveToSettings(Core::ISettings *)
{
}

void FormPreferencesFileSelectorWidget::changeEvent(QEvent *e)
{
}


///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////    FormPreferences    ////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

FormPreferencesPage::FormPreferencesPage(QObject *parent) :
        IOptionsPage(parent), m_Widget(0)
{ setObjectName("FormPreferencesPage"); }

FormPreferencesPage::~FormPreferencesPage()
{
    if (m_Widget) delete m_Widget;
    m_Widget = 0;
}

QString FormPreferencesPage::id() const { return objectName(); }
QString FormPreferencesPage::name() const { return tkTr(Trans::Constants::VIEWER); }
QString FormPreferencesPage::category() const { return tkTr(Trans::Constants::FORMS); }
QString FormPreferencesPage::title() const {return tr("Form and episode tree viewer");}

void FormPreferencesPage::resetToDefaults()
{
    QHash<QString, QVariant> defaultvalues;
    defaultvalues.insert(Constants::S_USEALTERNATEROWCOLOR, true);
    defaultvalues.insert(Constants::S_USESPECIFICCOLORFORROOTS, true);
    defaultvalues.insert(Constants::S_FOREGROUNDCOLORFORROOTS, "maroon");
    defaultvalues.insert(Constants::S_EPISODELABELCONTENT, QString("[[%1]]").arg(Constants::T_LABEL));
    defaultvalues.insert(Constants::S_EPISODEMODEL_LONGDATEFORMAT, QLocale().dateTimeFormat(QLocale::ShortFormat));
    defaultvalues.insert(Constants::S_EPISODEMODEL_SHORTDATEFORMAT, QLocale().dateFormat(QLocale::ShortFormat));
    defaultvalues.insert(Constants::S_EPISODEMODEL_EPISODE_FOREGROUND, "darkblue");
    defaultvalues.insert(Constants::S_EPISODEMODEL_FORM_FOREGROUND, "dark");

    foreach(const QString &k, defaultvalues.keys()) {
        settings()->setValue(k, defaultvalues.value(k));
    }
    if (m_Widget)
        m_Widget->setupUiData();
}

void FormPreferencesPage::applyChanges()
{
    if (!m_Widget) {
        return;
    }
    m_Widget->saveToSettings(settings());
}

void FormPreferencesPage::finish() { delete m_Widget; }

void FormPreferencesPage::checkSettingsValidity()
{
    QHash<QString, QVariant> defaultvalues;
    defaultvalues.insert(Constants::S_USEALTERNATEROWCOLOR, true);
    defaultvalues.insert(Constants::S_USESPECIFICCOLORFORROOTS, true);
    defaultvalues.insert(Constants::S_FOREGROUNDCOLORFORROOTS, "maroon");
    defaultvalues.insert(Constants::S_EPISODELABELCONTENT, QString("[[%1]]").arg(Constants::T_LABEL));
    defaultvalues.insert(Constants::S_EPISODEMODEL_LONGDATEFORMAT, QLocale().dateTimeFormat(QLocale::ShortFormat));
    defaultvalues.insert(Constants::S_EPISODEMODEL_SHORTDATEFORMAT, QLocale().dateFormat(QLocale::ShortFormat));
    defaultvalues.insert(Constants::S_EPISODEMODEL_EPISODE_FOREGROUND, "darkblue");
    defaultvalues.insert(Constants::S_EPISODEMODEL_FORM_FOREGROUND, "dark");

    foreach(const QString &k, defaultvalues.keys()) {
        if (settings()->value(k) == QVariant())
            settings()->setValue(k, defaultvalues.value(k));
    }
}

QWidget *FormPreferencesPage::createPage(QWidget *parent)
{
    if (m_Widget)
        delete m_Widget;
    m_Widget = new FormPreferencesWidget(parent);
    return m_Widget;
}


FormPreferencesWidget::FormPreferencesWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::FormPreferencesWidget)
{
    ui->setupUi(this);
    ui->episodeLabelContent->addItem(tr("Label"), QString("[[%1]]").arg(Constants::T_LABEL));
    ui->episodeLabelContent->addItem(tr("Label - User date (small)"), QString("[[%1]] - [[%2]]").arg(Constants::T_LABEL).arg(Constants::T_SMALLDATE));
    ui->episodeLabelContent->addItem(tr("Label - User date (full)"), QString("[[%1]] - [[%2]]").arg(Constants::T_LABEL).arg(Constants::T_FULLDATE));
    ui->episodeLabelContent->addItem(tr("User date (small)"), QString("[[%1]]").arg(Constants::T_SMALLDATE));
    ui->episodeLabelContent->addItem(tr("User date (full)"), QString("[[%1]]").arg(Constants::T_FULLDATE));
    ui->episodeLabelContent->addItem(tr("User date (small) - Label"), QString("[[%1]][ - [%2]]").arg(Constants::T_SMALLDATE).arg(Constants::T_LABEL));
    ui->episodeLabelContent->addItem(tr("User date (full) - Label"), QString("[[%1]][ - [%2]]").arg(Constants::T_FULLDATE).arg(Constants::T_LABEL));

    setupUiData();
}

FormPreferencesWidget::~FormPreferencesWidget()
{
    delete ui;
}

void FormPreferencesWidget::setupUiData()
{
    ui->useSpecificBackgroundRootForms->setChecked(settings()->value(Constants::S_USESPECIFICCOLORFORROOTS).toBool());
    ui->rootBackgroundButton->setColor(QColor(settings()->value(Constants::S_FOREGROUNDCOLORFORROOTS).toString()));
    ui->useAlternateRowColor->setChecked(settings()->value(Constants::S_USEALTERNATEROWCOLOR).toBool());
    ui->episodeLabelContent->setCurrentIndex(ui->episodeLabelContent->findData(settings()->value(Constants::S_EPISODELABELCONTENT).toString(), Qt::UserRole));
    ui->defaultFormForegroundColor->setColor(QColor(settings()->value(Constants::S_EPISODEMODEL_FORM_FOREGROUND).toString()));
    ui->episodeForegroundColor->setColor(QColor(settings()->value(Constants::S_EPISODEMODEL_EPISODE_FOREGROUND).toString()));
    ui->longDateFormat->setText(settings()->value(Constants::S_EPISODEMODEL_LONGDATEFORMAT).toString());
    ui->shortDateFormat->setText(settings()->value(Constants::S_EPISODEMODEL_SHORTDATEFORMAT).toString());
}

void FormPreferencesWidget::saveToSettings(Core::ISettings *)
{
    settings()->setValue(Constants::S_USESPECIFICCOLORFORROOTS, ui->useSpecificBackgroundRootForms->isChecked());
    settings()->setValue(Constants::S_FOREGROUNDCOLORFORROOTS, ui->rootBackgroundButton->color().name());
    settings()->setValue(Constants::S_USEALTERNATEROWCOLOR, ui->useAlternateRowColor->isChecked());
    settings()->setValue(Constants::S_EPISODELABELCONTENT, ui->episodeLabelContent->itemData(ui->episodeLabelContent->currentIndex()));
    settings()->setValue(Constants::S_EPISODEMODEL_FORM_FOREGROUND, ui->defaultFormForegroundColor->color().name());
    settings()->setValue(Constants::S_EPISODEMODEL_EPISODE_FOREGROUND, ui->episodeForegroundColor->color().name());
    settings()->setValue(Constants::S_EPISODEMODEL_LONGDATEFORMAT, ui->longDateFormat->text());
    settings()->setValue(Constants::S_EPISODEMODEL_SHORTDATEFORMAT, ui->shortDateFormat->text());
    settings()->setValue(Constants::S_EPISODELABELCONTENT, ui->episodeLabelContent->itemData(ui->episodeLabelContent->currentIndex()));
}

void FormPreferencesWidget::changeEvent(QEvent *e)
{
}

