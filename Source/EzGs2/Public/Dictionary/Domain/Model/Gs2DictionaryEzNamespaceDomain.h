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
#include "Dictionary/Domain/Model/Namespace.h"
#include "Dictionary/Model/Gs2DictionaryEzEntryModel.h"
#include "Dictionary/Model/Gs2DictionaryEzEntry.h"
#include "Dictionary/Model/Gs2DictionaryEzConfig.h"
#include "Gs2DictionaryEzEntryModelDomain.h"
#include "Dictionary/Domain/Iterator/Gs2DictionaryEzDescribeEntryModelsIterator.h"
#include "Gs2DictionaryEzUserDomain.h"
#include "Gs2DictionaryEzUserDomain.h"
#include "Gs2DictionaryEzUserGameSessionDomain.h"
#include "Gs2DictionaryEzNamespaceDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Dictionary::Domain::Model
{

    class EZGS2_API FEzNamespaceDomain final :
        public TSharedFromThis<FEzNamespaceDomain>
    {
        Gs2::Dictionary::Domain::Model::FNamespaceDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> Status() const;
        TOptional<FString> Url() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;

        FEzNamespaceDomain(
            Gs2::Dictionary::Domain::Model::FNamespaceDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        Gs2::UE5::Dictionary::Domain::Iterator::FEzDescribeEntryModelsIteratorPtr EntryModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeEntryModels(TFunction<void()> Callback);

        void UnsubscribeEntryModels(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Dictionary::Domain::Model::FEzEntryModelDomainPtr EntryModel(
            const FString EntryName
        ) const;

        Gs2::UE5::Dictionary::Domain::Model::FEzUserDomainPtr User(
            const FString UserId
        ) const;

        Gs2::UE5::Dictionary::Domain::Model::FEzUserGameSessionDomainPtr Me(
            Gs2::UE5::Auth::Model::FEzAccessTokenPtr AccessToken
        ) const;

    };
    typedef TSharedPtr<FEzNamespaceDomain> FEzNamespaceDomainPtr;
}
