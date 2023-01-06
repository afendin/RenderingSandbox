#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include <QObject>
#include "trianglestruct.h"

#include "QQmlHelpers"
#include "QQmlObjectListModel"

#define DRAW_QMLNAME "DrawManager"

class DrawManager : public QObject
{
    Q_OBJECT
    QML_READONLY_PROPERTY(QQmlObjectListModel<TriangleStruct> *, drawingModel)

public:
    explicit DrawManager(QObject *parent = nullptr);

public slots:
    void parseFile();
};

#endif // DRAWMANAGER_H
