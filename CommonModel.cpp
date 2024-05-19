#include "CommonModel.h"

CommonModel::CommonModel()
{

}

QString CommonModel::getSource()
{
    return media.m_source;

}

void CommonModel::setSource(QString source)
{
    media.m_source=source;

}

QString CommonModel::getFileName()
{
    return media.m_fileName;

}

void CommonModel::setFileName(QString fileName)
{
    media.m_fileName=fileName;

}

QString CommonModel::getTitle()
{
    if(media.m_title.toStdString()=="")
    {
        return "Unknow";
    }
    return media.m_title;

}

void CommonModel::setTitle(QString title)
{
    media.m_title=title;

}

QString CommonModel::getArtist()
{
    if(media.m_artist.toStdString()=="")
    {
        return "Unknow";
    }

    return media.m_artist;

}

void CommonModel::setArtist(QString artist)
{
    media.m_artist=artist;

}

QString CommonModel::getAlbum()
{
    if(media.m_album.toStdString()=="")
    {
        return "Unknow";
    }
    return media.m_album;

}

void CommonModel::setAlbum(QString album)
{
    media.m_album=album;
}

int CommonModel::getIndex()
{
    return media.m_index;

}

void CommonModel::setIndex(int index)
{
    media.m_index=index;

}


