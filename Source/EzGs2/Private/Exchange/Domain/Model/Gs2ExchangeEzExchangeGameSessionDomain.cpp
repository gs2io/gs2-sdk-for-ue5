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

#include "Exchange/Domain/Model/Gs2ExchangeEzExchangeGameSessionDomain.h"

namespace Gs2::UE5::Exchange::Domain::Model
{

    TOptional<FString> FEzExchangeGameSessionDomain::TransactionId() const
    {
        return Domain->TransactionId;
    }

    TOptional<bool> FEzExchangeGameSessionDomain::AutoRunStampSheet() const
    {
        return Domain->AutoRunStampSheet;
    }

    TOptional<FString> FEzExchangeGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzExchangeGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzExchangeGameSessionDomain::FEzExchangeGameSessionDomain(
        Gs2::Exchange::Domain::Model::FExchangeAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzExchangeGameSessionDomain::FExchangeTask::FExchangeTask(
        TSharedPtr<FEzExchangeGameSessionDomain> Self,
        FString RateName,
        int32 Count,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzConfig>>> Config
    ): Self(Self), RateName(RateName), Count(Count), Config(Config)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzExchangeGameSessionDomain::FExchangeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Exchange::Domain::Model::FEzExchangeGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FExchangeTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Exchange(
                    MakeShared<Gs2::Exchange::Request::FExchangeRequest>()
                        ->WithRateName(RateName)
                        ->WithCount(Count)
                        ->WithConfig([&]{
                            auto Arr = MakeShared<TArray<TSharedPtr<Gs2::Exchange::Model::FConfig>>>();
                            if (!Config.IsSet()) {
                                return Arr;
                            }
                            for (auto Value : *Config) {
                                Arr->Add(Value->ToModel());
                            }
                            return Arr;
                        }())
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Exchange::Domain::Model::FEzExchangeGameSessionDomain>(
                    Task->GetTask().Result(),
                    Self->ProfileValue
                );
                Task->EnsureCompletion();
                return nullptr;
            },
            nullptr
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            Future->EnsureCompletion();
            return Future->GetTask().Error();
        }
        Future->EnsureCompletion();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEzExchangeGameSessionDomain::FExchangeTask>> FEzExchangeGameSessionDomain::Exchange(
        FString RateName,
        int32 Count,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzConfig>>> Config
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FExchangeTask>>(
            this->AsShared(),
            RateName,
            Count,
            Config
        );
    }

    FEzExchangeGameSessionDomain::FIncrementalExchangeTask::FIncrementalExchangeTask(
        TSharedPtr<FEzExchangeGameSessionDomain> Self,
        FString RateName,
        int32 Count,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzConfig>>> Config
    ): Self(Self), RateName(RateName), Count(Count), Config(Config)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzExchangeGameSessionDomain::FIncrementalExchangeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Exchange::Domain::Model::FEzExchangeGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FIncrementalExchangeTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Incremental(
                    MakeShared<Gs2::Exchange::Request::FIncrementalExchangeRequest>()
                        ->WithRateName(RateName)
                        ->WithCount(Count)
                        ->WithConfig([&]{
                            auto Arr = MakeShared<TArray<TSharedPtr<Gs2::Exchange::Model::FConfig>>>();
                            if (!Config.IsSet()) {
                                return Arr;
                            }
                            for (auto Value : *Config) {
                                Arr->Add(Value->ToModel());
                            }
                            return Arr;
                        }())
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Exchange::Domain::Model::FEzExchangeGameSessionDomain>(
                    Task->GetTask().Result(),
                    Self->ProfileValue
                );
                Task->EnsureCompletion();
                return nullptr;
            },
            nullptr
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            Future->EnsureCompletion();
            return Future->GetTask().Error();
        }
        Future->EnsureCompletion();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEzExchangeGameSessionDomain::FIncrementalExchangeTask>> FEzExchangeGameSessionDomain::IncrementalExchange(
        FString RateName,
        int32 Count,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Exchange::Model::FEzConfig>>> Config
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FIncrementalExchangeTask>>(
            this->AsShared(),
            RateName,
            Count,
            Config
        );
    }
}
