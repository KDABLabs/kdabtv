#ifndef PROJECTCOORDINATESHELPER_H
#define PROJECTCOORDINATESHELPER_H

#include <QObject>
#include <Qt3DCore/QEntity>
#include <QMatrix4x4>
#include <QVector3D>
#include <QVector2D>

namespace Qt3DCore {
class QTransform;
}

namespace Qt3DRender {
class QCameraLens;
}

class ProjectCoordinatesHelper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Qt3DCore::QEntity *camera READ camera WRITE setCamera NOTIFY cameraChanged)
    Q_PROPERTY(QMatrix4x4 worldMatrix WRITE setWorldMatrix READ worldMatrix NOTIFY worldMatrixChanged)
    Q_PROPERTY(QVector2D screenPosition READ screenPosition NOTIFY screenPositionChanged)
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
public:
    explicit ProjectCoordinatesHelper(QObject *parent = nullptr);

    Qt3DCore::QEntity *camera() const;
    QMatrix4x4 worldMatrix() const;
    QVector2D screenPosition() const;

    int width() const;

    int height() const;

public slots:
    void setCamera(Qt3DCore::QEntity * camera);
    void setWorldMatrix(const QMatrix4x4 &worldMatrix);
    void setWidth(int width);
    void setHeight(int height);

Q_SIGNALS:
    void cameraChanged();
    void worldMatrixChanged();
    void screenPositionChanged();
    void widthChanged();
    void heightChanged();

private:
    void updateScreenPosition();

    Qt3DCore::QEntity *m_camera = nullptr;
    Qt3DCore::QTransform *m_cameraTransform = nullptr;
    Qt3DRender::QCameraLens *m_cameraLens = nullptr;

    QMatrix4x4 m_worldMatrix;
    QVector2D m_screenPosition;
    int m_width;
    int m_height;
};

#endif // PROJECTCOORDINATESHELPER_H
