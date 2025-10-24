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

#include "Money2/Domain/Model/Gs2Money2EzUserGameSessionDomain.h"

namespace Gs2::UE5::Money2::Domain::Model
{

    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Money2::Model::FEzDepositTransaction>>> FEzUserGameSessionDomain::WithdrawTransactions() const
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

    TOptional<FString> FEzUserGameSessionDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzUserGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzUserGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzUserGameSessionDomain::FEzUserGameSessionDomain(
        Gs2::Money2::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzUserGameSessionDomain::FAllocateSubscriptionStatusTask::FAllocateSubscriptionStatusTask(
        TSharedPtr<FEzUserGameSessionDomain> Self,
        FString Receipt
    ): Self(Self), Receipt(Receipt)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzUserGameSessionDomain::FAllocateSubscriptionStatusTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Money2::Domain::Model::FEzSubscriptionStatusGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->AllocateSubscriptionStatus(
                    MakeShared<Gs2::Money2::Request::FAllocateSubscriptionStatusRequest>()
                        ->WithReceipt(Receipt)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Money2::Domain::Model::FEzSubscriptionStatusGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzUserGameSessionDomain::FAllocateSubscriptionStatusTask>> FEzUserGameSessionDomain::AllocateSubscriptionStatus(
        FString Receipt
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FAllocateSubscriptionStatusTask>>(
            this->AsShared(),
            Receipt
        );
    }

    FEzUserGameSessionDomain::FTakeOverSubscriptionStatusTask::FTakeOverSubscriptionStatusTask(
        TSharedPtr<FEzUserGameSessionDomain> Self,
        FString Receipt
    ): Self(Self), Receipt(Receipt)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzUserGameSessionDomain::FTakeOverSubscriptionStatusTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Money2::Domain::Model::FEzSubscriptionStatusGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->TakeoverSubscriptionStatus(
                    MakeShared<Gs2::Money2::Request::FTakeoverSubscriptionStatusRequest>()
                        ->WithReceipt(Receipt)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Money2::Domain::Model::FEzSubscriptionStatusGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzUserGameSessionDomain::FTakeOverSubscriptionStatusTask>> FEzUserGameSessionDomain::TakeOverSubscriptionStatus(
        FString Receipt
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FTakeOverSubscriptionStatusTask>>(
            this->AsShared(),
            Receipt
        );
    }

    Gs2::UE5::Money2::Domain::Iterator::FEzDescribeWalletsIteratorPtr FEzUserGameSessionDomain::Wallets(
    ) const
    {
        return MakeShared<Gs2::UE5::Money2::Domain::Iterator::FEzDescribeWalletsIterator>(
            Domain,
            GameSession,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzUserGameSessionDomain::SubscribeWallets(TFunction<void()> Callback)
    {
        return Domain->SubscribeWallets(
            Callback
        );
    }

    void FEzUserGameSessionDomain::UnsubscribeWallets(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeWallets(
            CallbackId
        );
    }

    Gs2::UE5::Money2::Domain::Iterator::FEzDescribeSubscriptionStatusesIteratorPtr FEzUserGameSessionDomain::SubscriptionStatuses(
    ) const
    {
        return MakeShared<Gs2::UE5::Money2::Domain::Iterator::FEzDescribeSubscriptionStatusesIterator>(
            Domain,
            GameSession,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzUserGameSessionDomain::SubscribeSubscriptionStatuses(TFunction<void()> Callback)
    {
        return Domain->SubscribeSubscriptionStatuses(
            Callback
        );
    }

    void FEzUserGameSessionDomain::UnsubscribeSubscriptionStatuses(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeSubscriptionStatuses(
            CallbackId
        );
    }

    Gs2::UE5::Money2::Domain::Model::FEzWalletGameSessionDomainPtr FEzUserGameSessionDomain::Wallet(
        const int32 Slot
    ) const
    {
        return MakeShared<Gs2::UE5::Money2::Domain::Model::FEzWalletGameSessionDomain>(
            Domain->Wallet(
                Slot
            ),
            GameSession,
            ConnectionValue
        );
    }

    Gs2::UE5::Money2::Domain::Model::FEzSubscriptionStatusGameSessionDomainPtr FEzUserGameSessionDomain::SubscriptionStatus(
        const FString ContentName
    ) const
    {
        return MakeShared<Gs2::UE5::Money2::Domain::Model::FEzSubscriptionStatusGameSessionDomain>(
            Domain->SubscriptionStatus(
                ContentName
            ),
            GameSession,
            ConnectionValue
        );
    }
}
