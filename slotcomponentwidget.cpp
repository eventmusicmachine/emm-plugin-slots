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
#include <QUuid>
#include <extensionsystem/pluginmanager.h>

#include "slotcomponentwidget.h"
#include "ui_slotcomponentwidget.h"
#include "slotwidget.h"
#include "slot.h"
#include "layerselectiontoolbar.h"

using namespace Slots::Internal;

SlotComponentWidget::SlotComponentWidget(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::SlotComponentWidget)
{
    m_ui->setupUi(this);

    QFile styleFile(":/slots/qss/default.qss");
    styleFile.open(QFile::ReadOnly);
    this->setStyleSheet(QString(styleFile.readAll()));
    styleFile.close();

    LayerSelectionToolbar *layerSelector = new LayerSelectionToolbar(this);
    m_ui->slotComponentLayout->insertWidget(0, layerSelector);

    connect(layerSelector, &LayerSelectionToolbar::layerSelected, this, &SlotComponentWidget::updateLayer);

    updateWidgets();
    layerSelector->map();
}

SlotComponentWidget::~SlotComponentWidget()
{
    delete m_ui;
}

void SlotComponentWidget::updateWidgets()
{
    QSettings *settings = ExtensionSystem::PluginManager::instance()->settings();

    int oldColumns = m_ui->slotLayout->columnCount();
    int oldRows = m_ui->slotLayout->rowCount();
    int newColumns = settings->value("slots/columns", 10).toInt();
    int newRows = settings->value("slots/rows", 10).toInt();

    // Remove widgets which are not neeeded anymore
    for (int i = newColumns; i < oldColumns; i++) {
        for (int j = newRows; j < oldRows; j++) {
            QLayoutItem *item = m_ui->slotLayout->itemAtPosition(j, i);
            if (item) {
                QWidget *widget = item->widget();
                if (widget) {
                    // remove widget also deletes item
                    m_ui->slotLayout->removeWidget(widget);
                } else {
                    m_ui->slotLayout->removeItem(item);
                    delete item;
                }
            }
        }
    }

    // Add new widgets as needed
    for (int i = 0; i < newColumns; i++) {
        for (int j = 0; j < newRows; j++) {
            QLayoutItem *item = m_ui->slotLayout->itemAtPosition(j, i);
            if (item == 0) {
                SlotWidget *widget = new SlotWidget(j, i, this);
                widget->updateSlot(m_selectedLayerId);
                connect(this, &SlotComponentWidget::layerSelected, widget, &SlotWidget::updateSlot);
                m_ui->slotLayout->addWidget(widget, j, i);
            }
        }
    }
}

void SlotComponentWidget::updateLayer(QString layerId)
{
    m_selectedLayerId = QUuid::fromString(layerId);
    m_ui->stackedWidget->setCurrentIndex(1);
    emit layerSelected(m_selectedLayerId);
}
