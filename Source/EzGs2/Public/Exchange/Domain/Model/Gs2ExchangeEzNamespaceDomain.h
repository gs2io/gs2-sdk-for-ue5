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
#include "Exchange/Domain/Model/Namespace.h"
#include "Exchange/Model/Gs2ExchangeEzRateModel.h"
#include "Exchange/Model/Gs2ExchangeEzIncrementalRateModel.h"
#include "Exchange/Model/Gs2ExchangeEzAwait.h"
#include "Exchange/Model/Gs2ExchangeEzConfig.h"
#include "Exchange/Model/Gs2ExchangeEzAcquireAction.h"
#include "Exchange/Model/Gs2ExchangeEzConsumeAction.h"
#include "Gs2ExchangeEzRateModelDomain.h"
#include "Exchange/Domain/Iterator/Gs2ExchangeEzDescribeRateModelsIterator.h"
#include "Gs2ExchangeEzUserDomain.h"
#include "Gs2ExchangeEzUserDomain.h"
#include "Gs2ExchangeEzUserGameSessionDomain.h"
#include "Gs2ExchangeEzIncrementalRateModelDomain.h"
#include "Exchange/Domain/Iterator/Gs2ExchangeEzDescribeIncrementalRateModelsIterator.h"
#include "Gs2ExchangeEzNamespaceDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Exchange::Domain::Model
{

    class EZGS2_API FEzNamespaceDomain final :
        public TSharedFromThis<FEzNamespaceDomain>
    {
        Gs2::Exchange::Domain::Model::FNamespaceDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> Status() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;

        FEzNamespaceDomain(
            Gs2::Exchange::Domain::Model::FNamespaceDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        Gs2::UE5::Exchange::Domain::Iterator::FEzDescribeRateModelsIteratorPtr RateModels(
        ) const;

        Gs2::UE5::Exchange::Domain::Model::FEzRateModelDomainPtr RateModel(
            const FString RateName
        ) const;

        Gs2::UE5::Exchange::Domain::Model::FEzUserGameSessionDomainPtr Me(
            Gs2::UE5::Auth::Model::FEzAccessTokenPtr AccessToken
        ) const;

        Gs2::UE5::Exchange::Domain::Iterator::FEzDescribeIncrementalRateModelsIteratorPtr IncrementalRateModels(
        ) const;

        Gs2::UE5::Exchange::Domain::Model::FEzIncrementalRateModelDomainPtr IncrementalRateModel(
            const FString RateName
        ) const;

    };
    typedef TSharedPtr<FEzNamespaceDomain> FEzNamespaceDomainPtr;
}
