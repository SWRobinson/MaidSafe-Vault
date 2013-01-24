/***************************************************************************************************
 *  Copyright 2012 MaidSafe.net limited                                                            *
 *                                                                                                 *
 *  The following source code is property of MaidSafe.net limited and is not meant for external    *
 *  use.  The use of this code is governed by the licence file licence.txt found in the root of    *
 *  this directory and also on www.maidsafe.net.                                                   *
 *                                                                                                 *
 *  You are not free to copy, amend or otherwise use this source code without the explicit         *
 *  written permission of the board of directors of MaidSafe.net.                                  *
 **************************************************************************************************/

#ifndef MAIDSAFE_VAULT_PMID_ACCOUNT_H_
#define MAIDSAFE_VAULT_PMID_ACCOUNT_H_

#include <map>

#include "boost/filesystem/path.hpp"

#include "maidsafe/common/types.h"

#include "maidsafe/vault/disk_based_storage.h"
#include "maidsafe/vault/pmid_record.h"
#include "maidsafe/vault/types.h"


namespace maidsafe {

namespace vault {

class PmidAccount {
 public:
  typedef PmidName name_type;
  typedef TaggedValue<NonEmptyString, struct SerialisedMaidAccountTag> serialised_type;
  PmidAccount(const PmidName& pmid_name, const boost::filesystem::path& root);
  PmidAccount(const serialised_type& serialised_pmid_account, const boost::filesystem::path& root);
  serialised_type Serialise() const;



 private:
  PmidAccount(const PmidAccount&);
  PmidAccount& operator=(const PmidAccount&);
  PmidAccount(PmidAccount&&);
  PmidAccount& operator=(PmidAccount&&);
  PmidRecord pmid_record_;
  std::map<DataNameVariant, int32_t> recent_data_stored_;
  DiskBasedStorage archive_;
};

}  // namespace vault

}  // namespace maidsafe

#endif  // MAIDSAFE_VAULT_PMID_ACCOUNT_H_