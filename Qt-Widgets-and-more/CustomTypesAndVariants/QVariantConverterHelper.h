#pragma once

#define QVARIANTMACRO                                                                              \
public:                                                                                            \
    inline operator QVariant() const { return QVariant::fromValue(*this); }                        \
                                                                                                   \
private:
