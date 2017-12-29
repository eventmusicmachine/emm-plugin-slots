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

#ifndef LAYER_H
#define LAYER_H

#include <QString>
#include <QUuid>

namespace Slots {

namespace Internal {

class Layer
{
public:
    Layer();

    QUuid id() const;

    void setName(const QString name);
    QString name() const;

    int position() const;

    void setVisible(const bool visible);
    bool visible() const;

    static void saveLayers(QList<Layer*> layers);
    static QList<Layer*> readLayers();

private:
    QUuid m_id;
    QString m_name;
    int m_position;
    bool m_visible;

    static QString settingsPath();
};

} // namespace Internal
} // namespace Slots

#endif // LAYER_H
