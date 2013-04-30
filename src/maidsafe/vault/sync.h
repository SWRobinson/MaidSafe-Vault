/***************************************************************************************************
 *  Copyright 2013 MaidSafe.net limited                                                            *
 *                                                                                                 *
 *  The following source code is property of MaidSafe.net limited and is not meant for external    *
 *  use.  The use of this code is governed by the licence file licence.txt found in the root of    *
 *  this directory and also on www.maidsafe.net.                                                   *
 *                                                                                                 *
 *  You are not free to copy, amend or otherwise use this source code without the explicit         *
 *  written permission of the board of directors of MaidSafe.net.                                  *
 **************************************************************************************************/

#ifndef MAIDSAFE_VAULT_SYNC_H_
#define MAIDSAFE_VAULT_SYNC_H_

#include <cstdint>
#include <vector>

#include "maidsafe/common/node_id.h"


namespace maidsafe {

namespace vault {

class AccountDb;
// Purpose of this object is to ensure enough nodes have agreed the message is valid

template<typename MergePolicy>
class Sync : public MergePolicy {
 public:
  Sync(AccountDb* account_db, const NodeId& this_node_id);
  Sync(Sync&& other);
  Sync& operator=(Sync&& other);
  // This is called when receiving a Sync message from a peer or this node.  Returns true if the
  // entry becomes resolved.
  bool AddUnresolvedEntry(typename MergePolicy::UnresolvedEntry& entry, const NodeId& node_id);
  void AddLocalEntry(typename MergePolicy::UnresolvedEntry& entry);
  // Returns true if the entry becomes resolved
  bool AddAccountTransferRecord(typename MergePolicy::UnresolvedEntry& entry,
                                const NodeId& node_id,
                                bool all_account_transfers_received);
  void ReplaceNode(const NodeId& old_node, const NodeId& new_node);
  std::vector<typename MergePolicy::UnresolvedEntry> GetUnresolvedData() const;
  size_t GetUnresolvedCount() const { return MergePolicy::unresolved_data_.size(); }
  // int32_t sync_counter_max() const { return sync_counter_max_; }
  // void set_sync_counter_max(int32_t new_count) { sync_counter_max_ = new_count; }

  // Calling this will increment the sync counter and delete entries that reach the
  // 'sync_counter_max_' limit.
  void IncrementSyncAttmepts();

 private:
  Sync(const Sync&);
  Sync& operator=(const Sync&);
  typename std::vector<typename MergePolicy::UnresolvedEntry>::iterator FindUnresolved(
      const typename MergePolicy::UnresolvedEntry::Key& key_to_find);
  int32_t sync_counter_max_;
  NodeId this_node_id_;
};

}  // namespace vault

}  // namespace maidsafe

#include "maidsafe/vault/sync-inl.h"

#endif  // MAIDSAFE_VAULT_SYNC_H_
