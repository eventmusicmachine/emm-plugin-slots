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

#ifndef SLOTCOMPONENTWIDGET_H
#define SLOTCOMPONENTWIDGET_H

#include <QWidget>
#include <QUuid>

namespace Slots {

namespace Internal {

namespace Ui {

class SlotComponentWidget;

} // namespace Ui

class SlotComponentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SlotComponentWidget(QWidget *parent = 0);
    ~SlotComponentWidget();

private:
    void updateWidgets();
    void updateLayer(QString layerId);

    Ui::SlotComponentWidget *m_ui;
    QUuid m_selectedLayerId;

signals:
    void layerSelected(QUuid layerId);

};

} // namespace Internal
} // namespace Slots


#endif // SLOTCOMPONENTWIDGET_H
