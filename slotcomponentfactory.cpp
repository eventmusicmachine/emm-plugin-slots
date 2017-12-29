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

#include "slotcomponentfactory.h"
#include "slotcomponentwidget.h"

using namespace Slots;
using namespace Slots::Internal;

QString SlotComponentFactory::displayName() const
{
    return tr("Slots");
}

QWidget *SlotComponentFactory::createComponent(QWidget *parent)
{
    return new SlotComponentWidget(parent);
}
