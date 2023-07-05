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
#include "Exchange/Domain/Model/IncrementalRateModel.h"
#include "Exchange/Model/Gs2ExchangeEzRateModel.h"
#include "Exchange/Model/Gs2ExchangeEzIncrementalRateModel.h"
#include "Exchange/Model/Gs2ExchangeEzAwait.h"
#include "Exchange/Model/Gs2ExchangeEzConfig.h"
#include "Exchange/Model/Gs2ExchangeEzAcquireAction.h"
#include "Exchange/Model/Gs2ExchangeEzConsumeAction.h"
#include "Gs2ExchangeEzIncrementalRateModelDomain.h"
#include "Exchange/Domain/Iterator/Gs2ExchangeEzDescribeIncrementalRateModelsIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Exchange::Domain::Model
{

    class EZGS2_API FEzIncrementalRateModelDomain final :
        public TSharedFromThis<FEzIncrementalRateModelDomain>
    {
        Gs2::Exchange::Domain::Model::FIncrementalRateModelDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> RateName() const;

        FEzIncrementalRateModelDomain(
            Gs2::Exchange::Domain::Model::FIncrementalRateModelDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetIncrementalRateModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Exchange::Model::FEzIncrementalRateModel>,
            public TSharedFromThis<FGetIncrementalRateModelTask>
        {
            TSharedPtr<FEzIncrementalRateModelDomain> Self;

        public:
            explicit FGetIncrementalRateModelTask(
                TSharedPtr<FEzIncrementalRateModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Exchange::Model::FEzIncrementalRateModel>> Result
            ) override;
        };
        friend FGetIncrementalRateModelTask;

        TSharedPtr<FAsyncTask<FGetIncrementalRateModelTask>> GetIncrementalRateModel(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Exchange::Model::FEzIncrementalRateModel>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzIncrementalRateModelDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzIncrementalRateModelDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Exchange::Model::FEzIncrementalRateModelPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzIncrementalRateModelDomain> FEzIncrementalRateModelDomainPtr;
}
