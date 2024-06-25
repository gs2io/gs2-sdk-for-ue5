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

#include "Money2/Domain/Model/Gs2Money2EzWalletGameSessionDomain.h"

namespace Gs2::UE5::Money2::Domain::Model
{

    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Money2::Model::FEzDepositTransaction>>> FEzWalletGameSessionDomain::WithdrawTransactions() const
    {
        return [&]{
            auto Result = MakeShared<TArray<TSharedPtr<Gs2::UE5::Money2::Model::FEzDepositTransaction>>>();
            for (auto Value : *Domain->WithdrawTransactions) {
                Result->Add(
                    Gs2::UE5::Money2::Model::FEzDepositTransaction::FromModel(
                        Value
                    )
                );
            }
            return Result;
        }();
    }

    TOptional<FString> FEzWalletGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzWalletGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<int32> FEzWalletGameSessionDomain::Slot() const
    {
        return Domain->Slot;
    }

    FEzWalletGameSessionDomain::FEzWalletGameSessionDomain(
        Gs2::Money2::Domain::Model::FWalletAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzWalletGameSessionDomain::FWithdrawTask::FWithdrawTask(
        TSharedPtr<FEzWalletGameSessionDomain> Self,
        int32 WithdrawCount,
        TOptional<bool> PaidOnly
    ): Self(Self), WithdrawCount(WithdrawCount), PaidOnly(PaidOnly)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzWalletGameSessionDomain::FWithdrawTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Money2::Domain::Model::FEzWalletGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Withdraw(
                    MakeShared<Gs2::Money2::Request::FWithdrawRequest>()
                        ->WithWithdrawCount(WithdrawCount)
                        ->WithPaidOnly(PaidOnly)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Money2::Domain::Model::FEzWalletGameSessionDomain>(
                    Task->GetTask().Result(),
                    Self->GameSession,
                    Self->ConnectionValue
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

    TSharedPtr<FAsyncTask<FEzWalletGameSessionDomain::FWithdrawTask>> FEzWalletGameSessionDomain::Withdraw(
        int32 WithdrawCount,
        TOptional<bool> PaidOnly
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FWithdrawTask>>(
            this->AsShared(),
            WithdrawCount,
            PaidOnly
        );
    }

    FEzWalletGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzWalletGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzWalletGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Money2::Model::FEzWalletPtr> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Model();
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Money2::Model::FEzWallet::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzWalletGameSessionDomain::FModelTask>> FEzWalletGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzWalletGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Money2::Model::FEzWalletPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Money2::Model::FWalletPtr Item)
            {
                Callback(Gs2::UE5::Money2::Model::FEzWallet::FromModel(Item));
            }
        );
    }

    void FEzWalletGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
