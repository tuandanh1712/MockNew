#include "ListVideoModel.h"



ListVideoModel::ListVideoModel( QObject *parent)
    : QAbstractListModel(parent)
{

    // m_listVideo=videoList;


}

ListVideoModel::~ListVideoModel()
{
    for(int i=0;i<m_listVideo.size();i++)
    {
        delete m_listVideo[i];
    }

    m_listVideo.clear();


}

int ListVideoModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_listVideo.count();
}

QVariant ListVideoModel::data(const QModelIndex &index, int role) const
{
    if ( !index.isValid() )
        return QVariant();

    CommonModel* songs = m_listVideo.at(index.row());
    if ( role == TitleVideo ){
        return songs->getTitle();
    }
    else if ( role == AlbumVideo )
        return songs->getAlbum();
    else if ( role == ArtistVideo )
        return songs->getArtist();
    else if(role==SourceVideo)
        return songs->getSource();
    else if(role==IndexVideo)
        return songs->getIndex();
    else
        return QVariant();
}

QHash<int, QByteArray> ListVideoModel::roleNames() const
{
    static QHash<int, QByteArray> mapping {
        {TitleVideo, "TitleVideo"},
        {AlbumVideo, "AlbumVideo"},
        {ArtistVideo, "ArtistVideo"},
        {SourceVideo,"SourceVideo"},
        {IndexVideo,"IndexVideo"}
    };
    return mapping;
}
void ListVideoModel::deletelVideoModel(int index)
{
    beginRemoveRows(QModelIndex(),index,index);
    m_listVideo.removeAt(index);
    endRemoveRows();

}

void ListVideoModel::addVideoModel(CommonModel *data)
{
    beginInsertRows (QModelIndex(),rowCount (QModelIndex()),rowCount (QModelIndex()));
    m_listVideo.append (data);
    endInsertRows ();
}









