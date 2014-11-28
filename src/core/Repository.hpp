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

#pragma once

#include <git2/repository.h>

namespace boost {
    namespace filesystem {
        class path;
    }
}

namespace tkacz {
    class Repository {
    public:

        Repository(const boost::filesystem::path & path);
        static Repository initialize (const boost::filesystem::path & path, bool force=false);

        /**
         * @brief Locks this repository against concurrent writing.
         * @param timeout Give up after this number of milliseconds.
         * @param retryInterval Interval (in milliseconds) between attempts.
         * @param force Force release any existing lock.
         * @return True if a lock was held or acquired.
         */
        bool lock(int timeout=0, int retryInterval=100, bool force=false);
        /**
         * @brief Locks this repository against concurrent writing.
         * @param force Release any lock, even if owned by another process.
         * @return True if the repository has been unlocked
         */
        bool releaseLock(bool force=false);

    private:
        const git_repository * _git_repository;

    };
}