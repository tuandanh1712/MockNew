#ifndef LISTMUSICMODEL_H
#define LISTMUSICMODEL_H

#include <QObject>
#include <QVector>
#include <QDir>
#include <QByteArray>
#include <QStandardPaths>
#include <QDebug>
#include <QAbstractListModel>
#include <QBuffer>
#include "CommonModel.h"
#include "attachedpictureframe.h"
#include "fileref.h"
#include "id3v2tag.h"

#include <taglib/tag.h>



class ListMusicModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ListMusicModel(QVector<CommonModel*> &songList,QObject *parent = nullptr);
    ListMusicModel();
    enum Songs {
        TitleSongs = Qt::UserRole+1,
        ArtistSongs,
        AlbumSongs,
        SourceSongs,
        IndexSongs,
    };
    ~ListMusicModel();

    virtual int rowCount(const QModelIndex& parent=QModelIndex()) const override;

    QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;
    QHash<int, QByteArray> roleNames() const override;
    void deletelMusicModel(int index);
    void addMusicModel(CommonModel *data);
    QImage imageForTag(QString mediasource);
signals:


private:
    QVector<CommonModel*> m_listSong;

};

#endif
