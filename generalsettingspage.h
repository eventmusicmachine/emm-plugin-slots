/**************************************************************************
 * Event Music Machine
 * Copyright (C) 2014-2017 Christoph Kraemer
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 **************************************************************************/

#ifndef GENERALSETTINGSPAGE_H
#define GENERALSETTINGSPAGE_H

#include <QObject>
#include <settings/isettingspage.h>

namespace Slots {

namespace Internal {

class GeneralSettingsWidget;

class GeneralSettingsPage : public Settings::ISettingsPage
{
    Q_OBJECT
public:
    QString id() const;
    QWidget *widget();

    void load();
    void apply();

private:
    GeneralSettingsWidget *m_widget;

};

}
} // namespace Slots

#endif // GENERALSETTINGSPAGE_H
