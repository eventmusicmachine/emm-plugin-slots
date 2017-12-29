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

#include "layertablemodel.h"
#include "layer.h"

using namespace Slots::Internal;

int LayersTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_layers.length();
}

int LayersTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return 2;
}

QVariant LayersTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        case 0:
            return tr("Name");
        case 1:
            return tr("Visible");
        }
    }
    return QVariant();
}

QVariant LayersTableModel::data(const QModelIndex &index, int role) const
{
    if ((role == Qt::DisplayRole || role == Qt::EditRole) && index.column() == 0) {
        return m_layers.at(index.row())->name();
    } else if (role == Qt::CheckStateRole && index.column() == 1) {
        if (m_layers.at(index.row())->visible()) {
            return Qt::Checked;
        } else {
            return Qt::Unchecked;
        }
    }
    return QVariant();
}

bool LayersTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Layer *layer = m_layers.at(index.row());
    if (role == Qt::EditRole && index.column() == 0) {
        layer->setName(value.toString());
    } else if (role == Qt::CheckStateRole && index.column() == 1) {
        layer->setVisible(value.toBool());
    }
    return true;
}

Qt::ItemFlags LayersTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractTableModel::flags(index);

    if (index.isValid()) {
        switch (index.column()) {
        case 0:
            return Qt::ItemIsEditable | defaultFlags;
        case 1:
            return Qt::ItemIsUserCheckable | defaultFlags;
        }
    }

    return defaultFlags;
}

void LayersTableModel::setLayers(QList<Layer *> layers)
{
    m_layers = layers;
    emit layoutChanged();
}
