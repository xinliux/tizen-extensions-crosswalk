// Copyright (c) 2014 Samsung Electronics Co., Ltd All Rights Reserved
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DATASYNC_DATASYNC_MANAGER_H_
#define DATASYNC_DATASYNC_MANAGER_H_

#include <sync_agent.h>

#include <map>
#include <string>

#include "common/utils.h"
#include "datasync/datasync_error.h"
#include "datasync/sync_profile_info.h"
#include "datasync/sync_statistics.h"

namespace datasync {

class DatasyncInstance;

class DataSyncManager {
 public:
  typedef std::map<int, int> ProfileIdToCallbackIdMap;

  explicit DataSyncManager(DatasyncInstance& parent);
  ~DataSyncManager();

  ResultOrError<std::string> Add(SyncProfileInfo& profile_info);
  ResultOrError<void> Update(SyncProfileInfo& profile_info);
  ResultOrError<void> Remove(const std::string& id);

  ResultOrError<unsigned> GetMaxProfilesNum() const;
  ResultOrError<unsigned> GetProfilesNum() const;

  ResultOrError<SyncProfileInfoPtr> Get(
      const std::string& profile_id) const;
  ResultOrError<SyncProfileInfoListPtr> GetAll() const;
  ResultOrError<SyncStatisticsListPtr> GetLastSyncStatistics(
      const std::string& profile_str_id) const;

  ResultOrError<void> StartSync(
      const std::string& profile_id_str, int callback_id);
  ResultOrError<void> StopSync(const std::string& profile_id_str);

 private:
  int StateChangedCallback(sync_agent_event_data_s* request);
  int ProgressCallback(sync_agent_event_data_s* request);

  DatasyncInstance& instance_;
  ProfileIdToCallbackIdMap callbacks_;

  static bool sync_agent_initialized_;

  DISALLOW_COPY_AND_ASSIGN(DataSyncManager);
};

}  // namespace datasync

#endif  // DATASYNC_DATASYNC_MANAGER_H_
