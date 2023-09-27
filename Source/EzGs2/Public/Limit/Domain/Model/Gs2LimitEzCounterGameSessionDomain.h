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
#include "Limit/Domain/Model/CounterAccessToken.h"
#include "Limit/Model/Gs2LimitEzCounter.h"
#include "Limit/Model/Gs2LimitEzLimitModel.h"
#include "Gs2LimitEzCounterGameSessionDomain.h"
#include "Limit/Domain/Iterator/Gs2LimitEzDescribeCountersIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Limit::Domain::Model
{

    class EZGS2_API FEzCounterGameSessionDomain final :
        public TSharedFromThis<FEzCounterGameSessionDomain>
    {
        Gs2::Limit::Domain::Model::FCounterAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> LimitName() const;
        TOptional<FString> CounterName() const;

        FEzCounterGameSessionDomain(
            Gs2::Limit::Domain::Model::FCounterAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetCounterTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Limit::Model::FEzCounter>,
            public TSharedFromThis<FGetCounterTask>
        {
            TSharedPtr<FEzCounterGameSessionDomain> Self;

        public:
            explicit FGetCounterTask(
                TSharedPtr<FEzCounterGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Limit::Model::FEzCounter>> Result
            ) override;
        };
        friend FGetCounterTask;

        TSharedPtr<FAsyncTask<FGetCounterTask>> GetCounter(
        );

        class FCountUpTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Limit::Domain::Model::FEzCounterGameSessionDomain>,
            public TSharedFromThis<FCountUpTask>
        {
            TSharedPtr<FEzCounterGameSessionDomain> Self;
            TOptional<int32> CountUpValue;
            TOptional<int32> MaxValue;

        public:
            explicit FCountUpTask(
                TSharedPtr<FEzCounterGameSessionDomain> Self,
                TOptional<int32> CountUpValue = TOptional<int32>(),
                TOptional<int32> MaxValue = TOptional<int32>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Limit::Domain::Model::FEzCounterGameSessionDomain>> Result
            ) override;
        };
        friend FCountUpTask;

        TSharedPtr<FAsyncTask<FCountUpTask>> CountUp(
            TOptional<int32> CountUpValue = TOptional<int32>(),
            TOptional<int32> MaxValue = TOptional<int32>()
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Limit::Model::FEzCounter>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzCounterGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzCounterGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Limit::Model::FEzCounterPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Limit::Model::FEzCounterPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzCounterGameSessionDomain> FEzCounterGameSessionDomainPtr;
}
