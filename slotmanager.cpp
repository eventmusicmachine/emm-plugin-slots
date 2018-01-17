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

#include "slotmanager.h"

using namespace Slots::Internal;

static SlotManager *m_instance;

SlotManager::SlotManager() : QObject()
{
    m_instance = this;
}

SlotManager *SlotManager::instance()
{
    return m_instance;
}

std::shared_ptr<Slot> SlotManager::createSlot(QUuid layerId, int row, int column)
{
    QUuid slotId = QUuid::createUuidV3(layerId, QString::number(row) + "-" + QString::number(column));

    if (m_slots.contains(slotId)) {
        return m_slots.value(slotId);
    }

    std::shared_ptr<Slot> slot = std::shared_ptr<Slot>(new Slot(slotId));
    m_slots.insert(slotId, slot);
    return slot;
}
