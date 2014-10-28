#ifndef COVERART_H
#define COVERART_H

#include <QImage>
#include <QString>
#include <QObject>
#include <QtDebug>

struct CoverInfo {
    // DO NOT CHANGE THESE CONSTANT VALUES. THEY ARE STORED IN THE DATABASE.
    enum Source {
        // We don't know where we got this cover.
        UNKNOWN = 0,
        // The cover was automatically detected by Mixxx.
        GUESSED = 1,
        // The cover was selected by the user (do not disturb).
        USER_SELECTED = 2
    };

    // DO NOT CHANGE THESE CONSTANT VALUES. THEY ARE STORED IN THE DATABASE.
    enum Type {
        // No cover information is known.
        NONE = 0,
        // Cover is located in the metadata of an audio file.
        METADATA = 1,
        // Cover is located in a standalone image file.
        FILE = 2
    };

    CoverInfo() : source(UNKNOWN),
                  type(NONE),
                  trackId(-1),
                  coverLocation(QString()),
                  trackLocation(QString()),
                  hash(QString()) {}

    bool operator==(const CoverInfo& other) const {
        return other.source == source &&
                other.type == type &&
                other.coverLocation == coverLocation &&
                other.trackLocation == trackLocation &&
                other.hash == hash;
    }
    bool operator!=(const CoverInfo& other) const {
        return !(*this == other);
    }

    Source source;
    Type type;
    int trackId;
    QString coverLocation;
    QString trackLocation;
    QString hash;
};

struct CoverArt {
    CoverArt() {}

    bool operator==(const CoverArt& other) const {
        // Only count image in the equality if both are non-null.
        return other.info == info &&
                (other.image.isNull() || image.isNull() ||
                 other.image == image);
    }
    bool operator!=(const CoverArt& other) const {
        return !(*this == other);
    }

    CoverInfo info;
    QImage image;
};

QDebug operator<<(QDebug dbg, const CoverInfo& info);
QDebug operator<<(QDebug dbg, const CoverArt& art);

#endif /* COVERART_H */
