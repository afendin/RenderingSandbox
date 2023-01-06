#ifndef TRIANGLESTRUCT_H
#define TRIANGLESTRUCT_H

#include <QObject>
#include <QColor>
#include "QQmlHelpers"

class TriangleStruct : public QObject
{
    Q_OBJECT
    QML_WRITABLE_PROPERTY(double, x1)
    QML_WRITABLE_PROPERTY(double, y1)
    QML_WRITABLE_PROPERTY(double, z1)
    QML_WRITABLE_PROPERTY(double, x2)
    QML_WRITABLE_PROPERTY(double, y2)
    QML_WRITABLE_PROPERTY(double, z2)
    QML_WRITABLE_PROPERTY(double, x3)
    QML_WRITABLE_PROPERTY(double, y3)
    QML_WRITABLE_PROPERTY(double, z3)
    QML_WRITABLE_PROPERTY(QColor, color)
public:
    explicit TriangleStruct(const QList<double> &coords = QList<double>(),
                            const QColor &color = QColor(),
                            QObject *parent = nullptr);

signals:

};

#endif // TRIANGLESTRUCT_H
