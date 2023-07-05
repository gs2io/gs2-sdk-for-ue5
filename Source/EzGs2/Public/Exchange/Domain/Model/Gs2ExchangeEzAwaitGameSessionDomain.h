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
#include "Exchange/Domain/Model/AwaitAccessToken.h"
#include "Exchange/Model/Gs2ExchangeEzRateModel.h"
#include "Exchange/Model/Gs2ExchangeEzIncrementalRateModel.h"
#include "Exchange/Model/Gs2ExchangeEzAwait.h"
#include "Exchange/Model/Gs2ExchangeEzConfig.h"
#include "Exchange/Model/Gs2ExchangeEzAcquireAction.h"
#include "Exchange/Model/Gs2ExchangeEzConsumeAction.h"
#include "Gs2ExchangeEzAwaitGameSessionDomain.h"
#include "Exchange/Domain/Iterator/Gs2ExchangeEzDescribeAwaitsIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Exchange::Domain::Model
{

    class EZGS2_API FEzAwaitGameSessionDomain final :
        public TSharedFromThis<FEzAwaitGameSessionDomain>
    {
        Gs2::Exchange::Domain::Model::FAwaitAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<int64> UnlockAt() const;
        TOptional<FString> TransactionId() const;
        TOptional<bool> AutoRunStampSheet() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> AwaitName() const;

        FEzAwaitGameSessionDomain(
            Gs2::Exchange::Domain::Model::FAwaitAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FGetAwaitTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Exchange::Model::FEzAwait>,
            public TSharedFromThis<FGetAwaitTask>
        {
            TSharedPtr<FEzAwaitGameSessionDomain> Self;

        public:
            explicit FGetAwaitTask(
                TSharedPtr<FEzAwaitGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Exchange::Model::FEzAwait>> Result
            ) override;
        };
        friend FGetAwaitTask;

        TSharedPtr<FAsyncTask<FGetAwaitTask>> GetAwait(
        );

        class FAcquireTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Exchange::Domain::Model::FEzAwaitGameSessionDomain>,
            public TSharedFromThis<FAcquireTask>
        {
            TSharedPtr<FEzAwaitGameSessionDomain> Self;

        public:
            explicit FAcquireTask(
                TSharedPtr<FEzAwaitGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Exchange::Domain::Model::FEzAwaitGameSessionDomain>> Result
            ) override;
        };
        friend FAcquireTask;

        TSharedPtr<FAsyncTask<FAcquireTask>> Acquire(
        );

        class FSkipTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Exchange::Domain::Model::FEzAwaitGameSessionDomain>,
            public TSharedFromThis<FSkipTask>
        {
            TSharedPtr<FEzAwaitGameSessionDomain> Self;

        public:
            explicit FSkipTask(
                TSharedPtr<FEzAwaitGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Exchange::Domain::Model::FEzAwaitGameSessionDomain>> Result
            ) override;
        };
        friend FSkipTask;

        TSharedPtr<FAsyncTask<FSkipTask>> Skip(
        );

        class FDeleteAwaitTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Exchange::Domain::Model::FEzAwaitGameSessionDomain>,
            public TSharedFromThis<FDeleteAwaitTask>
        {
            TSharedPtr<FEzAwaitGameSessionDomain> Self;

        public:
            explicit FDeleteAwaitTask(
                TSharedPtr<FEzAwaitGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Exchange::Domain::Model::FEzAwaitGameSessionDomain>> Result
            ) override;
        };
        friend FDeleteAwaitTask;

        TSharedPtr<FAsyncTask<FDeleteAwaitTask>> DeleteAwait(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Exchange::Model::FEzAwait>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzAwaitGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzAwaitGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Exchange::Model::FEzAwaitPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };
    typedef TSharedPtr<FEzAwaitGameSessionDomain> FEzAwaitGameSessionDomainPtr;
}
