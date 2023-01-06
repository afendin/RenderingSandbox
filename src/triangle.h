#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QtQuick>
#include "QQmlHelpers"

class Triangle : public QQuickItem
{
    Q_OBJECT
    QML_WRITABLE_PROPERTY(double, x1)
    QML_WRITABLE_PROPERTY(double, y1)
    QML_WRITABLE_PROPERTY(double, x2)
    QML_WRITABLE_PROPERTY(double, y2)
    QML_WRITABLE_PROPERTY(double, x3)
    QML_WRITABLE_PROPERTY(double, y3)
    QML_WRITABLE_PROPERTY(QColor, color)
public:
    Triangle(QQuickItem *parent = nullptr);
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *data) override;

signals:

};

#endif // TRIANGLE_H
