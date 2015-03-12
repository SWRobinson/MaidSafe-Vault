/*  Copyright 2015 MaidSafe.net limited

    This MaidSafe Software is licensed to you under (1) the MaidSafe.net Commercial License,
    version 1.0 or later, or (2) The General Public License (GPL), version 3, depending on which
    licence you accepted on initial access to the Software (the "Licences").

    By contributing code to the MaidSafe Software, or to this project generally, you agree to be
    bound by the terms of the MaidSafe Contributor Agreement, version 1.0, found in the root
    directory of this project at LICENSE, COPYING and CONTRIBUTOR respectively and also
    available at: http://www.maidsafe.net/licenses

    Unless required by applicable law or agreed to in writing, the MaidSafe Software distributed
    under the GPL Licence is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS
    OF ANY KIND, either express or implied.

    See the Licences for the specific language governing permissions and limitations relating to
    use of the MaidSafe Software.                                                                 */

#include "maidsafe/vault/mpid_manager/messages.h"

namespace maidsafe {

namespace vault {

// ================================= MpidMessageBase =============================================

MpidMessageBase::MpidMessageBase()
    : sender(), receiver(), id(), parent_id(), signed_header() {}

MpidMessageBase::MpidMessageBase(const std::string& serialised_copy)
    : sender(), receiver(), id(), parent_id(), signed_header() {
  InputVectorStream binary_input_stream {
      SerialisedData(serialised_copy.begin(), serialised_copy.end()) };
  Parse(binary_input_stream, sender, receiver, id, parent_id, signed_header);
}

MpidMessageBase::MpidMessageBase(const passport::PublicMpid::Name& sender_in,
                                 const passport::PublicMpid::Name& receiver_in,
                                 int32_t id_in,
                                 int32_t parent_id_in, const MessageHeaderType& signed_header_in)
    : sender(sender_in), receiver(receiver_in), id(id_in), parent_id(parent_id_in),
      signed_header(signed_header_in) {}

MpidMessageBase::MpidMessageBase(const MpidMessageBase& other)
    : sender(other.sender), receiver(), id(other.id), parent_id(other.parent_id),
      signed_header(other.signed_header) {}

MpidMessageBase::MpidMessageBase(MpidMessageBase&& other)
    : sender(std::move(sender)), receiver(std::move(receiver)), id(std::move(other.id)),
      parent_id(std::move(other.parent_id)), signed_header(std::move(other.signed_header)) {}

MpidMessageBase& MpidMessageBase::operator=(MpidMessageBase other) {
  swap(*this, other);
  return *this;
}

bool operator==(const MpidMessageBase& lhs, const MpidMessageBase& rhs) {
  return (lhs.sender == rhs.sender) && (lhs.receiver == rhs.receiver) &&  (lhs.id == rhs.id) &&
         (lhs.parent_id == rhs.parent_id) && (lhs.signed_header == rhs.signed_header);
}

void swap(MpidMessageBase& lhs, MpidMessageBase& rhs) MAIDSAFE_NOEXCEPT {
  using std::swap;
  swap(lhs.sender, rhs.sender);
  swap(lhs.receiver, rhs.receiver);
  swap(lhs.id, rhs.id);
  swap(lhs.parent_id, rhs.parent_id);
  swap(lhs.signed_header, rhs.signed_header);
}

// ================================= MpidAlert ==================================================

MpidAlert::MpidAlert(const MpidMessageBase& base_in, const MessageIdType& message_id_in)
    : base(base_in), message_id(message_id_in) {}

MpidAlert::MpidAlert(const std::string& serialised_copy) : base(), message_id() {
  InputVectorStream binary_input_stream {
      SerialisedData(serialised_copy.begin(), serialised_copy.end()) };
  Parse(binary_input_stream, base, message_id);
}

MpidAlert::MpidAlert(const MpidAlert& other)
    : base(other.base), message_id(other.message_id){}

MpidAlert::MpidAlert(MpidAlert&& other)
    : base(std::move(other.base)), message_id(std::move(other.message_id)) {}

MpidAlert& MpidAlert::operator=(MpidAlert other) {
  swap(*this, other);
  return *this;
}

bool operator==(const MpidAlert& lhs, const MpidAlert& rhs) {
  return (lhs.base == rhs.base) && (lhs.message_id == rhs.message_id);
}

void swap(MpidAlert& lhs, MpidAlert& rhs) MAIDSAFE_NOEXCEPT {
  using std::swap;
  swap(lhs.base, rhs.base);
  swap(lhs.message_id, rhs.message_id);
}

// ================================= MpidMessage ==================================================

MpidMessage::MpidMessage(const MpidMessageBase& base_in, MessageBodyType& signed_body_in)
    : base(base_in), signed_body(signed_body_in) {}

MpidMessage::MpidMessage(const std::string& serialised_copy) : base(), signed_body(){
  InputVectorStream binary_input_stream {
      SerialisedData(serialised_copy.begin(), serialised_copy.end()) };
  Parse(binary_input_stream, base, signed_body);
}

MpidMessage::MpidMessage(const MpidMessage& other)
    : base(other.base), signed_body(other.signed_body){}

MpidMessage::MpidMessage(MpidMessage&& other)
    : base(std::move(other.base)), signed_body(std::move(other.signed_body)) {}

MpidMessage& MpidMessage::operator=(MpidMessage other) {
  swap(*this, other);
  return *this;
}

bool operator==(const MpidMessage& lhs, const MpidMessage& rhs) {
  return (lhs.base == rhs.base) && (lhs.signed_body == rhs.signed_body);
}

void swap(MpidMessage& lhs, MpidMessage& rhs) MAIDSAFE_NOEXCEPT {
  using std::swap;
  swap(lhs.base, rhs.base);
  swap(lhs.signed_body, rhs.signed_body);
}

}  // namespace vault

}  // namespace maidsafe
