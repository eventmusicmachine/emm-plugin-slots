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

#ifndef GENERALSETTINGSPAGE_H
#define GENERALSETTINGSPAGE_H

#include <QObject>
#include <settings/isettingspage.h>

namespace Slots {

namespace Internal {

class LayersTableModel;
class Layer;

namespace Ui {

class GeneralSettingsPage;

} //namespace Ui

class GeneralSettingsPage : public Settings::ISettingsPage
{
    Q_OBJECT
public:
    GeneralSettingsPage();
    ~GeneralSettingsPage();

    QString id() const override;

    void load() override;
    void apply() override;

private slots:
    void rowCountChanged(int rows);
    void columnCountChanged(int columns);
    void addLayer();
    void removeLayer();

private:
    Ui::GeneralSettingsPage *m_ui;
    QList<Layer*> m_layers;
    LayersTableModel *m_layersModel;
    int m_rowCount;
    int m_columnCount;
};

}
} // namespace Slots

#endif // GENERALSETTINGSPAGE_H
