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

#include "Inventory/Domain/Model/Gs2InventoryEzInventoryGameSessionDomain.h"

namespace Gs2::UE5::Inventory::Domain::Model
{

    TOptional<int64> FEzInventoryGameSessionDomain::OverflowCount() const
    {
        return Domain->OverflowCount;
    }

    TOptional<FString> FEzInventoryGameSessionDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzInventoryGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzInventoryGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzInventoryGameSessionDomain::InventoryName() const
    {
        return Domain->InventoryName;
    }

    FEzInventoryGameSessionDomain::FEzInventoryGameSessionDomain(
        Gs2::Inventory::Domain::Model::FInventoryAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    Gs2::UE5::Inventory::Domain::Iterator::FEzDescribeItemSetsIteratorPtr FEzInventoryGameSessionDomain::ItemSets(
    ) const
    {
        return MakeShared<Gs2::UE5::Inventory::Domain::Iterator::FEzDescribeItemSetsIterator>(
            Domain,
            GameSession,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzInventoryGameSessionDomain::SubscribeItemSets(TFunction<void()> Callback)
    {
        return Domain->SubscribeItemSets(
            Callback
        );
    }

    void FEzInventoryGameSessionDomain::UnsubscribeItemSets(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeItemSets(
            CallbackId
        );
    }

    Gs2::UE5::Inventory::Domain::Model::FEzItemSetGameSessionDomainPtr FEzInventoryGameSessionDomain::ItemSet(
        const FString ItemName,
        const TOptional<FString> ItemSetName
    ) const
    {
        return MakeShared<Gs2::UE5::Inventory::Domain::Model::FEzItemSetGameSessionDomain>(
            Domain->ItemSet(
                ItemName,
                ItemSetName
            ),
            GameSession,
            ConnectionValue
        );
    }

    FEzInventoryGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzInventoryGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzInventoryGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Inventory::Model::FEzInventoryPtr> Result
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
                *Result = Gs2::UE5::Inventory::Model::FEzInventory::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzInventoryGameSessionDomain::FModelTask>> FEzInventoryGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzInventoryGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Inventory::Model::FEzInventoryPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Inventory::Model::FInventoryPtr Item)
            {
                Callback(Gs2::UE5::Inventory::Model::FEzInventory::FromModel(Item));
            }
        );
    }

    void FEzInventoryGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
