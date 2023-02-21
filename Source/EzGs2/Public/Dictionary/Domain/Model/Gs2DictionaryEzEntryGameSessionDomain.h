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
#include "Dictionary/Domain/Model/EntryAccessToken.h"
#include "Dictionary/Model/Gs2DictionaryEzEntryModel.h"
#include "Dictionary/Model/Gs2DictionaryEzEntry.h"
#include "Dictionary/Model/Gs2DictionaryEzConfig.h"
#include "Gs2DictionaryEzEntryGameSessionDomain.h"
#include "Dictionary/Domain/Iterator/Gs2DictionaryEzDescribeEntriesIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Dictionary::Domain::Model
{

    class EZGS2_API FEzEntryGameSessionDomain final :
        public TSharedFromThis<FEzEntryGameSessionDomain>
    {
        Gs2::Dictionary::Domain::Model::FEntryAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> Body() const;
        TOptional<FString> Signature() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> EntryModelName() const;

        FEzEntryGameSessionDomain(
            Gs2::Dictionary::Domain::Model::FEntryAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetEntryTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Dictionary::Model::FEzEntry>,
            public TSharedFromThis<FGetEntryTask>
        {
            TSharedPtr<FEzEntryGameSessionDomain> Self;

        public:
            explicit FGetEntryTask(
                TSharedPtr<FEzEntryGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Dictionary::Model::FEzEntry>> Result
            ) override;
        };
        friend FGetEntryTask;

        TSharedPtr<FAsyncTask<FGetEntryTask>> GetEntry(
        );

        class FGetEntryWithSignatureTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Dictionary::Domain::Model::FEzEntryGameSessionDomain>,
            public TSharedFromThis<FGetEntryWithSignatureTask>
        {
            TSharedPtr<FEzEntryGameSessionDomain> Self;
            FString KeyId;

        public:
            explicit FGetEntryWithSignatureTask(
                TSharedPtr<FEzEntryGameSessionDomain> Self,
                FString KeyId
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Dictionary::Domain::Model::FEzEntryGameSessionDomain>> Result
            ) override;
        };
        friend FGetEntryWithSignatureTask;

        TSharedPtr<FAsyncTask<FGetEntryWithSignatureTask>> GetEntryWithSignature(
            FString KeyId
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Dictionary::Model::FEzEntry>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzEntryGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzEntryGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Dictionary::Model::FEzEntryPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzEntryGameSessionDomain> FEzEntryGameSessionDomainPtr;
}
