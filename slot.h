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

#ifndef SLOT_H
#define SLOT_H

#include <QColor>
#include <QUuid>
#include <memory>

QT_BEGIN_NAMESPACE
class QSettings;
QT_END_NAMESPACE

namespace Audio {
class IChannel;
} // namespace Audio

namespace Slots {

namespace Internal {

class SlotManager;

class Slot
{
public:
    ~Slot();

    void load();
    void save();
    void play();
    void stop();
    bool isPlaying();

    QString title() const;
    void setTitle(QString title);
    QString fileName() const;
    void setFileName(QString fileName);
    QString driver() const;
    void setDriver(QString driver);
    int device() const;
    void setDevice(int device);
    int channel() const;
    void setChannel(int channel);
    QColor backgroundColor() const;
    void setBackgroundColor(QColor color);
    int fontSize() const;
    void setFontSize(int size);
    QColor fontColor() const;
    void setFontColor(QColor color);

    bool exists() const;
    void initializeOutput();
    Audio::IChannel& output() const;

private:
    Slot(QUuid id);

    static QSettings *settings();

    QUuid m_id;
    QString m_title;
    QString m_fileName;
    QString m_driver;
    int m_device;
    int m_channel;
    QColor m_backgroundColor;
    int m_fontSize;
    QColor m_fontColor;

    bool m_exists;

    std::unique_ptr<Audio::IChannel> m_output;

    friend class Slots::Internal::SlotManager;
};

} // namespace Internal
} // namespace Slots

#endif // SLOT_H
