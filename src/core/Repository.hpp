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