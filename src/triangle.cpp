#include "triangle.h"

Triangle::Triangle(QQuickItem *parent)
    : QQuickItem(parent)
{
    setFlag(QQuickItem::ItemHasContents, true);
    connect(this, &Triangle::x1Changed, this, &Triangle::update);
    connect(this, &Triangle::y1Changed, this, &Triangle::update);
    connect(this, &Triangle::x2Changed, this, &Triangle::update);
    connect(this, &Triangle::y2Changed, this, &Triangle::update);
    connect(this, &Triangle::x3Changed, this, &Triangle::update);
    connect(this, &Triangle::y3Changed, this, &Triangle::update);
}

QSGNode *Triangle::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *data)
{
    if (width() <= 0 || height() <= 0) {
        delete oldNode;
        return 0;
    }

    QSGGeometryNode *triangle = static_cast<QSGGeometryNode*>(oldNode);
    if (!triangle) {
        triangle = new QSGGeometryNode;
        triangle->setFlag(QSGNode::OwnsMaterial, true);
        triangle->setFlag(QSGNode::OwnsGeometry, true);
    }

    QSGGeometry *geometry = new QSGGeometry(
                QSGGeometry::defaultAttributes_Point2D(), 3);

    QSGGeometry::Point2D *points = geometry->vertexDataAsPoint2D();

    points[0].set(m_x1, m_y1);
    points[1].set(m_x2, m_y2);
    points[2].set(m_x3, m_y3);

    triangle->setGeometry(geometry);

    QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
    material->setColor(m_color);
    triangle->setMaterial(material);

    return triangle;
}
