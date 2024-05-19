#ifndef MEDIAMODEL_H
#define MEDIAMODEL_H
#include <QString>
#include <QUrl>
#include <QVariant>

struct MediaData{
    MediaData(){}
    QString m_source;
    QString m_fileName;
    QString m_title;
    QString m_artist;
    QString m_album;
    int m_index;

};

class CommonModel
{
public:
    CommonModel();
    QString getSource();
    void setSource(QString);
    QString getFileName();
    void setFileName(QString);
    QString getTitle();
    void setTitle(QString);
    QString getArtist();
    void setArtist(QString);
    QString getAlbum();
    void setAlbum(QString);
    int getIndex();
    void setIndex(int);
private:
    MediaData media;

};

#endif // MEDIAMODEL_H
