#include <QtDebug>

#include "library/coverart.h"
#include "util/debug.h"

QString sourceToString(CoverInfo::Source source) {
    switch (source) {
        case CoverInfo::UNKNOWN:
            return "UNKNOWN";
        case CoverInfo::GUESSED:
            return "GUESSED";
        case CoverInfo::USER_SELECTED:
            return "USER_SELECTED";
    }
}

QString typeToString(CoverInfo::Type type) {
    switch (type) {
        case CoverInfo::NONE:
            return "NONE";
        case CoverInfo::METADATA:
            return "METADATA";
        case CoverInfo::FILE:
            return "FILE";
    }
}

QDebug operator<<(QDebug dbg, const CoverInfo& info) {
    return dbg.maybeSpace() << QString("CoverInfo(%1,%2,%3,%4,%5,%6)")
            .arg(typeToString(info.type))
            .arg(sourceToString(info.source))
            .arg(info.coverLocation)
            .arg(info.hash)
            .arg(QString::number(info.trackId))
            .arg(info.trackLocation);
}

QDebug operator<<(QDebug dbg, const CoverArt& art) {
    return dbg.maybeSpace() << QString("CoverArt(%1,%2)")
            .arg(toDebugString(art.image.size()))
            .arg(toDebugString(art.info));
}
