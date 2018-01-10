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

#include <QSettings>
#include <extensionsystem/pluginmanager.h>

#include "generalsettingspage.h"
#include "ui_generalsettingspage.h"
#include "layertablemodel.h"
#include "layer.h"

using namespace Slots::Internal;

GeneralSettingsPage::GeneralSettingsPage() :
    Settings::ISettingsPage(),
    m_ui(new Ui::GeneralSettingsPage),
    m_layersModel(new LayersTableModel)
{
    m_ui->setupUi(this);
    m_ui->layersTableView->setModel(m_layersModel);
    m_ui->layersTableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    m_ui->layersTableView->setColumnWidth(1, 55);
    m_ui->layersTableView->setAcceptDrops(true);
    connect(m_ui->layersSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &GeneralSettingsPage::layerCountChanged);
    connect(m_ui->rowsSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &GeneralSettingsPage::rowCountChanged);
    connect(m_ui->columnsSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &GeneralSettingsPage::columnCountChanged);
}

GeneralSettingsPage::~GeneralSettingsPage()
{
    delete m_ui;
    delete m_layersModel;
    qDeleteAll(m_layers);
}

QString GeneralSettingsPage::id() const
{
    return "SlotsGeneralSettings";
}

void GeneralSettingsPage::load()
{
    QSettings *settings = ExtensionSystem::PluginManager::instance()->settings();
    m_layerCount = settings->value("slots/layers", 1).toInt();
    m_rowCount = settings->value("slots/rows", 10).toInt();
    m_columnCount = settings->value("slots/columns", 10).toInt();
    updateLayers();

    m_ui->layersSpinBox->setValue(m_layerCount);
    m_ui->rowsSpinBox->setValue(m_rowCount);
    m_ui->columnsSpinBox->setValue(m_columnCount);
    m_layersModel->setLayers(m_layers);
}

void GeneralSettingsPage::apply()
{
    QSettings *settings = ExtensionSystem::PluginManager::instance()->settings();
    settings->setValue("slots/layers", m_layerCount);
    settings->setValue("slots/rows", m_rowCount);
    settings->setValue("slots/columns", m_columnCount);

    Layer::saveLayers(m_layers);
}

void GeneralSettingsPage::layerCountChanged(int layers)
{
    m_layerCount = layers;
    updateLayers();
}

void GeneralSettingsPage::rowCountChanged(int rows)
{
    m_rowCount = rows;
}

void GeneralSettingsPage::columnCountChanged(int columns)
{
    m_columnCount = columns;
}

void GeneralSettingsPage::updateLayers()
{
    QList<Layer*> layers = Layer::readLayers();

    while (layers.length() > m_layerCount) {
        layers.takeLast();
    }

    while (m_layerCount > layers.length()) {
        Layer *layer = new Layer();
        layer->setName(QString(tr("Layer %1")).arg(layers.length() + 1));
        layer->setVisible(true);
        layers.append(layer);
    }

    m_layersModel->setLayers(layers);
    qDeleteAll(m_layers);
    m_layers = layers;
}
