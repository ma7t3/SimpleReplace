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
