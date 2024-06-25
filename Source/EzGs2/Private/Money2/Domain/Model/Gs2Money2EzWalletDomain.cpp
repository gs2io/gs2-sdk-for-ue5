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

#include "Money2/Domain/Model/Gs2Money2EzWalletDomain.h"

namespace Gs2::UE5::Money2::Domain::Model
{

    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Money2::Model::FEzDepositTransaction>>> FEzWalletDomain::WithdrawTransactions() const
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

    TOptional<FString> FEzWalletDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzWalletDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<int32> FEzWalletDomain::Slot() const
    {
        return Domain->Slot;
    }

    FEzWalletDomain::FEzWalletDomain(
        Gs2::Money2::Domain::Model::FWalletDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    FEzWalletDomain::FModelTask::FModelTask(
        TSharedPtr<FEzWalletDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzWalletDomain::FModelTask::Action(
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

    TSharedPtr<FAsyncTask<FEzWalletDomain::FModelTask>> FEzWalletDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzWalletDomain::Subscribe(TFunction<void(Gs2::UE5::Money2::Model::FEzWalletPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Money2::Model::FWalletPtr Item)
            {
                Callback(Gs2::UE5::Money2::Model::FEzWallet::FromModel(Item));
            }
        );
    }

    void FEzWalletDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
