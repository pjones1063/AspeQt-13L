/*
 * bootoptionsdialog.cpp
 *
 * Copyright 2015 Joseph Zatarski
 * Copyright 2017 blind
 *
 * This file is copyrighted by either Fatih Aygun, Ray Ataergin, or both.
 * However, the years for these copyrights are unfortunately unknown. If you
 * know the specific year(s) please let the current maintainer know.
 */

#include "bootoptionsdialog.h"
#include "ui_bootoptionsdialog.h"
#include "mainwindow.h"

#include <QTranslator>
#include <QDir>

extern QString g_respeQtAppPath;
extern bool g_disablePicoHiSpeed;

QString selectedDOS, bootDir;

BootOptionsDialog::BootOptionsDialog(const QString& bootFolderPath, QWidget *parent) :
    QDialog(parent),
    bootFolderPath_(bootFolderPath),
    m_ui(new Ui::BootOptionsDialog)
{
    Qt::WindowFlags flags = windowFlags();
    flags = flags & (~Qt::WindowContextHelpButtonHint);
    setWindowFlags(flags);

    m_ui->setupUi(this);

    connect(m_ui->myPicoDOS, SIGNAL(toggled(bool)), this, SLOT(picoDOSToggled()));
}

BootOptionsDialog::~BootOptionsDialog()
{
    delete m_ui;
}

void BootOptionsDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void BootOptionsDialog::accept()
{
    QDir dir;
    QFile file;
    QStringList filters;
    QStringList allFiles;
    QString fileName;

    if(m_ui->atariDOS->isChecked()) selectedDOS = "$bootata";
    if(m_ui->myDOS->isChecked()) selectedDOS = "$bootmyd";
    if(m_ui->dosXL->isChecked()) selectedDOS = "$bootdxl";
    if(m_ui->smartDOS->isChecked()) selectedDOS = "$bootsma";
    if(m_ui->spartaDOS->isChecked()) selectedDOS = "$bootspa";
    if(m_ui->myPicoDOS->isChecked()) {
        selectedDOS = "$bootpic";
        g_disablePicoHiSpeed = m_ui->disablePicoHiSpeed->isChecked();
    }

    bootDir = g_respeQtAppPath + "/" + selectedDOS;

    // First delete existing boot files in the Folder Image
    // then copy new boot files from the appropriate DOS directory

    dir.setPath(bootFolderPath_);
    filters << "*dos.sys" << "dup.sys" << "dosxl.sys"
            << "autorun.sys" << "ramdisk.com" << "menu.com"
            << "startup.exc" << "x*.dos" << "startup.bat" << "$*.bin";
    allFiles =  dir.entryList(filters, QDir::Files);
    foreach(fileName, allFiles) {
        file.remove(bootFolderPath_ + "/" + fileName);
    }
    dir.setPath(g_respeQtAppPath + "/" + selectedDOS);
    allFiles =  dir.entryList(QDir::NoDotAndDotDot | QDir::Files);
    foreach(fileName, allFiles) {
        file.copy(dir.path() + "/" + fileName, bootFolderPath_ + "/" + fileName);
    }

    QDialog::accept();
}

void BootOptionsDialog::picoDOSToggled()
{
    bool enable = m_ui->myPicoDOS->isChecked();
    m_ui->disablePicoHiSpeed->setEnabled(enable);
}
