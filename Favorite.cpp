#include "Favorite.h"
#include "ListMusicModel.h"
#include "fileref.h"
#include <QDebug>

Favorite::Favorite( QObject *parent)
    : QAbstractListModel(parent),m_listFavor()
{

    //    m_listSong=songList;


}

Favorite::~Favorite()
{
    for(int i=0;i<m_listFavor.size();i++)
    {
        delete m_listFavor[i];
    }

    m_listFavor.clear();


}

int Favorite::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_listFavor.count();
}

QVariant Favorite::data(const QModelIndex &index, int role) const
{
    if ( !index.isValid() )
        return QVariant();

    CommonModel* songs = m_listFavor.at(index.row());
    if ( role == TitleSongs ){
        return songs->getTitle();
    }
    else if ( role == AlbumSongs )
        return songs->getAlbum();
    else if ( role == ArtistSongs )
        return songs->getArtist();
    else if(role==SourceSongs)
        return songs->getSource();
    else if(role==IndexSongs)
        return songs->getIndex();
    else
        return QVariant();
}

QHash<int, QByteArray> Favorite::roleNames() const
{
    static QHash<int, QByteArray> mapping {
        {TitleSongs, "TitleSongs"},
        {ArtistSongs, "ArtistSongs"},
        {AlbumSongs, "AlbumSongs"},
        {SourceSongs,"SourceSongs"},
        {IndexSongs,"IndexSongs"}
    };
    return mapping;
}

void Favorite::removeFavor(int index)
{
    beginRemoveRows(QModelIndex(),index,index);
    m_listFavor.removeAt(index);
    endRemoveRows();

}
void Favorite::addMusicFavor(CommonModel *data)
{
    beginInsertRows (QModelIndex(),rowCount (QModelIndex()),rowCount (QModelIndex()));
    m_listFavor.append (data);
    endInsertRows ();

}



QVector<CommonModel *> Favorite::listFavor() const
{
    return m_listFavor;
}

void Favorite::setListFavor(const QVector<CommonModel *> &newListFavor)
{
    if (m_listFavor == newListFavor)
        return;
    m_listFavor = newListFavor;
    emit listFavorChanged();
}
