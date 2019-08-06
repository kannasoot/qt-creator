/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#pragma once

#include "directorypathid.h"
#include "filepath.h"
#include "filepathexceptions.h"
#include "filepathid.h"
#include "filepathstoragesources.h"
#include "filepathview.h"
#include "stringcache.h"

#include <algorithm>

namespace ClangBackEnd {

template<typename FilePathStorage, typename Mutex = SharedMutex>
class CLANGSUPPORT_GCCEXPORT FilePathCache
{
    FilePathCache(const FilePathCache &) = default;
    FilePathCache &operator=(const FilePathCache &) = default;

    template<typename Storage, typename M>
    friend class FilePathCache;

public:
    using DirectoryPathCache = StringCache<Utils::PathString,
                                           Utils::SmallStringView,
                                           int,
                                           Mutex,
                                           decltype(&Utils::reverseCompare),
                                           Utils::reverseCompare,
                                           Sources::Directory>;
    using FileNameCache = StringCache<FileNameEntry,
                                      FileNameView,
                                      int,
                                      Mutex,
                                      decltype(&FileNameView::compare),
                                      FileNameView::compare,
                                      Sources::Source>;

    FilePathCache(FilePathStorage &filePathStorage)
        : m_filePathStorage(filePathStorage)
    {
        m_directoryPathCache.populate(filePathStorage.fetchAllDirectories());
        m_fileNameCache.populate(filePathStorage.fetchAllSources());
    }

    FilePathCache(FilePathCache &&) = default;
    FilePathCache &operator=(FilePathCache &&) = default;

    template<typename Cache>
    Cache clone()
    {
        using DirectoryPathCache = typename Cache::DirectoryPathCache;
        using FileNameCache = typename Cache::FileNameCache;
        Cache cache{m_filePathStorage};
        cache.m_directoryPathCache = m_directoryPathCache.template clone<DirectoryPathCache>();
        cache.m_fileNameCache = m_fileNameCache.template clone<FileNameCache>();

        return cache;
    }

    FilePathId filePathId(FilePathView filePath) const
    {
        Utils::SmallStringView directoryPath = filePath.directory();

        int directoryId = m_directoryPathCache.stringId(
            directoryPath, [&](const Utils::SmallStringView directoryPath) {
                return m_filePathStorage.fetchDirectoryId(directoryPath);
            });

        Utils::SmallStringView fileName = filePath.name();

        int fileNameId = m_fileNameCache.stringId({fileName, directoryId},
                                                  [&] (const FileNameView) {
            return m_filePathStorage.fetchSourceId(directoryId, fileName);
        });

        return fileNameId;
    }

    DirectoryPathId directoryPathId(Utils::SmallStringView directoryPath) const
    {
        Utils::SmallStringView path = directoryPath.back() == '/'
                                          ? directoryPath.mid(0, directoryPath.size() - 1)
                                          : directoryPath;

        return m_directoryPathCache.stringId(path, [&](const Utils::SmallStringView directoryPath) {
            return m_filePathStorage.fetchDirectoryId(directoryPath);
        });
    }

    FilePath filePath(FilePathId filePathId) const
    {
        if (Q_UNLIKELY(!filePathId.isValid()))
            throw NoFilePathForInvalidFilePathId();

        auto fetchSoureNameAndDirectoryId = [&] (int id) {
            auto entry = m_filePathStorage.fetchSourceNameAndDirectoryId(id);
            return FileNameEntry{entry.sourceName, entry.directoryId};
        };

        FileNameEntry entry = m_fileNameCache.string(filePathId.filePathId,
                                                     fetchSoureNameAndDirectoryId);

        auto fetchDirectoryPath = [&] (int id) { return m_filePathStorage.fetchDirectoryPath(id); };

        Utils::PathString directoryPath = m_directoryPathCache.string(entry.directoryId,
                                                                      fetchDirectoryPath);

        return FilePath{directoryPath, entry.fileName};
    }

    Utils::PathString directoryPath(DirectoryPathId directoryPathId) const
    {
        if (Q_UNLIKELY(!directoryPathId.isValid()))
            throw NoDirectoryPathForInvalidDirectoryPathId();

        auto fetchDirectoryPath = [&](int id) { return m_filePathStorage.fetchDirectoryPath(id); };

        return m_directoryPathCache.string(directoryPathId.directoryPathId, fetchDirectoryPath);
    }

    DirectoryPathId directoryPathId(FilePathId filePathId) const
    {
        if (Q_UNLIKELY(!filePathId.isValid()))
            throw NoFilePathForInvalidFilePathId();

        auto fetchSoureNameAndDirectoryId = [&](int id) {
            auto entry = m_filePathStorage.fetchSourceNameAndDirectoryId(id);
            return FileNameEntry{entry.sourceName, entry.directoryId};
        };

        FileNameEntry entry = m_fileNameCache.string(filePathId.filePathId,
                                                     fetchSoureNameAndDirectoryId);

        return m_fileNameCache.string(filePathId.filePathId, fetchSoureNameAndDirectoryId).directoryId;
    }

private:
    mutable DirectoryPathCache m_directoryPathCache;
    mutable FileNameCache m_fileNameCache;
    FilePathStorage &m_filePathStorage;
};

} // namespace ClangBackEnd
