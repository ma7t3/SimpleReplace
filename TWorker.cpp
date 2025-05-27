#include "TWorker.h"

#include <QtCore>

TWorker::TWorker(QObject *parent) :
    QThread(parent),
    _workMode(FindOnlyMode),
    _includeMode(SimpleMode),
    _recursive(false),
    _caseInsensitive(false),
    _useRegex(false) {

}

void TWorker::run() {
    // Do some work here
    processFolder(_workingDir);
}

void TWorker::processFolder(const QString folderPath) {
    QString relPath = folderPath;
    relPath.remove(_workingDir + "/");
    QDir dir(folderPath);
    QStringList files = dir.entryList(QDir::Files|QDir::NoDotAndDotDot);
    emit progressMax(files.count());
    int i = 0;
    for(QString current : files) {
        emit progressUpdate(i, relPath + "/" + current);
        processFile(folderPath + "/" + current);

        i++;
    }

    if(_recursive) {
        QStringList folders = dir.entryList(QDir::Dirs|QDir::NoDotAndDotDot);
        for(QString current : folders) {
            processFolder(folderPath + "/" + current);
        }
    }

    emit progressUpdate(i + 1, tr("Finished"));
}

void TWorker::processFile(const QString filePath) {
    QString relPath = filePath;
    relPath.remove(_workingDir + "/");

    QFile f(filePath);
    if(!f.open(QFile::ReadWrite)) {
        emit fileFinished(relPath, 0, false);
        return;
    }

    QTextStream s(&f);
    s.setEncoding(_encoding);
    QString str = s.readAll();
    f.close();

    int count = str.count(_searchString, (_caseInsensitive ? Qt::CaseInsensitive : Qt::CaseSensitive));

    if(_workMode == FindAndReplaceMode)
        str.replace(_searchString, _replaceString, (_caseInsensitive ? Qt::CaseInsensitive : Qt::CaseSensitive));

    if(!f.open(QFile::WriteOnly|QFile::Truncate)) {
        emit fileFinished(relPath, 0, false);
        return;
    }

    s << str;
    f.close();
    emit fileFinished(relPath, count, true);
}

TWorker::WorkMode TWorker::workMode() const {
    return _workMode;
}

void TWorker::setWorkMode(const WorkMode &m) {
    _workMode = m;
}

TWorker::IncludeMode TWorker::includeMode() const {
    return _includeMode;
}

void TWorker::setIncludeMode(IncludeMode newIncludeMode) {
    _includeMode = newIncludeMode;
}

QString TWorker::workingDir() const {
    return _workingDir;
}

void TWorker::setWorkingDir(const QString &newWorkingDir) {
    _workingDir = newWorkingDir;
}


bool TWorker::recursive() const
{
    return _recursive;
}

void TWorker::setRecursive(bool newRecursive)
{
    _recursive = newRecursive;
}

QStringList TWorker::excludeDir() const {
    return _excludeDir;
}

void TWorker::setExcludeDir(const QStringList &newExcludeDir) {
    _excludeDir = newExcludeDir;
    _includeMode = SimpleMode;
}

QStringList TWorker::fileMask() const {
    return _fileMask;
}

void TWorker::setFileMask(const QStringList &newFileMask) {
    _fileMask = newFileMask;
    _includeMode = SimpleMode;
}

QStringList TWorker::excludeFileMask() const {
    return _excludeFileMask;
}

void TWorker::setExcludeFileMask(const QStringList &newExcludeFileMask) {
    _excludeFileMask = newExcludeFileMask;
    _includeMode = SimpleMode;
}

QRegularExpression TWorker::advancedRegEx() const {
    return _advancedRegEx;
}

void TWorker::setAdvancedRegEx(const QRegularExpression &newAdvancedRegEx) {
    _advancedRegEx = newAdvancedRegEx;
    _includeMode = AdvancedMode;
}

void TWorker::setAdvancedRegEx(const QString &newAdvancedRegEx) {
    setAdvancedRegEx(QRegularExpression(newAdvancedRegEx));
}

bool TWorker::caseInsensitive() const {
    return _caseInsensitive;
}

void TWorker::setCaseInsensitive(bool newCaseInsensitive) {
    _caseInsensitive = newCaseInsensitive;
}

bool TWorker::useRegex() const {
    return _useRegex;
}

void TWorker::setUseRegex(bool newUseRegex) {
    _useRegex = newUseRegex;
}

QStringConverter::Encoding TWorker::encoding() const {
    return _encoding;
}

void TWorker::setEncoding(QStringConverter::Encoding newEncoding) {
    _encoding = newEncoding;
}

QString TWorker::replaceString() const {
    return _replaceString;
}

void TWorker::setReplaceString(const QString &newReplaceString) {
    _replaceString = newReplaceString;
}

QString TWorker::searchString() const {
    return _searchString;
}

void TWorker::setSearchString(const QString &newSearchString) {
    _searchString = newSearchString;
}
