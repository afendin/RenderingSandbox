#include "trianglestruct.h"

TriangleStruct::TriangleStruct(const QList<double> &coords, const QColor &color, QObject *parent)
    : QObject{parent}
{
    m_x1 = coords[0];
    m_y1 = coords[1];
    m_z1 = coords[2];
    m_x2 = coords[3];
    m_y2 = coords[4];
    m_z2 = coords[5];
    m_x3 = coords[6];
    m_y3 = coords[7];
    m_z3 = coords[8];
    m_color = color;
}
