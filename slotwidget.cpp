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
#include <audio/devicemanager.h>
#include <audio/idriver.h>
#include <audio/idevice.h>
#include <audio/ichannel.h>

#include "slotwidget.h"
#include "ui_slotwidget.h"
#include "slot.h"
#include "slotmanager.h"
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

    m_slot = SlotManager::instance()->createSlot(layerId, m_row, m_column);
    if (m_slot) {
        /*Audio::IChannel output = m_slot->output();
        if (output) {
            connect(&output, &Audio::IChannel::lengthUpdated, this, &SlotWidget::lengthUpdated);
            connect(&output, &Audio::IChannel::positionChanged, this, &SlotWidget::positionChanged);
        }*/

        updateData();

        QMap<QString, Audio::IDriver*> drivers = Audio::DeviceManager::instance()->drivers();
        if (!drivers.contains(m_slot->driver())) {
            return;
        }
    }
}

void SlotWidget::updateData()
{
    QFont font = m_ui->titleLabel->font();
    font.setPointSize(m_slot->fontSize());

    m_ui->stackedWidget->setCurrentIndex(m_slot->exists() ? 1 : 0);
    m_ui->titleLabel->setText(m_slot->title());
    m_ui->titleLabel->setFont(font);

    m_ui->playerPage->setStyleSheet(" \
        #playerPage, QProgressBar::chunk { background-color: " + m_slot->backgroundColor().name() + " } \
        #titleLabel, #timeLabel { color: " + m_slot->fontColor().name() + " } \
    ");
}

void SlotWidget::lengthUpdated(float length)
{
    m_ui->progressBar->setMaximum(length);
    m_ui->progressBar->setValue(length);
    setTime(length);
}

void SlotWidget::positionChanged(float position, float length)
{
    m_ui->progressBar->setValue(length - position);
    m_ui->progressBar->repaint();
    setTime(length - position);
}

void SlotWidget::setTime(float time)
{
    int mins = time / 60;
    int secs = floor(time - mins * 60);
    int msecs = floor((time - mins * 60 - secs) * 10);

    QString timeString = QString("%1:%2.%3").arg(mins, 2, 10, QChar('0')).arg(secs, 2, 10, QChar('0')).arg(msecs);
    m_ui->timeLabel->setText(timeString);
}

void SlotWidget::config()
{
    SlotConfigurationDialog dialog(*m_slot, this);
    if(dialog.exec()) {
        updateData();
    }
}

void SlotWidget::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::RightButton) {
        config();
    } else if (e->button() == Qt::LeftButton) {
        if (m_slot->isPlaying()) {
            m_slot->stop();
        } else {
            m_slot->play();
        }
    }
}

