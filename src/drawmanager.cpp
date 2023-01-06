#include <QTimer>
#include <QFile>
#include "drawmanager.h"
#include "3rdparty/tinyrenderer/model.h"

DrawManager::DrawManager(QObject *parent)
    : QObject{parent}
{
    m_drawingModel = new QQmlObjectListModel<TriangleStruct>(this);
}

void DrawManager::parseFile()
{
//    QFile file(":/obj/african_head.obj");
//    if (!file.open(QIODevice::ReadOnly)){
//        qDebug() << file.errorString();
//        return;
//    }
    Model *model = new Model("obj/african_head.obj");
    Vec3f light_dir(0,0,-1);

    for (int i=0; i<model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        Vec3f world_coords[3];
        QList<double> coords;
        for (int j=0; j<3; j++) {
            Vec3f v = model->vert(face[j]);
            coords << v.x << v.y << v.z;
            world_coords[j]  = v;
        }

        Vec3f n = (world_coords[2]-world_coords[0])^(world_coords[1]-world_coords[0]);

        n.normalize();
        float intensity = n*light_dir;

        QColor color;

        if (intensity > 0) {
            color.setRedF(intensity);
            color.setGreenF(intensity);
            color.setBlueF(intensity);
            color.setAlpha(255);
        }

        m_drawingModel->append(new TriangleStruct(coords, color));
    }
}
