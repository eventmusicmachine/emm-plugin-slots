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

#ifndef GENERALSETTINGSWIDGET_H
#define GENERALSETTINGSWIDGET_H

#include <QWidget>

namespace Slots {

namespace Internal {

class GeneralSettingsPage;
class LayersTableModel;
class Layer;

namespace Ui {

class GeneralSettingsWidget;

} //namespace Ui

class GeneralSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralSettingsWidget(QWidget *parent = 0);
    ~GeneralSettingsWidget();

    void apply();
    void load();

private slots:
    void layerCountChanged(int layers);
    void rowCountChanged(int rows);
    void columnCountChanged(int columns);

private:
    void updateLayers();

    Ui::GeneralSettingsWidget *m_ui;
    QList<Layer*> m_layers;
    LayersTableModel *m_layersModel;
    int m_layerCount;
    int m_rowCount;
    int m_columnCount;
};

} // namespace Internal
} // namespace Slots

#endif // GENERALSETTINGSWIDGET_H
