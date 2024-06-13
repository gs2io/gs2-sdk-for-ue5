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
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Idle::Domain::Model
{

    class EZGS2_API FEzCategoryModelDomain final :
        public TSharedFromThis<FEzCategoryModelDomain>
    {
        Gs2::Idle::Domain::Model::FCategoryModelDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> CategoryName() const;

        FEzCategoryModelDomain(
            Gs2::Idle::Domain::Model::FCategoryModelDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FModelTask :
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

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Idle::Model::FEzCategoryModelPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzCategoryModelDomain> FEzCategoryModelDomainPtr;
}
