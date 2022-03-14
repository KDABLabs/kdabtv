/* MIT License

Copyright (C) 2021 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <QDebug>
#include <QFlags>

namespace {
enum class PartyOption { BoringParty = 0x0, MakeIce = 0x1, BrewCoffee = 0x2, OpenBeers = 0x4 };

Q_DECLARE_FLAGS(PartyOptions, PartyOption)
Q_DECLARE_OPERATORS_FOR_FLAGS(PartyOptions)

void party(PartyOptions options)
{
    qDebug().noquote() << "Step 5: Lets Party, here are the jobs to do:\n"
                       << "Make Ice: " << (options.testFlag(PartyOption::MakeIce) ? "Yes" : "No")
                       << "\n"
                       << "Brew Coffee: "
                       << (options.testFlag(PartyOption::BrewCoffee) ? "Yes" : "No") << "\n"
                       << "Open Beers:"
                       << (options.testFlag(PartyOption::OpenBeers) ? "Yes" : "No");
}
}

void go5()
{
    party(PartyOption::BrewCoffee | PartyOption::OpenBeers);
}
