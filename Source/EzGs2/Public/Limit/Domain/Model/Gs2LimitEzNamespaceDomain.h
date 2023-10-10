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
#include "Limit/Domain/Model/Namespace.h"
#include "Limit/Model/Gs2LimitEzCounter.h"
#include "Limit/Model/Gs2LimitEzLimitModel.h"
#include "Gs2LimitEzLimitModelDomain.h"
#include "Limit/Domain/Iterator/Gs2LimitEzDescribeLimitModelsIterator.h"
#include "Gs2LimitEzUserDomain.h"
#include "Gs2LimitEzUserDomain.h"
#include "Gs2LimitEzUserGameSessionDomain.h"
#include "Gs2LimitEzNamespaceDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Limit::Domain::Model
{

    class EZGS2_API FEzNamespaceDomain final :
        public TSharedFromThis<FEzNamespaceDomain>
    {
        Gs2::Limit::Domain::Model::FNamespaceDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> Status() const;
        TOptional<FString> Url() const;
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;

        FEzNamespaceDomain(
            Gs2::Limit::Domain::Model::FNamespaceDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        Gs2::UE5::Limit::Domain::Iterator::FEzDescribeLimitModelsIteratorPtr LimitModels(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeLimitModels(TFunction<void()> Callback);

        void UnsubscribeLimitModels(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Limit::Domain::Model::FEzLimitModelDomainPtr LimitModel(
            const FString LimitName
        ) const;

        Gs2::UE5::Limit::Domain::Model::FEzUserDomainPtr User(
            const FString UserId
        ) const;

        Gs2::UE5::Limit::Domain::Model::FEzUserGameSessionDomainPtr Me(
            Gs2::UE5::Auth::Model::FEzAccessTokenPtr AccessToken
        ) const;

    };
    typedef TSharedPtr<FEzNamespaceDomain> FEzNamespaceDomainPtr;
}
