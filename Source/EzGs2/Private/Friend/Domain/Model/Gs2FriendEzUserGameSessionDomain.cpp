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

#include "Friend/Domain/Model/Gs2FriendEzUserGameSessionDomain.h"

namespace Gs2::UE5::Friend::Domain::Model
{

    TOptional<FString> FEzUserGameSessionDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzUserGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzUserGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzUserGameSessionDomain::FEzUserGameSessionDomain(
        Gs2::Friend::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzUserGameSessionDomain::FSendRequestTask::FSendRequestTask(
        TSharedPtr<FEzUserGameSessionDomain> Self,
        FString TargetUserId
    ): Self(Self), TargetUserId(TargetUserId)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzUserGameSessionDomain::FSendRequestTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Friend::Domain::Model::FEzSendFriendRequestGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FSendRequestTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->SendRequest(
                    MakeShared<Gs2::Friend::Request::FSendRequestRequest>()
                        ->WithTargetUserId(TargetUserId)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Friend::Domain::Model::FEzSendFriendRequestGameSessionDomain>(
                    Task->GetTask().Result(),
                    Self->ProfileValue
                );
                Task->EnsureCompletion();
                return nullptr;
            },
            nullptr
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            Future->EnsureCompletion();
            return Future->GetTask().Error();
        }
        Future->EnsureCompletion();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEzUserGameSessionDomain::FSendRequestTask>> FEzUserGameSessionDomain::SendRequest(
        FString TargetUserId
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSendRequestTask>>(
            this->AsShared(),
            TargetUserId
        );
    }

    Gs2::UE5::Friend::Domain::Model::FEzProfileGameSessionDomainPtr FEzUserGameSessionDomain::Profile(
    ) const
    {
        return MakeShared<Gs2::UE5::Friend::Domain::Model::FEzProfileGameSessionDomain>(
            Domain->Profile(
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Friend::Domain::Iterator::FEzDescribeBlackListIteratorPtr FEzUserGameSessionDomain::BlackLists(
    ) const
    {
        return MakeShared<Gs2::UE5::Friend::Domain::Iterator::FEzDescribeBlackListIterator>(
            Domain->BlackLists(
            )
        );
    }

    Gs2::UE5::Friend::Domain::Model::FEzBlackListGameSessionDomainPtr FEzUserGameSessionDomain::BlackList(
    ) const
    {
        return MakeShared<Gs2::UE5::Friend::Domain::Model::FEzBlackListGameSessionDomain>(
            Domain->BlackList(
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Friend::Domain::Iterator::FEzDescribeFollowsIteratorPtr FEzUserGameSessionDomain::Follows(
          const TOptional<bool> WithProfile
    ) const
    {
        return MakeShared<Gs2::UE5::Friend::Domain::Iterator::FEzDescribeFollowsIterator>(
            Domain->Follows(
                WithProfile
            )
        );
    }

    Gs2::UE5::Friend::Domain::Model::FEzFollowUserGameSessionDomainPtr FEzUserGameSessionDomain::FollowUser(
        const FString TargetUserId,
        const bool WithProfile
    ) const
    {
        return MakeShared<Gs2::UE5::Friend::Domain::Model::FEzFollowUserGameSessionDomain>(
            Domain->FollowUser(
                TargetUserId,
                WithProfile
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Friend::Domain::Iterator::FEzDescribeFriendsIteratorPtr FEzUserGameSessionDomain::Friends(
          const TOptional<bool> WithProfile
    ) const
    {
        return MakeShared<Gs2::UE5::Friend::Domain::Iterator::FEzDescribeFriendsIterator>(
            Domain->Friends(
                WithProfile
            )
        );
    }

    Gs2::UE5::Friend::Domain::Model::FEzFriendGameSessionDomainPtr FEzUserGameSessionDomain::Friend(
        const bool WithProfile
    ) const
    {
        return MakeShared<Gs2::UE5::Friend::Domain::Model::FEzFriendGameSessionDomain>(
            Domain->Friend(
                WithProfile
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Friend::Domain::Iterator::FEzDescribeSendRequestsIteratorPtr FEzUserGameSessionDomain::SendRequests(
    ) const
    {
        return MakeShared<Gs2::UE5::Friend::Domain::Iterator::FEzDescribeSendRequestsIterator>(
            Domain->SendRequests(
            )
        );
    }

    Gs2::UE5::Friend::Domain::Model::FEzSendFriendRequestGameSessionDomainPtr FEzUserGameSessionDomain::SendFriendRequest(
        const FString TargetUserId
    ) const
    {
        return MakeShared<Gs2::UE5::Friend::Domain::Model::FEzSendFriendRequestGameSessionDomain>(
            Domain->SendFriendRequest(
                TargetUserId
            ),
            ProfileValue
        );
    }

    Gs2::UE5::Friend::Domain::Iterator::FEzDescribeReceiveRequestsIteratorPtr FEzUserGameSessionDomain::ReceiveRequests(
    ) const
    {
        return MakeShared<Gs2::UE5::Friend::Domain::Iterator::FEzDescribeReceiveRequestsIterator>(
            Domain->ReceiveRequests(
            )
        );
    }

    Gs2::UE5::Friend::Domain::Model::FEzReceiveFriendRequestGameSessionDomainPtr FEzUserGameSessionDomain::ReceiveFriendRequest(
        const FString FromUserId
    ) const
    {
        return MakeShared<Gs2::UE5::Friend::Domain::Model::FEzReceiveFriendRequestGameSessionDomain>(
            Domain->ReceiveFriendRequest(
                FromUserId
            ),
            ProfileValue
        );
    }
}
