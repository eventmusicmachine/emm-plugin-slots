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

#include <QMouseEvent>

#include "slotwidget.h"
#include "ui_slotwidget.h"
#include "slot.h"
#include "slotconfigurationdialog.h"

using namespace Slots::Internal;

SlotWidget::SlotWidget(int row, int column, QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::SlotWidget)
{
    m_ui->setupUi(this);
    m_row = row;
    m_column = column;
}

SlotWidget::~SlotWidget()
{
    delete m_ui;
}

void SlotWidget::updateSlot(QUuid layerId)
{
    if (layerId == 0) {
        return;
    }
    m_slot = Slot::create(layerId, m_row, m_column);
    if (m_slot) {
        QFont font = m_ui->titleLabel->font();
        font.setPointSize(m_slot->fontSize());

        m_ui->stackedWidget->setCurrentIndex(m_slot->exists() ? 1 : 0);
        m_ui->playerPage->setStyleSheet("#playerPage { background-color: " + m_slot->backgroundColor().name() + " }");
        m_ui->titleLabel->setText(m_slot->title());
        m_ui->titleLabel->setStyleSheet("#titleLabel { color: " + m_slot->fontColor().name() + " }");
        m_ui->titleLabel->setFont(font);
    }
}

void SlotWidget::config()
{
    SlotConfigurationDialog dialog(m_slot, this);
    dialog.exec();
}

void SlotWidget::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::RightButton) {
        config();
    }
}

