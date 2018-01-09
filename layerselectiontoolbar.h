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

#ifndef LAYERSELECTIONTOOLBAR_H
#define LAYERSELECTIONTOOLBAR_H

#include <QToolBar>

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QSignalMapper;
QT_END_NAMESPACE

namespace Slots {

namespace Internal {

class LayerSelectionToolbar : public QToolBar
{
    Q_OBJECT
public:
    explicit LayerSelectionToolbar(QWidget *parent = nullptr);
    ~LayerSelectionToolbar();

    void map();

private:
    void updateLayers();

    QSignalMapper *m_mapper;
    QActionGroup *m_actionGroup;
    QList<QAction*> m_actions;

signals:
    void layerSelected(const QString &id);
};

} // namespace Internal
} // namespace Slots

#endif // LAYERSELECTIONTOOLBAR_H
