
#include "MediaModel.h"
#include "Translator.h"
#include <QApplication>
#include <QQmlApplicationEngine>
#include<QQmlContext>
#include <QQuickView>
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    MediaController* mediaCtrl=new MediaController;
    QQmlContext *rootContext=engine.rootContext();
    rootContext->setContextProperty("mediaCtrl",mediaCtrl);
    Translator translator;
    rootContext->setContextProperty("Translator",&translator);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.load(url);
    return app.exec();
}


