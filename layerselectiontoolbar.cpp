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

#include <QSignalMapper>
#include <QAction>
#include <QActionGroup>

#include "layerselectiontoolbar.h"
#include "layer.h"

using namespace Slots::Internal;

LayerSelectionToolbar::LayerSelectionToolbar(QWidget *parent) :
    QToolBar(parent),
    m_mapper(new QSignalMapper(this)),
    m_actionGroup(new QActionGroup(this))
{
    updateLayers();

    connect(m_mapper, QOverload<const QString&>::of(&QSignalMapper::mapped), this, &LayerSelectionToolbar::layerSelected);

    if (actions().length() > 0) {
        actions().first()->setChecked(true);
        m_mapper->map(actions().first());
    }
}

LayerSelectionToolbar::~LayerSelectionToolbar()
{
    delete m_mapper;
    delete m_actionGroup;
}

void LayerSelectionToolbar::map()
{
    m_mapper->map(m_actionGroup->checkedAction());
}

void LayerSelectionToolbar::updateLayers()
{
    foreach (QAction* action, m_actions) {
        this->removeAction(action);
        m_actionGroup->removeAction(action);
        m_actions.removeOne(action);
        delete action;
    }

    QList<Layer*> layers = Layer::readLayers();
    foreach (Layer *layer, layers) {
        QAction *action = new QAction(layer->name());
        action->setCheckable(true);
        action->setVisible(layer->visible());
        m_actionGroup->addAction(action);
        m_mapper->setMapping(action, layer->id().toString());
        this->addAction(action);
        connect(action, &QAction::triggered, m_mapper, QOverload<>::of(&QSignalMapper::map));
    }
}
