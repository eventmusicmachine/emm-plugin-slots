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

#include <QFile>
#include <QStandardPaths>
#include <QStandardPaths>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include "layer.h"

using namespace Slots::Internal;

Layer::Layer()
{
    m_id = QUuid::createUuid();
}

QUuid Layer::id() const
{
    return m_id;
}

void Layer::setName(const QString name)
{
    m_name = name;
}

QString Layer::name() const
{
    return m_name;
}

int Layer::position() const
{
    return m_position;
}

void Layer::setVisible(const bool visible)
{
    m_visible = visible;
}

bool Layer::visible() const
{
    return m_visible;
}

void Layer::saveLayers(QList<Layer*> layers)
{
    QFile settingsFile(settingsPath());
    if (settingsFile.open(QIODevice::ReadWrite)) {

        QXmlStreamWriter xmlWriter(&settingsFile);
        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("layers");

        for (int i = 0; i < layers.count(); i++) {
            Layer *layer = layers.at(i);
            xmlWriter.writeStartElement("layer");
            xmlWriter.writeAttribute("id", layer->id().toString());
            xmlWriter.writeAttribute("position", QString::number(i));
            xmlWriter.writeTextElement("name", layer->name());
            xmlWriter.writeTextElement("visible", layer->visible() ? "true" : "false");
            xmlWriter.writeEndElement();
        }

        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();

        settingsFile.close();
    } else {
        // TODO handle error
        QString test1 = settingsFile.errorString();
        QFileDevice::FileError error = settingsFile.error();
        QString test2 = "lalala";
    }
}

QList<Layer*> Layer::readLayers()
{
    QFile layersFile(settingsPath());
    QList<Layer*> layers;

    if (!layersFile.open(QFile::ReadOnly)) {
        return layers;
    }

    QXmlStreamReader reader(&layersFile);

    if (reader.readNextStartElement() && reader.name() == "layers") {
        while (reader.readNextStartElement()) {
            if (reader.name() == "layer") {
                Layer *layer = new Layer();
                foreach(const QXmlStreamAttribute &attr, reader.attributes()) {
                    if (attr.name().toString() == "id") {
                        layer->m_id = QUuid(attr.value().toString());
                    } else if (attr.name().toString() == "position") {
                        layer->m_position = attr.value().toInt();
                    }
                }
                while (reader.readNextStartElement()) {
                    if (reader.name() == "name") {
                        layer->m_name = reader.readElementText();
                    } else if (reader.name() == "visible") {
                        layer->m_visible = reader.readElementText() == "true";
                    } else {
                        reader.skipCurrentElement();
                    }
                }
                layers.append(layer);
            } else {
                reader.skipCurrentElement();
            }
        }
    }

    layersFile.close();

    return layers;
}

QString Layer::settingsPath()
{
    QString settingsPath = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation);
    settingsPath += "/EMM/layers.xml";
    return settingsPath;
}
