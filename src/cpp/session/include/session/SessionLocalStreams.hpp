/*
 * SessionLocalStreams.hpp
 *
 * Copyright (C) 2009-18 by RStudio, Inc.
 *
 * Unless you have received this program directly from RStudio pursuant
 * to the terms of a commercial license agreement with RStudio, then
 * this program is licensed to you under the terms of version 3 of the
 * GNU Affero General Public License. This program is distributed WITHOUT
 * ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING THOSE OF NON-INFRINGEMENT,
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Please refer to the
 * AGPL (http://www.gnu.org/licenses/agpl-3.0.txt) for more details.
 *
 */

#ifndef SESSION_LOCAL_STREAMS_HPP
#define SESSION_LOCAL_STREAMS_HPP

#include <string>

#include <core/Error.hpp>
#include <core/FilePath.hpp>

#include <core/system/Environment.hpp>
#include <core/system/System.hpp>

#include <core/http/LocalStreamSocketUtils.hpp>

#define kSessionTmpDirEnvVar     "RS_SESSION_TMP_DIR"

namespace rstudio {
namespace session {
namespace local_streams {

inline core::Error ensureStreamsDir()
{
   core::FilePath sessionStreamsPath(core::system::getenv(kSessionTmpDirEnvVar));
   return core::http::initializeStreamDir(sessionStreamsPath);
}
   
inline core::FilePath streamPath(const std::string& file)
{
   core::FilePath sessionStreamsPath(core::system::getenv(kSessionTmpDirEnvVar));
   core::FilePath path = sessionStreamsPath.complete(file);
   core::Error error = core::http::initializeStreamDir(path.parent());
   if (error)
      LOG_ERROR(error);
   return path;
}

} // namespace local_streams
} // namepspace session
} // namespace rstudio

#endif // SESSION_LOCAL_STREAMS_HPP


