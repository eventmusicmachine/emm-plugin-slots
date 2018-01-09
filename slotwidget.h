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

#ifndef SLOTWIDGET_H
#define SLOTWIDGET_H

#include <QWidget>
#include <QUuid>

namespace Slots {

namespace Internal {

class Slot;
class SlotConfigurationDialog;

namespace Ui {

class SlotWidget;

} // namespace Ui

class SlotWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SlotWidget(int row, int column, QWidget *parent = 0);
    ~SlotWidget();

public slots:
    void updateSlot(QUuid layerId);

protected:
    void mousePressEvent(QMouseEvent *);

private:
    void config();

    Ui::SlotWidget *m_ui;
    Slot *m_slot;
    int m_row;
    int m_column;
};

} // namespace Internal
} // namespace Slots

#endif // SLOTWIDGET_H
