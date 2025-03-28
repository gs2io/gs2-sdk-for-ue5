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

#include "Dictionary/Domain/Model/Gs2DictionaryEzUserGameSessionDomain.h"

namespace Gs2::UE5::Dictionary::Domain::Model
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
        Gs2::Dictionary::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Dictionary::Domain::Iterator::FEzDescribeEntriesIteratorPtr FEzUserGameSessionDomain::Entries(
    ) const
    {
        return MakeShared<Gs2::UE5::Dictionary::Domain::Iterator::FEzDescribeEntriesIterator>(
            Domain,
            GameSession,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzUserGameSessionDomain::SubscribeEntries(TFunction<void()> Callback)
    {
        return Domain->SubscribeEntries(
            Callback
        );
    }

    void FEzUserGameSessionDomain::UnsubscribeEntries(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeEntries(
            CallbackId
        );
    }

    Gs2::UE5::Dictionary::Domain::Model::FEzEntryGameSessionDomainPtr FEzUserGameSessionDomain::Entry(
        const FString EntryModelName
    ) const
    {
        return MakeShared<Gs2::UE5::Dictionary::Domain::Model::FEzEntryGameSessionDomain>(
            Domain->Entry(
                EntryModelName
            ),
            GameSession,
            ConnectionValue
        );
    }

    Gs2::UE5::Dictionary::Domain::Iterator::FEzDescribeLikesIteratorPtr FEzUserGameSessionDomain::Likes(
    ) const
    {
        return MakeShared<Gs2::UE5::Dictionary::Domain::Iterator::FEzDescribeLikesIterator>(
            Domain,
            GameSession,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzUserGameSessionDomain::SubscribeLikes(TFunction<void()> Callback)
    {
        return Domain->SubscribeLikes(
            Callback
        );
    }

    void FEzUserGameSessionDomain::UnsubscribeLikes(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeLikes(
            CallbackId
        );
    }

    Gs2::UE5::Dictionary::Domain::Model::FEzLikeGameSessionDomainPtr FEzUserGameSessionDomain::Like(
        const FString EntryModelName
    ) const
    {
        return MakeShared<Gs2::UE5::Dictionary::Domain::Model::FEzLikeGameSessionDomain>(
            Domain->Like(
                EntryModelName
            ),
            GameSession,
            ConnectionValue
        );
    }
}
