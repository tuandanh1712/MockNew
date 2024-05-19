#ifndef LISTVIDEOMODEL_H
#define LISTVIDEOMODEL_H
#include "CommonModel.h"
#include <QObject>
#include <QVector>
#include <QDir>
#include <QByteArray>
#include <QStandardPaths>
#include <QDebug>
#include <QAbstractListModel>
#include <QBuffer>
#include <taglib/tag.h>
#include <taglib/fileref.h>




class ListVideoModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ListVideoModel(QObject *parent = nullptr);
    enum Songs {
        TitleVideo = Qt::UserRole+1,
        ArtistVideo,
        AlbumVideo,
        SourceVideo,
        IndexVideo,
    };
    ~ListVideoModel();

    int rowCount(const QModelIndex& parent) const override;

    QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;
    QHash<int, QByteArray> roleNames() const override;
    void deletelVideoModel(int index);
    void addVideoModel(CommonModel *data);

signals:


private:
    QVector<CommonModel*> m_listVideo;

};

#endif
