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
#include "Exchange/Domain/Model/Await.h"
#include "Exchange/Model/Gs2ExchangeEzRateModel.h"
#include "Exchange/Model/Gs2ExchangeEzIncrementalRateModel.h"
#include "Exchange/Model/Gs2ExchangeEzAwait.h"
#include "Exchange/Model/Gs2ExchangeEzConfig.h"
#include "Exchange/Model/Gs2ExchangeEzAcquireAction.h"
#include "Exchange/Model/Gs2ExchangeEzConsumeAction.h"
#include "Gs2ExchangeEzAwaitDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Exchange::Domain::Model
{

    class EZGS2_API FEzAwaitDomain final :
        public TSharedFromThis<FEzAwaitDomain>
    {
        Gs2::Exchange::Domain::Model::FAwaitDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<int64> UnlockAt() const;
        TOptional<FString> TransactionId() const;
        TOptional<bool> AutoRunStampSheet() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> AwaitName() const;

        FEzAwaitDomain(
            Gs2::Exchange::Domain::Model::FAwaitDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Exchange::Model::FEzAwait>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzAwaitDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzAwaitDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Exchange::Model::FEzAwaitPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Exchange::Model::FEzAwaitPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzAwaitDomain> FEzAwaitDomainPtr;
}
