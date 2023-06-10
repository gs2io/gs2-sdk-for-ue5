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
#include "Idle/Domain/Model/CategoryModel.h"
#include "Idle/Model/Gs2IdleEzCategoryModel.h"
#include "Idle/Model/Gs2IdleEzStatus.h"
#include "Idle/Model/Gs2IdleEzConfig.h"
#include "Idle/Model/Gs2IdleEzAcquireAction.h"
#include "Idle/Model/Gs2IdleEzAcquireActionList.h"
#include "Gs2IdleEzCategoryModelDomain.h"
#include "Idle/Domain/Iterator/Gs2IdleEzDescribeCategoryModelsIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Idle::Domain::Model
{

    class EZGS2_API FEzCategoryModelDomain final :
        public TSharedFromThis<FEzCategoryModelDomain>
    {
        Gs2::Idle::Domain::Model::FCategoryModelDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> CategoryName() const;

        FEzCategoryModelDomain(
            Gs2::Idle::Domain::Model::FCategoryModelDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetCategoryModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Idle::Model::FEzCategoryModel>,
            public TSharedFromThis<FGetCategoryModelTask>
        {
            TSharedPtr<FEzCategoryModelDomain> Self;

        public:
            explicit FGetCategoryModelTask(
                TSharedPtr<FEzCategoryModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Idle::Model::FEzCategoryModel>> Result
            ) override;
        };
        friend FGetCategoryModelTask;

        TSharedPtr<FAsyncTask<FGetCategoryModelTask>> GetCategoryModel(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Idle::Model::FEzCategoryModel>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzCategoryModelDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzCategoryModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Idle::Model::FEzCategoryModelPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzCategoryModelDomain> FEzCategoryModelDomainPtr;
}
