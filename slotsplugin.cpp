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

#include <extensionsystem/pluginmanager.h>
#include <settings/settingsmanager.h>
#include <settings/navigationtreeitem.h>

#include "slotsplugin.h"
#include "slotcomponentfactory.h"
#include "generalsettingsfactory.h"

using namespace Slots;
using namespace Slots::Internal;

SlotsPlugin::SlotsPlugin()
{

}

SlotsPlugin::~SlotsPlugin()
{
    ExtensionSystem::PluginManager::removeObject(m_factory);
    delete m_factory;
}

bool SlotsPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    Q_UNUSED(arguments)
    Q_UNUSED(errorString)

    m_factory = new SlotComponentFactory;
    ExtensionSystem::PluginManager::addObject(m_factory);
    Settings::NavigationTreeItem *settingsItem = Settings::SettingsManager::createNavigationNode("SLOTS", tr("Cart Slots"));
    settingsItem->setFactory(new GeneralSettingsFactory());
    Settings::SettingsManager::navigationNode("ROOT")->addChild(settingsItem);

    return true;
}

void SlotsPlugin::extensionsInitialized()
{
}

ExtensionSystem::IPlugin::ShutdownFlag SlotsPlugin::aboutToShutdown()
{
    return SynchronousShutdown;
}
