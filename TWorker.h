#ifndef TWORKER_H
#define TWORKER_H

#include <QThread>
#include <QRegularExpression>

class TWorker : public QThread {
    Q_OBJECT
public:
    TWorker(QObject *parent);

    enum WorkMode {
        FindOnlyMode,
        FindAndReplaceMode
    };

    enum IncludeMode {
        SimpleMode,
        AdvancedMode
    };

    void run() override;

    WorkMode workMode() const;
    void setWorkMode(const WorkMode &m);

    IncludeMode includeMode() const;
    void setIncludeMode(IncludeMode newIncludeMode);

    QString workingDir() const;
    void setWorkingDir(const QString &newWorkingDir);

    QStringList excludeDir() const;
    void setExcludeDir(const QStringList &newExcludeDir);

    QStringList fileMask() const;
    void setFileMask(const QStringList &newFileMask);

    QStringList excludeFileMask() const;
    void setExcludeFileMask(const QStringList &newExcludeFileMask);

    QRegularExpression advancedRegEx() const;
    void setAdvancedRegEx(const QRegularExpression &newAdvancedRegEx);
    void setAdvancedRegEx(const QString &newAdvancedRegEx);

    bool caseInsensitive() const;
    void setCaseInsensitive(bool newCaseInsensitive);

    bool useRegex() const;
    void setUseRegex(bool newUseRegex);

    QStringConverter::Encoding encoding() const;
    void setEncoding(QStringConverter::Encoding newEncoding);

    bool recursive() const;
    void setRecursive(bool newRecursive);

signals:
    void progressUpdate(const int &value, const QString &text);
    void progressMax(const int &max);
    void fileFinished(const QString &file, const int &occurences, const bool &success);

private:
    WorkMode _workMode;
    IncludeMode _includeMode;
    QString _workingDir;
    bool _recursive;
    QStringList _excludeDir;
    QStringList _fileMask;
    QStringList _excludeFileMask;
    QRegularExpression _advancedRegEx;
    bool _caseInsensitive;
    bool _useRegex;
    QStringConverter::Encoding _encoding;
};

#endif // TWORKER_H
