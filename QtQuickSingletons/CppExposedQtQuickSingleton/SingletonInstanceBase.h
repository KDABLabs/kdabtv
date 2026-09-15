#pragma once

#include <QObject>
#include <QQmlEngine>


template <typename Singleton>
class SingletonInstanceBase: public QObject {
public:
    SingletonInstanceBase(QObject* parent)
        :QObject(parent)
    {
        static_assert(!std::is_default_constructible<Singleton>::value,
                      "Don't use a default-constructable type, as the QML "
                      "engine won't use the provided instance then.");

        const auto ptr = singletonInstance(this);
        Q_UNUSED(ptr);
    }

    ~SingletonInstanceBase()
    {
        // s_singletonBaseInstance = nullptr;
    }

    using Base = SingletonInstanceBase<Singleton>;

    static Singleton *create(QQmlEngine *, QJSEngine *engine)
    {
        static QJSEngine *s_engine = nullptr;

        // The instance has to exist before it is used. We cannot replace it.
        Q_ASSERT(singletonInstance());

        // The engine has to have the same thread affinity as the singleton.
        Q_ASSERT(engine->thread() == singletonInstance()->thread());

        // There can only be one engine accessing the singleton.
        if (s_engine)
            Q_ASSERT(engine == s_engine);
        else
            s_engine = engine;

        // Explicitly specify C++ ownership so that the engine doesn't delete
        // the instance.
        QJSEngine::setObjectOwnership(singletonInstance(),
                                      QJSEngine::CppOwnership);
        return singletonInstance();
    }

private:
    static Singleton* singletonInstance(SingletonInstanceBase* baseInstance = nullptr)
    {
        static SingletonInstanceBase *s_singletonBaseInstance = nullptr;
        if (baseInstance) {
            Q_ASSERT (s_singletonBaseInstance == nullptr);
            s_singletonBaseInstance = baseInstance;
            return nullptr; //it's unsafe to return the actual casted instance at this point, as we're still constructing it
        }
        // before first use, the singleton must be instantiated
        Q_ASSERT(s_singletonBaseInstance);
        return static_cast<Singleton*>(s_singletonBaseInstance);
    }
};
