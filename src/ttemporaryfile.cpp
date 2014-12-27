/* Copyright (c) 2010-2013, AOYAMA Kazuharu
 * All rights reserved.
 *
 * This software may be used and distributed according to the terms of
 * the New BSD License, which is incorporated herein by reference.
 */

#include <QDir>
#include <TTemporaryFile>
#include <TWebApplication>
#include <TAppSettings>

/*!
  \class TTemporaryFile
  \brief The TTemporaryFile class is a temporary file device on an action
  context of web application. After an action of a controller returns,
  temporary files created in the action will be deleted. Because this
  class inherits QTemporaryFile, you can use same functions as that.
  \sa http://qt-project.org/doc/qt-4.8/qtemporaryfile.html
*/

/*!
  Constructor.
*/
TTemporaryFile::TTemporaryFile()
{
    QString tmppath;
    if (Tf::app()) {
        tmppath = Tf::appSettings()->value(Tf::UploadTemporaryDirectory).toString().trimmed();
        if (!tmppath.isEmpty() && QDir::isRelativePath(tmppath)) {
            tmppath = Tf::app()->webRootPath() + tmppath + QDir::separator();
        }

        if (!QDir(tmppath).exists()) {
            tmppath = "";
        }
    }

    if (tmppath.trimmed().isEmpty()) {
        tmppath = QDir::tempPath();
    }

    if (!tmppath.endsWith(QDir::separator())) {
        tmppath += QDir::separator();
    }
    setFileTemplate(tmppath + "tf_temp.XXXXXXXXXXXXXXXX");
}

/*!
  Returns an absolute path including the file name.
*/
QString TTemporaryFile::absoluteFilePath() const
{
    QFileInfo info(*this);
    return info.absoluteFilePath();
}
