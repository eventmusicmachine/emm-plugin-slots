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

#ifndef GENERALSETTINGSFACTORY_H
#define GENERALSETTINGSFACTORY_H

#include <settings/isettingspagefactory.h>
#include <settings/isettingspage.h>

#include "generalsettingspage.h"

namespace Slots {

namespace Internal {

class GeneralSettingsFactory : public Settings::ISettingsPageFactory {
public:
    Settings::ISettingsPage *createPage() {
        return new GeneralSettingsPage();
    }
};

} // namespace Internal
} // namespace Slots

#endif // GENERALSETTINGSFACTORY_H
