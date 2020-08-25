#include "projectcoordinateshelper.h"
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QCameraLens>

ProjectCoordinatesHelper::ProjectCoordinatesHelper(QObject *parent)
    : QObject(parent)
{
    QObject::connect(this, &ProjectCoordinatesHelper::worldMatrixChanged,
                     this, &ProjectCoordinatesHelper::updateScreenPosition);
    QObject::connect(this, &ProjectCoordinatesHelper::widthChanged,
                     this, &ProjectCoordinatesHelper::updateScreenPosition);
    QObject::connect(this, &ProjectCoordinatesHelper::heightChanged,
                     this, &ProjectCoordinatesHelper::updateScreenPosition);
}

Qt3DCore::QEntity *ProjectCoordinatesHelper::camera() const
{
    return m_camera;
}

QMatrix4x4 ProjectCoordinatesHelper::worldMatrix() const
{
    return m_worldMatrix;
}

QVector2D ProjectCoordinatesHelper::screenPosition() const
{
    return m_screenPosition;
}

int ProjectCoordinatesHelper::width() const
{
    return m_width;
}

int ProjectCoordinatesHelper::height() const
{
    return m_height;
}

void ProjectCoordinatesHelper::setCamera(Qt3DCore::QEntity *camera)
{
    if (m_camera == camera)
        return;

    if (m_cameraTransform) {
        QObject::disconnect(m_cameraTransform, &Qt3DCore::QTransform::worldMatrixChanged,
                            this, &ProjectCoordinatesHelper::updateScreenPosition);
        m_cameraTransform = nullptr;
    }

    if (m_cameraLens) {
        QObject::disconnect(m_cameraLens, &Qt3DRender::QCameraLens::projectionMatrixChanged,
                            this, &ProjectCoordinatesHelper::updateScreenPosition);
        m_cameraLens = nullptr;
    }

    m_camera = camera;

    if (m_camera) {
        const auto transforms = m_camera->componentsOfType<Qt3DCore::QTransform>();
        m_cameraTransform = transforms.size() > 0 ? transforms.first() : nullptr;
        const auto lenses = m_camera->componentsOfType<Qt3DRender::QCameraLens>();
        m_cameraLens = lenses.size() > 0 ? lenses.first() : nullptr;

        if (m_cameraTransform)
            QObject::connect(m_cameraTransform, &Qt3DCore::QTransform::worldMatrixChanged,
                             this, &ProjectCoordinatesHelper::updateScreenPosition);

        if (m_cameraLens)
            QObject::connect(m_cameraLens, &Qt3DRender::QCameraLens::projectionMatrixChanged,
                             this, &ProjectCoordinatesHelper::updateScreenPosition);
    }

    emit cameraChanged();
}

void ProjectCoordinatesHelper::setWorldMatrix(const QMatrix4x4 &worldMatrix)
{
    if (m_worldMatrix == worldMatrix)
        return;

    m_worldMatrix = worldMatrix;
    emit worldMatrixChanged();
}

void ProjectCoordinatesHelper::setWidth(int width)
{
    if (m_width == width)
        return;

    m_width = width;
    emit widthChanged();
}

void ProjectCoordinatesHelper::setHeight(int height)
{
    if (m_height == height)
        return;

    m_height = height;
    emit heightChanged();
}

void ProjectCoordinatesHelper::updateScreenPosition()
{
    const QMatrix4x4 projectionMatrix = (m_cameraLens) ? m_cameraLens->projectionMatrix() : QMatrix4x4();
    const QMatrix4x4 viewMatrix = (m_cameraTransform) ? m_cameraTransform-> worldMatrix().inverted() : QMatrix4x4();
    const QVector3D projectedPoint = QVector3D().project(viewMatrix * m_worldMatrix,
                                                         projectionMatrix,
                                                         QRect(0, 0, m_width, m_height)).toVector2D();

    m_screenPosition = QVector2D(projectedPoint.x(), m_height - projectedPoint.y());
    emit screenPositionChanged();
}
