#pragma once

#include <QString>

#include <gst/gst.h>

class QQuickWindow;

class StreamingPipeline
{
public:
    explicit StreamingPipeline(QQuickWindow *quickWindow, const QString &webRootPath);
    ~StreamingPipeline();

    void start();
    void stop();

private:
    QQuickWindow *m_window;
    GstElement *m_pipeline;
};
