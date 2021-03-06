
#include "Helper.h"

namespace Helper
{

int indexOf(const QString array[], int size, const QString& value)
{
    for(int index = 0; index < size; index++)
    {
        if(value == array[index])
            return index;
    }

    return (-1);
}

int statusIndexFromCode(QString status)
{
    for( int index = 0; index < ST_COUNT; index++ )
    {
        if( statusCode[index].compare(status) == 0 )
            return index;
    }

    return -1;
}

QString  formatSize(qint64 size)
{
    qint64 gb = 1073741824;
    qint64 mb = 1048576;
    qint64 kb = 1024;

    if(size > gb)
        return QString("%1 GB").arg((double)size / gb, 0, 'f', 2);
    else if(size > mb)
        return QString("%1 MB").arg((double)size / mb, 0, 'f', 2);
    else if(size > kb)
        return QString("%1 KB").arg((double)size / kb, 0, 'f', 2);
    else
        return QString("%1 bytes").arg(size);
}

QString  getUuid(void)
{
    QString Uuid = QUuid::createUuid().toString();
    Uuid = Uuid.remove("{").remove("}").remove("-");
    return Uuid;
}

QString  getLogonName(void)
{
#if defined Q_OS_WIN	//	if platform is Windows
    TCHAR szUserName[UNLEN + 1];
    DWORD nSize = sizeof(szUserName);
    GetUserName(szUserName, &nSize);
    return QString::fromStdWString(szUserName);
#else	// this code should work for MAC and Linux
    char* szUserName;
    szUserName = getenv("USER");
    if(szUserName)
        return QString::fromLatin1(szUserName);
#endif

    return QString::null;
}

QString  getHostName(void)
{
    return QHostInfo::localHostName();
}

QString  getOSName(void)
{
    QString osName = "Unknown";

#if defined Q_OS_WIN
    switch(QSysInfo::WindowsVersion) {
    case QSysInfo::WV_NT:
        osName = "Windows NT";
        break;
    case QSysInfo::WV_2000:
        osName = "Windows 2000";
        break;
    case QSysInfo::WV_XP:
        osName = "Windows XP";
        break;
    case QSysInfo::WV_2003:
        osName = "Windows Server 2003";
        break;
    case QSysInfo::WV_VISTA:
        osName = "Windows Vista";
        break;
    case QSysInfo::WV_WINDOWS7:
        osName = "Windows 7";
        break;
    default:
        osName = "Windows";
        break;
    }
#elif defined Q_OS_MAC
    switch(QSysInfo::MacintoshVersion) {
    case QSysInfo::MV_CHEETAH:
        osName = "Mac OS X 10.0";
        break;
    case QSysInfo::MV_PUMA:
        osName = "Mac OS X 10.1";
        break;
    case QSysInfo::MV_JAGUAR:
        osName = "Mac OS X 10.2";
        break;
    case QSysInfo::MV_PANTHER:
        osName = "Mac OS X 10.3";
        break;
    case QSysInfo::MV_TIGER:
        osName = "Mac OS X 10.4";
        break;
    case QSysInfo::MV_LEOPARD:
        osName = "Mac OS X 10.5";
        break;
    case QSysInfo::MV_SNOWLEOPARD:
        osName = "Mac OS X 10.6";
        break;
    case QSysInfo::MV_LION:
        osName = "Mac OS X 10.7";
        break;
    default:
        osName = "Mac OS X";
        break;
    }
#elif defined Q_OS_LINUX
    osName = "Linux/X11";
#endif

    return osName;
}

// #define DELIMITER		"||"
// #define DELIMITER_ESC	"\\|\\|"


QString  escapeDelimiter(QString *lpszData)
{
    return lpszData->replace( "||", "\\|\\|", Qt::CaseSensitive);
}

QString  unescapeDelimiter(QString* lpszData)
{
    return lpszData->replace( "\\|\\|", "||", Qt::CaseSensitive);
}

//	Returns:
//	<0 if version 1 is older
//	>0 if version 1 is newer
//	0 if both versions are same
int  compareVersions(const QString& version1, const QString& version2)
{
    QStringList v1 = version1.split(".", QString::SkipEmptyParts);
    QStringList v2 = version2.split(".", QString::SkipEmptyParts);

    //	Assuming that the version is in x.x.x format, we only need to iterate 3 times
    for(int index = 0; index < 3; index++) {
        int comp = v1[index].toInt() - v2[index].toInt();
        if(comp != 0)
            return comp;
    }

    return 0;
}

QString  boolToString(bool value)
{
    return value ? "true" : "false";
}

bool  stringToBool(const QString& value)
{
    return value.compare( "true" ) == 0 ? true : false;
}

//	Function that copies content of source to destination
//	Destination file will be overwritten
//	Supports only small files
bool  copyFile(const QString& source, const QString& destination)
{
    QFile srcFile(source);
    if(!srcFile.open(QIODevice::ReadOnly))
        return false;

    QByteArray data = srcFile.readAll();
    srcFile.close();

    QFile destFile(destination);
    if(!destFile.open(QIODevice::WriteOnly))
        return false;

    destFile.write(data);
    destFile.close();

    return true;
}

}; // namespace Helper


