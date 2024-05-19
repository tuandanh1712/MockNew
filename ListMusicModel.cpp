#include "ListMusicModel.h"

#include "qimage.h"

ListMusicModel::ListMusicModel(QVector<CommonModel*> &songList, QObject *parent)
    : QAbstractListModel(parent),m_listSong()
{

    m_listSong=songList;


}

ListMusicModel::ListMusicModel()
{

}

ListMusicModel::~ListMusicModel()
{
    for(int i=0;i<m_listSong.size();i++)
    {
        delete m_listSong[i];
    }

    m_listSong.clear();


}

int ListMusicModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_listSong.count();
}

QVariant ListMusicModel::data(const QModelIndex &index, int role) const
{
    if ( !index.isValid() )
        return QVariant();

    CommonModel* songs = m_listSong.at(index.row());
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

QHash<int, QByteArray> ListMusicModel::roleNames() const
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

void ListMusicModel::deletelMusicModel(int index)
{
    beginRemoveRows(QModelIndex(),index,index);
    m_listSong.removeAt(index);
    endRemoveRows();
}

void ListMusicModel::addMusicModel(CommonModel *data)
{
    beginInsertRows (QModelIndex(),rowCount (QModelIndex()),rowCount (QModelIndex()));
    m_listSong.append (data);
    endInsertRows ();

}

QImage ListMusicModel::imageForTag(QString mediasource)
{
    qDebug()<<"abc"<<mediasource;
    QImage image;
    TagLib::FileRef taglib_file(mediasource.toLocal8Bit().data());
    TagLib::ID3v2::Tag tagObject = TagLib::ID3v2::Tag(taglib_file.file(), 0);
    TagLib::ID3v2::Tag* tag = &tagObject;
    TagLib::ID3v2::FrameList l = tag->frameList("APIC");
    /* "APIC" is the ID3v2 frame identifier for attached pictures (album artwork).
    The retrieved frames are stored in the FrameList object called l.*/
    if(l.isEmpty()) {
        return image;
    }
    //performing a static cast on the first element of the FrameList l to convert it into a pointer of type TagLib::ID3v2::AttachedPictureFrame*.
    TagLib::ID3v2::AttachedPictureFrame *f =
        static_cast<TagLib::ID3v2::AttachedPictureFrame *>(l.front());
    image.loadFromData((const uchar *) f->picture().data(), f->picture().size());
    return image;
}







