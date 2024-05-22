#ifndef MEDIACONTROL_H
#define MEDIACONTROL_H

#include "Favorite.h"
#include "ListMusicModel.h"
#include "ListVideoModel.h"
#include "qcoreapplication.h"
#include "qimage.h"
#include "qmediaplayer.h"
#include <QObject>
#include <QDebug>
#include <QAbstractListModel>
#include <QSortFilterProxyModel>

class MediaController : public QObject
{
    Q_OBJECT


public:
    explicit MediaController(QObject *parent = nullptr);
    ~MediaController();


    Q_PROPERTY(QSortFilterProxyModel* proxyVideo READ proxyVideo WRITE setproxyVideo NOTIFY proxyVideoChanged FINAL)
    Q_PROPERTY(QAbstractVideoSurface* videoSurface READ videoSurface WRITE setVideoSurface NOTIFY videoSurfaceChanged FINAL)
    Q_PROPERTY(ListMusicModel* musicListModel READ musicListModel WRITE setMusicListModel NOTIFY musicListModelChanged FINAL)
    Q_PROPERTY(ListVideoModel* videoListModel READ videoListModel WRITE setVideoListModel NOTIFY videoListModelChanged FINAL)
    Q_PROPERTY(Favorite* favoriteSongs READ favoriteSongs WRITE setFavoriteSongs NOTIFY favoriteSongsChanged)
    Q_PROPERTY(Favorite* favoritVideos READ favoritVideos WRITE setFavoritVideos NOTIFY favoritVideosChanged)
    Q_PROPERTY(int index READ index WRITE setIndex NOTIFY indexChanged FINAL)
    Q_PROPERTY(int indexVideo READ indexVideo WRITE setIndexVideo NOTIFY indexVideoChanged FINAL)
    Q_PROPERTY(int indexFavor READ indexFavor WRITE setIndexFavor NOTIFY indexFavorChanged)
    Q_PROPERTY(int indexVideoFavor READ indexVideoFavor WRITE setIndexVideoFavor NOTIFY indexVideoFavorChanged)
    Q_PROPERTY(bool isMusicFavorit READ isMusicFavorit WRITE setIsMusicFavorit NOTIFY isMusicFavoritChanged FINAL)
    Q_PROPERTY(int volume READ volume WRITE setVolume NOTIFY volumeChanged FINAL)
    Q_PROPERTY(qint64 duration READ duration WRITE setDuration NOTIFY durationChanged FINAL)
    Q_PROPERTY(qint64 position READ position WRITE setPosition NOTIFY positionChanged FINAL)
    Q_PROPERTY(QStringList listSongPath READ listSongPath WRITE setListSongPath NOTIFY listSongPathChanged FINAL)
    Q_PROPERTY(QStringList listVideoPath READ listVideoPath WRITE setListVideoPath NOTIFY listVideoPathChanged FINAL)



    Q_INVOKABLE void getFolderMusic();
    Q_INVOKABLE void getFolderVideo();
    Q_INVOKABLE QVariantList getMusicLocal();
    Q_INVOKABLE QVariantList getVideoLocal();
    Q_INVOKABLE  void setIndex(int newIndex);
    Q_INVOKABLE void setIndexVideo(int newIndexVideo);
    Q_INVOKABLE  void setIndexFavor(int newIndexFavor);
    Q_INVOKABLE void setIndexVideoFavor(int newIndexVideoFavor);
    Q_INVOKABLE void resumeMedia();
    Q_INVOKABLE void pauseMedia();
    Q_INVOKABLE void previousMedia();
    Q_INVOKABLE void nextMedia();
    Q_INVOKABLE void seekForward();
    Q_INVOKABLE void seekBack();
    Q_INVOKABLE QString getMusicTitleArtist(int indexSong);
    Q_INVOKABLE QString getVideoTitleArtist(int indexSong);
    Q_INVOKABLE void shuffleMedia();
    Q_INVOKABLE void notShuffleMedia();
    Q_INVOKABLE void repeatMedia(int repeatIndex);
    Q_INVOKABLE void speedMedia(qreal repeatIndex);
    Q_INVOKABLE void setMusicPlay();
    Q_INVOKABLE void setVideoPlay();
    Q_INVOKABLE void setFavoritMusicPlay();
    Q_INVOKABLE void setFavoritVideoPlay();
    Q_INVOKABLE void playMusic(int index);
    Q_INVOKABLE void playVideo(int index);
    Q_INVOKABLE void playFavorit(int index);
    Q_INVOKABLE void playFavoritVideo(int index);
    Q_INVOKABLE void deletelMusic(int index);
    Q_INVOKABLE void deletelVideo(int index);
    Q_INVOKABLE QString songCoverArt();
    Q_INVOKABLE void setSource(QString source);
    Q_INVOKABLE void addToFavorite(int index);
    Q_INVOKABLE void addToFavoriteVideo(int index);
    Q_INVOKABLE QString getFavoritTitleArtits(int index);
    Q_INVOKABLE QString getFavoritVideoTitleArtits(int indexVideo);
    Q_INVOKABLE void deletelMusicFavorit(int index);
    Q_INVOKABLE void deletelVideoFavorit(int indexVideo);

    QAbstractVideoSurface *videoSurface() const;
    void setVideoSurface(QAbstractVideoSurface *newVideoSurface);
    void setListVideoPath(const QStringList &newListVideoPath);
    void setListSongPath(const QStringList &newListSongPath);
    void setVolume(int newVolume);
    void setPosition(qint64 newPosition);
    void setDuration(qint64 newDuration);
    QStringList listSongPath() const;
    QStringList listVideoPath() const;
    QSortFilterProxyModel* proxyVideo() const;
    ListMusicModel *musicListModel() const;
    ListVideoModel *videoListModel() const;
    Favorite *favoriteSongs() const;
    Favorite *favoritVideos() const;
    int volume() const;
    int indexVideo() const;
    int index() const;
    qint64 duartion() const;
    qint64 position() const;
    qint64 duration() const;
    void setMusicListModel(ListMusicModel *newMusicListModel);
    void setVideoListModel(ListVideoModel *newVideoListModel);
    void setFavoritVideos(Favorite *newFavoritVideos);
    void setFavoriteSongs(Favorite *newFavoriteSongs);
    void setproxyVideo( QSortFilterProxyModel *newProxyVideo);
    int indexFavor() const;
    int indexVideoFavor() const;
    bool isMusicFavorit() const;
    void setIsMusicFavorit(bool newIsMusicFavorit);

public slots:
    void setIndexMediaChanged();
    void setIndexFavoritMediaChanged();
signals:


    void musicListModelChanged();
    void videoListModelChanged();
    void favoriteSongsChanged();
    void favoritVideosChanged();
    void indexVideoFavorChanged();
    void isMusicFavoritChanged();

    void indexChanged();
    void indexVideoChanged();
    void indexFavorChanged();

    void volumeChanged();
    void positionChanged();
    void durationChanged();
    void videoSurfaceChanged();
    void listSongPathChanged();
    void listVideoPathChanged();
    void proxyVideoChanged();

private:
    QMediaPlayer* player ;

    QVector<CommonModel*> musicModel;
    QVector<CommonModel*> videoModel;
    ListMusicModel *m_musicListModel = nullptr;
    ListVideoModel *m_videoListModel = nullptr;
    Favorite *m_favoriteSongs = nullptr;
    Favorite *m_favoritVideos = nullptr;


    QMediaPlaylist *playMusicList;
    QMediaPlaylist *playVideoList;
    QMediaPlaylist *playMusicFavorit;
    QMediaPlaylist *playFavoritVideoList;

    int m_index;
    int m_indexVideo;
    int m_indexFavor;
    int m_indexVideoFavor;
    int m_volume;
    qint64 m_position;
    qint64 m_duration;
    QImage m_currentCoverArt;
    bool m_isMusicFavorit;

    QAbstractVideoSurface *m_videoSurface = nullptr;
    QSortFilterProxyModel* m_proxyVideo=nullptr;
    QStringList m_listSongPath;
    QStringList m_listVideoPath;
    QVariantList musicList;
    QVariantList videoList;


};

#endif
