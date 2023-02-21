/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include "Friend/Domain/Model/Gs2FriendEzSendFriendRequestDomain.h"

namespace Gs2::UE5::Friend::Domain::Model
{

    TOptional<FString> FEzSendFriendRequestDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzSendFriendRequestDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzSendFriendRequestDomain::TargetUserId() const
    {
        return Domain->TargetUserId;
    }

    FEzSendFriendRequestDomain::FEzSendFriendRequestDomain(
        Gs2::Friend::Domain::Model::FSendFriendRequestDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }
}
