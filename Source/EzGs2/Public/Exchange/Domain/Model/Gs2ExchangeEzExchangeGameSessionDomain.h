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
#include "Exchange/Domain/Model/ExchangeAccessToken.h"
#include "Exchange/Model/Gs2ExchangeEzRateModel.h"
#include "Exchange/Model/Gs2ExchangeEzIncrementalRateModel.h"
#include "Exchange/Model/Gs2ExchangeEzAwait.h"
#include "Exchange/Model/Gs2ExchangeEzConfig.h"
#include "Exchange/Model/Gs2ExchangeEzAcquireAction.h"
#include "Exchange/Model/Gs2ExchangeEzConsumeAction.h"
#include "Exchange/Model/Gs2ExchangeEzVerifyAction.h"
#include "Gs2ExchangeEzExchangeGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Exchange::Domain::Model
{

    class EZGS2_API FEzExchangeGameSessionDomain final :
        public TSharedFromThis<FEzExchangeGameSessionDomain>
    {
        Gs2::Exchange::Domain::Model::FExchangeAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> TransactionId() const;
        TOptional<bool> AutoRunStampSheet() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzExchangeGameSessionDomain(
            Gs2::Exchange::Domain::Model::FExchangeAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FExchangeTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Exchange::Domain::Model::FEzExchangeGameSessionDomain>,
            public TSharedFromThis<FExchangeTask>
        {
            TSharedPtr<FEzExchangeGameSessionDomain> Self;
            FString RateName;
            int32 Count;
            TOptional<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzConfig>>> Config;

        public:
            explicit FExchangeTask(
                TSharedPtr<FEzExchangeGameSessionDomain> Self,
                FString RateName,
                int32 Count,
                TOptional<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzConfig>>> Config = TOptional<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzConfig>>>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Exchange::Domain::Model::FEzExchangeGameSessionDomain>> Result
            ) override;
        };
        friend FExchangeTask;

        TSharedPtr<FAsyncTask<FExchangeTask>> Exchange(
            FString RateName,
            int32 Count,
            TOptional<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzConfig>>> Config = TOptional<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzConfig>>>()
        );

        class EZGS2_API FIncrementalExchangeTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Exchange::Domain::Model::FEzExchangeGameSessionDomain>,
            public TSharedFromThis<FIncrementalExchangeTask>
        {
            TSharedPtr<FEzExchangeGameSessionDomain> Self;
            FString RateName;
            int32 Count;
            TOptional<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzConfig>>> Config;

        public:
            explicit FIncrementalExchangeTask(
                TSharedPtr<FEzExchangeGameSessionDomain> Self,
                FString RateName,
                int32 Count,
                TOptional<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzConfig>>> Config = TOptional<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzConfig>>>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Exchange::Domain::Model::FEzExchangeGameSessionDomain>> Result
            ) override;
        };
        friend FIncrementalExchangeTask;

        TSharedPtr<FAsyncTask<FIncrementalExchangeTask>> IncrementalExchange(
            FString RateName,
            int32 Count,
            TOptional<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzConfig>>> Config = TOptional<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzConfig>>>()
        );

    };
    typedef TSharedPtr<FEzExchangeGameSessionDomain> FEzExchangeGameSessionDomainPtr;
}
