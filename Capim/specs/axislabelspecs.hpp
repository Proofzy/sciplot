// Capim - a modern C++ plotting library powered by gnuplot
// https://github.com/allanleal/capim
//
// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
//
// Copyright (c) 2018 Allan Leal
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

// Capim includes
#include <Capim/default.hpp>
#include <Capim/specs/fontspecs.hpp>
#include <Capim/specs/textspecs.hpp>
#include <Capim/util.hpp>

namespace Capim {
namespace internal {

/// The specifications for an axis label (e.g., xlabel, ylabel, etc.)
class axislabelspecs : public textspecs<axislabelspecs>
{
public:
    /// Construct a default axislabelspecs instance.
    axislabelspecs(std::string axis);

    /// Convert this axislabelspecs object into a gnuplot formatted string.
    auto repr() const -> std::string;

    /// Set the offset of the label.
    /// @param xval The offset along the x direction
    /// @param yval The offset along the y direction
    auto offset(int xval, int yval) -> axislabelspecs& { m_offset = str(xval) + "," + str(yval); return *this; }

    /// Set the rotation angle of the label in degrees.
    auto rotate(double angle) -> axislabelspecs& { m_rotate = "by " + str(angle); return *this; }

    /// Set the axis label parallel to its corresponding axis.
    auto axisparallel() -> axislabelspecs& { m_rotate = "parallel"; return *this; }

private:
    /// The name of the axis (e.g., `"x"`, `"y"`, `"z"`)
    std::string m_axis;

    /// The offset used to move the label around.
    std::string m_offset;

    /// The rotation command to rotate the label around.
    std::string m_rotate;
};

axislabelspecs::axislabelspecs(std::string axis)
: m_axis(axis)
{
}

auto axislabelspecs::repr() const -> std::string
{
    std::stringstream ss;
    ss << "set " + m_axis + "label ";
    ss << textspecs<axislabelspecs>::repr();
    ss << fontspecs<axislabelspecs>::repr();
    ss << optionvaluestr("offset", m_offset);
    ss << optionvaluestr("rotate", m_rotate);
    return ss.str();
}

} // namespace internal
} // namespace Capim
