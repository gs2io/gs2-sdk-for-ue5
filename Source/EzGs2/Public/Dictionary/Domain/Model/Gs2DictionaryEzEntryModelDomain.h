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
#include "Dictionary/Domain/Model/EntryModel.h"
#include "Dictionary/Model/Gs2DictionaryEzEntryModel.h"
#include "Dictionary/Model/Gs2DictionaryEzEntry.h"
#include "Dictionary/Model/Gs2DictionaryEzConfig.h"
#include "Gs2DictionaryEzEntryModelDomain.h"
#include "Dictionary/Domain/Iterator/Gs2DictionaryEzDescribeEntryModelsIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Dictionary::Domain::Model
{

    class EZGS2_API FEzEntryModelDomain final :
        public TSharedFromThis<FEzEntryModelDomain>
    {
        Gs2::Dictionary::Domain::Model::FEntryModelDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> EntryName() const;

        FEzEntryModelDomain(
            Gs2::Dictionary::Domain::Model::FEntryModelDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetEntryModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Dictionary::Model::FEzEntryModel>,
            public TSharedFromThis<FGetEntryModelTask>
        {
            TSharedPtr<FEzEntryModelDomain> Self;

        public:
            explicit FGetEntryModelTask(
                TSharedPtr<FEzEntryModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Dictionary::Model::FEzEntryModel>> Result
            ) override;
        };
        friend FGetEntryModelTask;

        TSharedPtr<FAsyncTask<FGetEntryModelTask>> GetEntryModel(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Dictionary::Model::FEzEntryModel>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzEntryModelDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzEntryModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Dictionary::Model::FEzEntryModelPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzEntryModelDomain> FEzEntryModelDomainPtr;
}
