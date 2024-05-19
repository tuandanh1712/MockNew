#ifndef FAVORITE_H
#define FAVORITE_H

#include "CommonModel.h"
#include <QAbstractListModel>
#include <QObject>

class Favorite : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit Favorite(QObject *parent = nullptr);
    Q_PROPERTY(QVector<CommonModel*> listFavor READ listFavor WRITE setListFavor NOTIFY listFavorChanged)
    enum Songs {
        TitleSongs = Qt::UserRole+1,
        ArtistSongs,
        AlbumSongs,
        SourceSongs,
        IndexSongs,
        //Duration,
    };
    ~Favorite();

    int rowCount(const QModelIndex& parent) const override;
    QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;
    QHash<int, QByteArray> roleNames() const override;
    void removeFavor(int index);
    void addMusicFavor(CommonModel *data);
    QVector<CommonModel*> getlistFavor();

    QVector<CommonModel *> listFavor() const;
    void setListFavor(const QVector<CommonModel *> &newListFavor);

signals:
    void listFavorChanged();

private:

    QVector<CommonModel *> m_listFavor;
};

#endif // FAVORITE_H
