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

#include <QColorDialog>
#include <QFileDialog>
#include <audio/devicemanager.h>
#include <audio/idriver.h>

#include "slotconfigurationdialog.h"
#include "ui_slotconfigurationdialog.h"
#include "slot.h"

using namespace Slots::Internal;

SlotConfigurationDialog::SlotConfigurationDialog(Slot& slot, QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::SlotConfigurationDialog),
    m_slot(slot)
{
    m_ui->setupUi(this);

    // Assign slot values to configuration fields
    m_ui->textInputField->setText(m_slot.title());
    m_ui->fileInputField->setText(m_slot.fileName());
    m_ui->outputSelectionWidget->setSelection(m_slot.driver(), m_slot.device(), m_slot.channel());
    m_backgroundColor = m_slot.backgroundColor();
    m_fontColor = m_slot.fontColor();
    m_ui->fontSizeSpinBox->setValue(m_slot.fontSize());

    updateBackgroundLabelColor();
    updateFontLabelColor();

    connect(m_ui->buttonBox, &QDialogButtonBox::accepted, this, &SlotConfigurationDialog::save);
    connect(m_ui->fileButton, &QToolButton::clicked, this, &SlotConfigurationDialog::selectFile);
    connect(m_ui->backgroundColorButton, &QToolButton::clicked, this, &SlotConfigurationDialog::selectBackgroundColor);
    connect(m_ui->fontColorButton, &QToolButton::clicked, this, &SlotConfigurationDialog::selectFontColor);
}

SlotConfigurationDialog::~SlotConfigurationDialog()
{
    delete m_ui;
}

void SlotConfigurationDialog::save()
{
    m_slot.setTitle(m_ui->textInputField->text());
    m_slot.setFileName(m_ui->fileInputField->text());
    m_slot.setDriver(m_ui->outputSelectionWidget->driver());
    m_slot.setDevice(m_ui->outputSelectionWidget->device());
    m_slot.setChannel(m_ui->outputSelectionWidget->channel());
    m_slot.setBackgroundColor(m_backgroundColor);
    m_slot.setFontColor(m_fontColor);
    m_slot.save();
    accept();
}

void SlotConfigurationDialog::selectFile()
{
    QStringList mimeTypes;
    QMap<QString, Audio::IDriver*> drivers = Audio::DeviceManager::instance()->drivers();
    QString selectedDriver = m_ui->outputSelectionWidget->driver();
    if (drivers.contains(selectedDriver)) {
        mimeTypes = drivers.value(selectedDriver)->supportedMimeTypes();
    }
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::List);
    dialog.setMimeTypeFilters(mimeTypes);
    if (dialog.exec() && dialog.selectedFiles().length() > 0) {
        QString file = dialog.selectedFiles().first();
        m_ui->fileInputField->setText(file);
    }
}

void SlotConfigurationDialog::selectBackgroundColor()
{
    QColor selectedColor = QColorDialog::getColor(QColor(m_backgroundColor), this);
    if (selectedColor.isValid())
    {
        m_backgroundColor = selectedColor;
        updateBackgroundLabelColor();
    }
}

void SlotConfigurationDialog::selectFontColor()
{
    QColor selectedColor = QColorDialog::getColor(QColor(m_fontColor), this);
    if (selectedColor.isValid())
    {
        m_fontColor = selectedColor;
        updateFontLabelColor();
    }
}

void SlotConfigurationDialog::updateBackgroundLabelColor()
{
    QPalette p(m_ui->backgroundColorDisplayLabel->palette());
    p.setColor(QPalette::Background, m_backgroundColor);
    m_ui->backgroundColorDisplayLabel->setPalette(p);
}

void SlotConfigurationDialog::updateFontLabelColor()
{
    QPalette p(m_ui->fontColorDisplayLabel->palette());
    p.setColor(QPalette::Background, m_fontColor);
    m_ui->fontColorDisplayLabel->setPalette(p);
}
