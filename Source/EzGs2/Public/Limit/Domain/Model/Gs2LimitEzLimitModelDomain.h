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
#include "Limit/Domain/Model/LimitModel.h"
#include "Limit/Model/Gs2LimitEzCounter.h"
#include "Limit/Model/Gs2LimitEzLimitModel.h"
#include "Gs2LimitEzLimitModelDomain.h"
#include "Limit/Domain/Iterator/Gs2LimitEzDescribeLimitModelsIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Limit::Domain::Model
{

    class EZGS2_API FEzLimitModelDomain final :
        public TSharedFromThis<FEzLimitModelDomain>
    {
        Gs2::Limit::Domain::Model::FLimitModelDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> LimitName() const;

        FEzLimitModelDomain(
            Gs2::Limit::Domain::Model::FLimitModelDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetLimitModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Limit::Model::FEzLimitModel>,
            public TSharedFromThis<FGetLimitModelTask>
        {
            TSharedPtr<FEzLimitModelDomain> Self;

        public:
            explicit FGetLimitModelTask(
                TSharedPtr<FEzLimitModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Limit::Model::FEzLimitModel>> Result
            ) override;
        };
        friend FGetLimitModelTask;

        TSharedPtr<FAsyncTask<FGetLimitModelTask>> GetLimitModel(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Limit::Model::FEzLimitModel>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzLimitModelDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzLimitModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Limit::Model::FEzLimitModelPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzLimitModelDomain> FEzLimitModelDomainPtr;
}
