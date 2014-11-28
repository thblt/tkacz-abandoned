/*                                                                 [licblock]
 * This file is part of Tkacz. 
 * Copyright (c) 2012-2014 Thibault Polge. All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *                                                                [/licblock] */

#include <iostream>

#include <boost/python.hpp>

#include "TZProperty.hpp"

namespace bpy = boost::python;

namespace tkacz {

    template <typename T>
    TZProperty<T>::TZProperty(T * value) {
        value = value;
    }

    class Test {
    public:
        void hello() {
            std::cout << "Hello, world!\n";
        }
    };

    BOOST_PYTHON_MODULE(tkacz) {
        bpy::class_<Test>("TZTest")
        .def("hello", &Test::hello);
    }

}