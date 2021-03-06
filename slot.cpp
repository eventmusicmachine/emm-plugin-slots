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
#include <audio/devicemanager.h>
#include <audio/ichannel.h>

#include "slot.h"

using namespace Slots::Internal;

Slot::Slot(QUuid slotId)
{
    m_id = slotId;
    m_fontSize = 14;
    m_fontColor = "#cccccc";
    m_backgroundColor = "#000000";
    m_title = "No Title";
    load();
}

Slot::~Slot()
{

}

void Slot::load()
{
    QSettings *s = settings();

    m_exists = s->childGroups().contains(m_id.toString());
    if (!m_exists) {
        return;
    }

    // Read settings

    s->beginGroup(m_id.toString());

    m_title = s->value("title", "No title").toString();
    m_fileName = s->value("file", "").toString();
    m_driver = s->value("driver", "").toString();
    m_device = s->value("device", 1).toInt();
    m_channel = s->value("channel", 1).toInt();
    m_backgroundColor = QColor(s->value("backgroundColor", "#cccccc").toString());
    m_fontColor = QColor(s->value("fontColor", "#000000").toString());
    m_fontSize = s->value("fontSize", 14).toInt();

    s->endGroup();

    initializeOutput();
}

void Slot::save()
{
    QSettings *s = settings();

    s->beginGroup(m_id.toString());
    s->setValue("title", m_title);
    s->setValue("file", m_fileName);
    s->setValue("driver", m_driver);
    s->setValue("device", m_device);
    s->setValue("channel", m_channel);
    s->setValue("backgroundColor", m_backgroundColor.name());
    s->setValue("fontColor", m_fontColor.name());
    s->setValue("fontSize", m_fontSize);
    s->endGroup();
}

void Slot::initializeOutput()
{
    m_output.reset(Audio::DeviceManager::instance()->createChannel(m_driver, m_device, m_channel));

    if (!m_output) {
        return;
    }

    m_output->load(m_fileName);
}

void Slot::play()
{
    if (!m_output) {
        return;
    }

    m_output->play();
}

void Slot::stop()
{
    if (!m_output) {
        return;
    }

    m_output->stop();
}

bool Slot::isPlaying()
{
    if (!m_output) {
        return false;
    }

    return m_output->isPlaying();
}

QString Slot::title() const
{
    return m_title;
}

void Slot::setTitle(QString title)
{
    m_title = title;
}

QString Slot::fileName() const
{
    return m_fileName;
}

void Slot::setFileName(QString fileName)
{
    m_fileName = fileName;

    // Load new file n output channel
    initializeOutput();
}

QString Slot::driver() const
{
    return m_driver;
}

void Slot::setDriver(QString driver)
{
    m_driver = driver;
}

int Slot::device() const
{
    return m_device;
}

void Slot::setDevice(int device)
{
    m_device = device;
}

int Slot::channel() const
{
    return m_channel;
}

void Slot::setChannel(int channel)
{
    m_channel = channel;
}

bool Slot::exists() const
{
    return m_exists;
}

Audio::IChannel& Slot::output() const
{
    return *m_output;
}

QColor Slot::backgroundColor() const
{
    return m_backgroundColor;
}

void Slot::setBackgroundColor(QColor color)
{
    m_backgroundColor = color;
}

QColor Slot::fontColor() const
{
    return m_fontColor;
}

void Slot::setFontColor(QColor color)
{
    m_fontColor = color;
}

int Slot::fontSize() const
{
    return m_fontSize;
}

void Slot::setFontSize(int size)
{
    m_fontSize = size;
}

QSettings *Slot::settings()
{
    return new QSettings(QSettings::IniFormat, QSettings::UserScope, "EMM", "slots");
}
