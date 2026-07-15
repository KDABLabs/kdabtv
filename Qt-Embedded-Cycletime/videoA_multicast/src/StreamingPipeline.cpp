#include <StreamingPipeline.hpp>

#include <QRunnable>
#include <QQuickWindow>

class SetPlaying : public QRunnable
{
public:
    SetPlaying(GstElement *pipeline, bool playing)
        : m_pipeline(pipeline ? static_cast<GstElement*>(gst_object_ref(pipeline)) : nullptr)
        , m_playing(playing)
    {
    }

    ~SetPlaying()
    {
        if (m_pipeline)
            gst_object_unref(m_pipeline);
    }

    void run()
    {
        if (m_pipeline) {
            gst_element_set_state(m_pipeline, m_playing ? GST_STATE_PLAYING : GST_STATE_PAUSED);
        }
    }

private:
    GstElement *m_pipeline;
    bool m_playing;
};


StreamingPipeline::StreamingPipeline(QQuickWindow *quickWindow, const QString &webRootPath)
    : m_window(quickWindow)
    , m_pipeline(nullptr)
{
    gst_init(nullptr, nullptr);

    auto *pipeline = gst_parse_launch("qml6glsrc name=src ! glvideoflip video-direction=auto ! gldownload ! videoconvert ! webrtcsink name=sink", nullptr);
    if (!pipeline)
        qFatal("Unable to create gstreamer pipeline");

    auto *src = gst_bin_get_by_name(GST_BIN(pipeline), "src");
    auto *sink = gst_bin_get_by_name(GST_BIN(pipeline), "sink");

    g_object_set(src, "window", m_window, nullptr);
    g_object_set(src, "use-default-fbo", TRUE, nullptr);
    g_object_set(src, "view-only", FALSE, nullptr);
    g_object_set(src, "do-timestamp", TRUE, nullptr);

    g_object_set(sink, "stun-server", nullptr, nullptr);
    g_object_set(sink, "run-signalling-server", TRUE, nullptr);
    g_object_set(sink, "enable-control-data-channel", TRUE, nullptr);
    g_object_set(sink, "run-web-server", TRUE, nullptr);
    g_object_set(sink, "web-server-directory", qPrintable(webRootPath), nullptr);

    m_pipeline = pipeline;
}

StreamingPipeline::~StreamingPipeline()
{
    if (m_pipeline) {
        gst_element_set_state(m_pipeline, GST_STATE_NULL);
        gst_object_unref(m_pipeline);
    }

    gst_deinit();
}

void StreamingPipeline::start()
{
    m_window->scheduleRenderJob(new SetPlaying(m_pipeline, true), QQuickWindow::BeforeSynchronizingStage);
    m_window->update();
}

void StreamingPipeline::stop()
{
    m_window->scheduleRenderJob(new SetPlaying(m_pipeline, false), QQuickWindow::BeforeSynchronizingStage);
    m_window->update();
}
