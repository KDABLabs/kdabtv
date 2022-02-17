set(KDChatAppBack_SRCS
    root.cpp
    root.h
    kdchatappback.cpp
    kdchatappback.h
    ${TEMPLATES_SRC}
)

# Create the application
add_library(KDChatAppBack SHARED ${KDChatAppBack_SRCS})

# Link to Cutelyst
target_link_libraries(KDChatAppBack
    Cutelyst::Core
    ASqlQt5::Core # link to ASql
    ASqlQt5::Pg # link to ASql Postgres Driver
    FirebaseAdminQt5::Core
    Qt5::Core
    Qt5::Network
)
