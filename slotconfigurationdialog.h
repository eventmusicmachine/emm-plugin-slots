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

#ifndef SLOTCONFIGURATIONDIALOG_H
#define SLOTCONFIGURATIONDIALOG_H

#include <QColor>
#include <QDialog>

namespace Slots {

namespace Internal {

class Slot;

namespace Ui {
class SlotConfigurationDialog;
} // namespace Ui

class SlotConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SlotConfigurationDialog(Slot& slot, QWidget *parent = 0);
    ~SlotConfigurationDialog();

private:
    void updateBackgroundLabelColor();
    void updateFontLabelColor();

    Ui::SlotConfigurationDialog *m_ui;
    Slot& m_slot;
    QColor m_backgroundColor;
    QColor m_fontColor;

private slots:
    void save();
    void selectFile();
    void selectBackgroundColor();
    void selectFontColor();
};

} // namespace Internal
} // namespace Slots

#endif // SLOTCONFIGURATIONDIALOG_H
