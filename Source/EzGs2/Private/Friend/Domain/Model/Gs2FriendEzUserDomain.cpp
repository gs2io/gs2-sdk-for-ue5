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

#include "Friend/Domain/Model/Gs2FriendEzUserDomain.h"

namespace Gs2::UE5::Friend::Domain::Model
{

    TOptional<FString> FEzUserDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzUserDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzUserDomain::UserId() const
    {
        return Domain->UserId;
    }

    FEzUserDomain::FEzUserDomain(
        Gs2::Friend::Domain::Model::FUserDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Friend::Domain::Model::FEzProfileDomainPtr FEzUserDomain::Profile(
    ) const
    {
        return MakeShared<Gs2::UE5::Friend::Domain::Model::FEzProfileDomain>(
            Domain->Profile(
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Friend::Domain::Model::FEzPublicProfileDomainPtr FEzUserDomain::PublicProfile(
    ) const
    {
        return MakeShared<Gs2::UE5::Friend::Domain::Model::FEzPublicProfileDomain>(
            Domain->PublicProfile(
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Friend::Domain::Model::FEzBlackListDomainPtr FEzUserDomain::BlackList(
    ) const
    {
        return MakeShared<Gs2::UE5::Friend::Domain::Model::FEzBlackListDomain>(
            Domain->BlackList(
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Friend::Domain::Model::FEzFollowDomainPtr FEzUserDomain::Follow(
        const bool WithProfile
    ) const
    {
        return MakeShared<Gs2::UE5::Friend::Domain::Model::FEzFollowDomain>(
            Domain->Follow(
                WithProfile
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Friend::Domain::Model::FEzFriendDomainPtr FEzUserDomain::Friend(
        const bool WithProfile
    ) const
    {
        return MakeShared<Gs2::UE5::Friend::Domain::Model::FEzFriendDomain>(
            Domain->Friend(
                WithProfile
            ),
            ConnectionValue
        );
    }
}
