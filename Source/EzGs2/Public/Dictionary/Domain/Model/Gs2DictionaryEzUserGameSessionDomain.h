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

#pragma once

#include "CoreMinimal.h"
#include "Dictionary/Domain/Model/UserAccessToken.h"
#include "Dictionary/Model/Gs2DictionaryEzEntryModel.h"
#include "Dictionary/Model/Gs2DictionaryEzEntry.h"
#include "Dictionary/Model/Gs2DictionaryEzLike.h"
#include "Dictionary/Model/Gs2DictionaryEzConfig.h"
#include "Gs2DictionaryEzEntryGameSessionDomain.h"
#include "Dictionary/Domain/Iterator/Gs2DictionaryEzDescribeEntriesIterator.h"
#include "Gs2DictionaryEzLikeGameSessionDomain.h"
#include "Dictionary/Domain/Iterator/Gs2DictionaryEzDescribeLikesIterator.h"
#include "Gs2DictionaryEzUserGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Dictionary::Domain::Model
{

    class EZGS2_API FEzUserGameSessionDomain final :
        public TSharedFromThis<FEzUserGameSessionDomain>
    {
        Gs2::Dictionary::Domain::Model::FUserAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserGameSessionDomain(
            Gs2::Dictionary::Domain::Model::FUserAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Dictionary::Domain::Iterator::FEzDescribeEntriesIteratorPtr Entries(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeEntries(TFunction<void()> Callback);

        void UnsubscribeEntries(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Dictionary::Domain::Model::FEzEntryGameSessionDomainPtr Entry(
            const FString EntryModelName
        ) const;

        Gs2::UE5::Dictionary::Domain::Iterator::FEzDescribeLikesIteratorPtr Likes(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeLikes(TFunction<void()> Callback);

        void UnsubscribeLikes(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Dictionary::Domain::Model::FEzLikeGameSessionDomainPtr Like(
            const FString EntryModelName
        ) const;

    };
    typedef TSharedPtr<FEzUserGameSessionDomain> FEzUserGameSessionDomainPtr;
}
