#include "MediaModel.h"
#include "qfiledialog.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTranslator>
MediaController::MediaController( QObject *parent)
    : QObject(parent)
{

    player=new QMediaPlayer;
    playMusicList = new QMediaPlaylist;
    playVideoList= new QMediaPlaylist;
    playMusicFavorit=new QMediaPlaylist;
    m_proxyVideo=new QSortFilterProxyModel;
    m_musicListModel=new ListMusicModel;
    m_videoListModel=new ListVideoModel;
    m_favoriteSongs=new Favorite;
    player->setVolume(0);

    connect(player, &QMediaPlayer::volumeChanged, this, &MediaController::volumeChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &MediaController::positionChanged);
    connect(player,&QMediaPlayer::durationChanged, this, &MediaController::durationChanged);
    connect(playMusicList,&QMediaPlaylist::currentIndexChanged,this,&MediaController::setIndexMediaChanged);
    connect(playVideoList,&QMediaPlaylist::currentIndexChanged,this,&MediaController::setIndexMediaChanged);
    connect(playMusicFavorit,&QMediaPlaylist::currentIndexChanged,this,&MediaController::setIndexMediaChanged);
    getMusicLocal();
    getVideoLocal();
}



MediaController::~MediaController()
{
    delete player;
    delete  playMusicList;
    delete m_proxyVideo;

    delete  playVideoList;
    delete m_musicListModel;
    delete m_videoListModel;
    delete playMusicFavorit;
    delete m_favoriteSongs;
}


void MediaController::getFolderMusic()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::Directory);
    QString folderPath=dialog.getExistingDirectory(nullptr,"Open Folder","/home");
    qDebug()<<"folderPath"<<folderPath;
    QDir folder(folderPath);
    QStringList filter;
    filter<<"*.mp3";
    QStringList filePath = folder.entryList(filter, QDir::Files);
    qDebug()<<"filePath"<<filePath;
    QList<QMediaContent> content;
    for (int i = 0; i < filePath.size(); i++){

        const QString& fileName=filePath[i];
        QString fullPath = folder.filePath(fileName);
        qDebug()<<"fullPath"<<fullPath;
        //get metadata of media
        TagLib::FileRef f(fullPath.toLocal8Bit().data());
        TagLib::Tag* tag = f.tag();
        if (!tag)
        {
            continue;
        }
        // QString m_source=fullPath.toStdString().c_str();
        // QString m_title=QString::fromStdString(tag->title().to8Bit(true));
        // QString m_artist=QString::fromStdString(tag->artist().to8Bit(true));
        // QString m_album=QString::fromStdString(tag->album().to8Bit(true));
        // int m_index=i;
        CommonModel* song = new CommonModel;
        song->setSource(fullPath.toStdString().c_str());
        song->setTitle(QString::fromStdString(tag->title().to8Bit(true)));
        song->setArtist(QString::fromStdString(tag->artist().to8Bit(true)));
        song->setAlbum(QString::fromStdString(tag->album().to8Bit(true)));
        song->setIndex(i);
        musicModel.push_back(song);
        m_musicListModel->addMusicModel (song);
        content.push_back(QMediaContent(QUrl::fromLocalFile(fullPath)));
    }
    playMusicList->addMedia(content);

}
QVariantList MediaController::getMusicLocal()
{

    QDir m_musicPath;
    m_musicPath.setPath(QStandardPaths::standardLocations(QStandardPaths::MusicLocation).at(0));// set path in music location
    QDir directory(m_musicPath);
    m_listSongPath = directory.entryList(QStringList() << "*.mp3" << "*.MP3",QDir::Files);// find files has format mp3, MP3
    QList<QMediaContent> content;
    for (int i = 0; i < m_listSongPath.size(); ++i)
    {
        const QString& f = m_listSongPath[i];
        content.push_back(QUrl::fromLocalFile(directory.path()+"/" + f));
        musicList.push_back(QVariant::fromValue(f));
        TagLib::FileRef r((directory.path()+"/" + f).toLocal8Bit().data());
        TagLib::Tag* tag = r.tag();
        if (!tag)
        {
            continue;
        }
        CommonModel* song = new CommonModel;
        song->setSource((directory.path()+"/" + f).toLocal8Bit().data());
        song->setTitle(QString::fromStdString(tag->title().to8Bit(true)));
        song->setArtist(QString::fromStdString(tag->artist().to8Bit(true)));
        song->setAlbum(QString::fromStdString(tag->album().to8Bit(true)));
        song->setIndex(i);
        m_musicListModel->addMusicModel (song);
        musicModel.push_back(song);
    }
    playMusicList->addMedia(content);
    return musicList;

}




void MediaController::getFolderVideo()
{
    {
        QFileDialog dialog;
        dialog.setFileMode(QFileDialog::Directory);
        QString folderPath=dialog.getExistingDirectory(nullptr,"Open Folder","/home");
        qDebug()<<"folderPath"<<folderPath;
        QDir folder(folderPath);
        QStringList filter;
        filter<<"*.mp4";
        QStringList filePath = folder.entryList(filter, QDir::Files);
        qDebug()<<"filePath"<<filePath;
        QList<QMediaContent> content;
        for (int i = 0; i < filePath.size(); i++){

            const QString& fileName=filePath[i];
            QString fullPath = folder.filePath(fileName);
            qDebug()<<"fullPath"<<fullPath;
            //get metadata of media
            TagLib::FileRef f(fullPath.toLocal8Bit().data());
            TagLib::Tag* tag = f.tag();
            if (!tag)
            {
                continue;
            }
            CommonModel* video = new CommonModel;
            video->setSource(fullPath.toStdString().c_str());
            video->setTitle(QString::fromStdString(tag->title().to8Bit(true)));
            video->setArtist(QString::fromStdString(tag->artist().to8Bit(true)));
            video->setAlbum(QString::fromStdString(tag->album().to8Bit(true)));
            video->setIndex(i);
            m_videoListModel->addVideoModel(video);
            // videoModel .push_back(video);
            content.push_back(QMediaContent(QUrl::fromLocalFile(fullPath)));
        }
        // m_videoListModel=new ListVideoModel(videoModel);
        // m_proxyVideo->setSourceModel(m_videoListModel);
        playVideoList->addMedia(content);
    }
}

QVariantList MediaController::getVideoLocal()
{

    QDir m_videoPath;
    m_videoPath.setPath(QStandardPaths::standardLocations(QStandardPaths::MoviesLocation).at(0));// set path in movie location
    QDir directory(m_videoPath);
    m_listVideoPath = directory.entryList(QStringList() << "*.mp4" << "*.MP4",QDir::Files);// find files has format mp4, MP4

    QList<QMediaContent> content;
    for(int i=0;i<m_listVideoPath.size();++i)
    {
        const QString& f=m_listVideoPath[i];

        content.push_back(QUrl::fromLocalFile(directory.path()+"/" + f));
        videoList.push_back(QVariant::fromValue(f));

        TagLib::FileRef r((directory.path()+"/" + f).toLocal8Bit().data());
        TagLib::Tag* tag = r.tag();
        if (!tag)
        {
            continue;
        }
        CommonModel* video = new CommonModel;
        video->setSource((directory.path()+"/" + f).toLocal8Bit().data());
        video->setTitle(QString::fromStdString(tag->title().to8Bit(true)));
        video->setArtist(QString::fromStdString(tag->artist().to8Bit(true)));
        video->setAlbum(QString::fromStdString(tag->album().to8Bit(true)));
        video->setIndex(i);
        m_videoListModel->addVideoModel(video);
        // videoModel .push_back(video);
    }
    // m_videoListModel=new ListVideoModel(videoModel);
    // m_proxyVideo->setSourceModel(m_videoListModel);
    playVideoList->addMedia(content);
    return videoList;

}

ListMusicModel *MediaController::musicListModel() const
{
    return m_musicListModel;
}

void MediaController::setMusicListModel(ListMusicModel *newMusicListModel)
{
    if (m_musicListModel == newMusicListModel)
        return;
    m_musicListModel = newMusicListModel;
    emit musicListModelChanged();
}



void MediaController::setMusicPlay()
{
    player->setPlaylist(playMusicList);

}

void MediaController::setSource(QString source)
{
    qDebug()<<"source"<<source;
    m_currentCoverArt=m_musicListModel->imageForTag(source);
}

void MediaController::playMusic(int index)
{
    playMusicList->setCurrentIndex(index);
    player->play();
}

int MediaController::index() const
{
    return m_index;
}

void MediaController::setIndex(int newIndex)
{
    qDebug()<<newIndex;
    if (m_index == newIndex)
        return;
    if(newIndex>playMusicList->mediaCount()-1)
    {

        m_index=newIndex-playMusicList->mediaCount();

    }
    else if(newIndex<0)
    {
        m_index=newIndex-playMusicList->mediaCount()-1;

    }
    else{
        m_index = newIndex;
    }

    emit indexChanged();
}

void MediaController::setVideoPlay()
{
    player->setPlaylist(playVideoList);

}

void MediaController::playVideo(int index)
{
    playVideoList->setCurrentIndex(index);
    player->play();
}



int MediaController::indexVideo() const
{
    return m_indexVideo;
}

void MediaController::setIndexVideo(int newIndexVideo)
{
    if (m_indexVideo == newIndexVideo)
        return;
    if(newIndexVideo>playVideoList->mediaCount()-1)
    {

        m_indexVideo=newIndexVideo-playVideoList->mediaCount();

    }
    else if(newIndexVideo<0)
    {
        m_indexVideo=newIndexVideo-playVideoList->mediaCount()-1;

    }
    else{
        m_indexVideo = newIndexVideo;
    }

    emit indexVideoChanged();
}
void MediaController::resumeMedia()
{
    player->play();


}
void MediaController::pauseMedia()
{
    player->pause();

}
void MediaController::seekBack()
{
    player->setPosition(player->position()-5000);
}
void MediaController::previousMedia()
{
    playMusicList->previous();
    playVideoList->previous();
    playMusicFavorit->previous();

}
void MediaController::nextMedia()
{
    playMusicList->next();
    playVideoList->next();
    playMusicFavorit->next();

}
void MediaController::seekForward()
{
    player->setPosition(player->position()+5000);
}

int MediaController::volume() const
{
    return player->volume();
}

void MediaController::setVolume(int newVolume)
{
    if (m_volume == newVolume)
        return;
    m_volume = newVolume;
    player->setVolume(newVolume);
    emit volumeChanged();
}



qint64 MediaController::position() const
{
    return player->position();
}

void MediaController::setPosition(qint64 newPosition)
{
    if (m_position == newPosition)
        return;
    m_position = newPosition;
    player->setPosition(newPosition);
    emit positionChanged();
}

qint64 MediaController::duration() const
{
    return player->duration();
}

void MediaController::setDuration(qint64 newDuration)
{
    if (m_duration == newDuration)
        return;
    m_duration = newDuration;
    emit durationChanged();
}

QAbstractVideoSurface *MediaController::videoSurface() const
{
    return m_videoSurface;
}

void MediaController::setVideoSurface(QAbstractVideoSurface *newVideoSurface)
{
    if (m_videoSurface == newVideoSurface)
        return;
    m_videoSurface = newVideoSurface;
    player->setVideoOutput(m_videoSurface);
    emit videoSurfaceChanged();
}

void MediaController::deletelMusic(int index)
{
    qDebug()<<"index delete"<<index;
    m_musicListModel->deletelMusicModel(index);
    playMusicList->removeMedia(index);
    if(playMusicList->currentIndex()==index)
    {
        player->stop();

    }
    else
    {
        player->play();
    }
}

void MediaController::deletelVideo(int index)
{
    m_videoListModel->deletelVideoModel(index);
    playVideoList->removeMedia(index);
}

void MediaController::setIndexMediaChanged()
{
    setIndex(playMusicList->currentIndex());
    setIndexVideo(playVideoList->currentIndex());
    setIndexFavor(playMusicFavorit->currentIndex());
    QModelIndex index = m_musicListModel->index(m_index,0);
    QVariant data = m_musicListModel->data(index,m_musicListModel->ListMusicModel::Songs::SourceSongs);
    QString source= data.toString();
    setSource(source);
}

QString MediaController::getMusicTitleArtist(int indexSong)
{
    qDebug()<<indexSong;
    QModelIndex index= m_musicListModel->index(indexSong,0);
    QVariant data= m_musicListModel->data(index,m_musicListModel->Songs::TitleSongs);
    QVariant data2= m_musicListModel->data(index,m_musicListModel->Songs::ArtistSongs);
    QString tilteSong= data.toString();
    QString artist= data2.toString();
    qDebug()<<tilteSong+"-"+artist;
    return tilteSong+"-"+artist;


}
QString MediaController::getFavoritTitleArtits(int indexSong)
{
    qDebug()<<"favorit next"<<indexSong;
    QModelIndex index= m_favoriteSongs->index(indexSong,0);
    QVariant data= m_favoriteSongs->data(index,m_favoriteSongs->Songs::TitleSongs);
    QVariant data2= m_favoriteSongs->data(index,m_favoriteSongs->Songs::ArtistSongs);
    QString tilteSong= data.toString();
    QString artist= data2.toString();
    qDebug()<<tilteSong+"-"+artist;
    return tilteSong+"-"+artist;


}

QString MediaController::getVideoTitleArtist(int indexSong)
{
    qDebug()<<"indexVideo"<<indexSong;
    QModelIndex index= m_videoListModel->index(indexSong,0);
    QVariant data= m_videoListModel->data(index,m_videoListModel->Songs::TitleVideo);
    QVariant data2= m_videoListModel->data(index,m_videoListModel->Songs::ArtistVideo);
    QString tilteSong= data.toString();
    QString artist= data2.toString();
    qDebug()<<tilteSong+"-"+artist;
    return tilteSong+"-"+artist;
}
void MediaController::shuffleMedia()
{
    if (playMusicList->isEmpty())
        return;
    playMusicList->setPlaybackMode(QMediaPlaylist::Random);
    playVideoList->setPlaybackMode(QMediaPlaylist::Random);
}
void MediaController::notShuffleMedia()
{
    if (playMusicList->isEmpty())
        return;
    playMusicList->setPlaybackMode(QMediaPlaylist::Sequential);
    playMusicList->setPlaybackMode(QMediaPlaylist::Loop);
    playVideoList->setPlaybackMode(QMediaPlaylist::Sequential);
    playVideoList->setPlaybackMode(QMediaPlaylist::Loop);
}
void MediaController::repeatMedia(int repeatIndex)
{

    if(repeatIndex==0)
    {

        playMusicList->setPlaybackMode(QMediaPlaylist::Sequential);
        playVideoList->setPlaybackMode(QMediaPlaylist::Sequential);
    }
    else if(repeatIndex==1)
    {
        playMusicList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        playVideoList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    }
    else if(repeatIndex==2){
        playMusicList->setPlaybackMode(QMediaPlaylist::Loop);
        playVideoList->setPlaybackMode(QMediaPlaylist::Loop);

    }

}
void MediaController::speedMedia(qreal rate)
{
    player->setPlaybackRate(rate);

}


QStringList MediaController::listSongPath() const
{
    return m_listSongPath;
}

void MediaController::setListSongPath(const QStringList &newListSongPath)
{
    if (m_listSongPath == newListSongPath)
        return;
    m_listSongPath = newListSongPath;
    emit listSongPathChanged();
}

QStringList MediaController::listVideoPath() const
{
    return m_listVideoPath;
}

void MediaController::setListVideoPath(const QStringList &newListVideoPath)
{
    if (m_listVideoPath == newListVideoPath)
        return;
    m_listVideoPath = newListVideoPath;
    emit listVideoPathChanged();
}

QString MediaController::songCoverArt()
{
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    m_currentCoverArt.save(&buffer,"png");
    QString base64 = buffer.data().toBase64();
    if(base64=="")
    {
        return "qrc:/assets/images/Spotify-Emblema.png";
    }
    QString ret= QString("data:image/png;base64,")+ base64;
    return ret;
}

ListVideoModel *MediaController::videoListModel() const
{
    return m_videoListModel;
}

void MediaController::setVideoListModel(ListVideoModel *newVideoListModel)
{
    if (m_videoListModel == newVideoListModel)
        return;
    m_videoListModel = newVideoListModel;
    emit videoListModelChanged();
}


QSortFilterProxyModel *MediaController::proxyVideo() const
{
    return m_proxyVideo;
}

void MediaController::setproxyVideo(QSortFilterProxyModel *newProxyVideo)
{
    if (m_proxyVideo == newProxyVideo)
        return;
    m_proxyVideo = newProxyVideo;
    emit proxyVideoChanged();
}

Favorite *MediaController::favoriteSongs() const
{
    return m_favoriteSongs;
}

void MediaController::setFavoriteSongs(Favorite *newFavoriteSongs)
{
    if (m_favoriteSongs == newFavoriteSongs)
        return;
    m_favoriteSongs = newFavoriteSongs;
    emit favoriteSongsChanged();
}

int MediaController::indexFavor() const
{
    return m_indexFavor;
}

void MediaController::setIndexFavor(int newIndexFavor)
{
    if (m_indexFavor == newIndexFavor)
        return;
    if(newIndexFavor>playMusicFavorit->mediaCount()-1)
    {

        m_indexFavor=newIndexFavor-playMusicFavorit->mediaCount();

    }
    else if(newIndexFavor<0)
    {
        m_indexFavor=newIndexFavor-playMusicFavorit->mediaCount()-1;

    }
    else{
        m_indexFavor = newIndexFavor;
    }

    emit indexFavorChanged();
}

void MediaController::addToFavorite(int index)
{
    // Lấy thông tin về bài hát từ index được chọ;
    CommonModel* data1=musicModel[index];
    QString fullPath= data1->getSource();
    QList<QMediaContent> content;
    m_favoriteSongs->addMusicFavor (data1);
    content.push_back(QMediaContent(QUrl::fromLocalFile(fullPath)));
    playMusicFavorit->addMedia(content);
    // Kích hoạt sự kiện hoặc thực hiện bất kỳ công việc nào liên quan đến việc cập nhật giao diện
    emit favoriteSongsChanged();
}
void MediaController::setFavoritMusicPlay()
{
    player->setPlaylist(playMusicFavorit);

}
void MediaController::setSourceFavor(QString source)
{
    //	m_currentCoverArt=m_favoriteSongs->imageForTag(source);//set source media to get cover art

}
void MediaController::playFavorit(int index)
{
    qDebug()<<"index list"<<index;
    qDebug()<<"index favor"<<index;
    playMusicFavorit->setCurrentIndex(index);
    player->play();

}
