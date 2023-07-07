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

#include "Inventory/Domain/Model/Gs2InventoryEzSimpleInventoryGameSessionDomain.h"

namespace Gs2::UE5::Inventory::Domain::Model
{

    TOptional<FString> FEzSimpleInventoryGameSessionDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzSimpleInventoryGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzSimpleInventoryGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzSimpleInventoryGameSessionDomain::InventoryName() const
    {
        return Domain->InventoryName;
    }

    FEzSimpleInventoryGameSessionDomain::FEzSimpleInventoryGameSessionDomain(
        Gs2::Inventory::Domain::Model::FSimpleInventoryAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzSimpleInventoryGameSessionDomain::FConsumeSimpleItemsTask::FConsumeSimpleItemsTask(
        TSharedPtr<FEzSimpleInventoryGameSessionDomain> Self,
        TArray<TSharedPtr<Gs2::UE5::Inventory::Model::FEzConsumeCount>> ConsumeCounts
    ): Self(Self), ConsumeCounts(ConsumeCounts)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzSimpleInventoryGameSessionDomain::FConsumeSimpleItemsTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Inventory::Domain::Model::FEzSimpleItemGameSessionDomain>>>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FConsumeSimpleItemsTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->ConsumeSimpleItems(
                    MakeShared<Gs2::Inventory::Request::FConsumeSimpleItemsRequest>()
                        ->WithConsumeCounts([&]{
                            auto Arr = MakeShared<TArray<TSharedPtr<Gs2::Inventory::Model::FConsumeCount>>>();
                            for (auto Value : ConsumeCounts) {
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
                *Result = MakeShared<TArray<TSharedPtr<Gs2::UE5::Inventory::Domain::Model::FEzSimpleItemGameSessionDomain>>>();
                for (auto Value : *Task->GetTask().Result()) {
                    (**Result).Add(MakeShared<Gs2::UE5::Inventory::Domain::Model::FEzSimpleItemGameSessionDomain>(
                        Value,
                        Self->ProfileValue
                    ));
                }
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

    TSharedPtr<FAsyncTask<FEzSimpleInventoryGameSessionDomain::FConsumeSimpleItemsTask>> FEzSimpleInventoryGameSessionDomain::ConsumeSimpleItems(
        TArray<TSharedPtr<Gs2::UE5::Inventory::Model::FEzConsumeCount>> ConsumeCounts
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FConsumeSimpleItemsTask>>(
            this->AsShared(),
            ConsumeCounts
        );
    }

    Gs2::UE5::Inventory::Domain::Iterator::FEzDescribeSimpleItemsIteratorPtr FEzSimpleInventoryGameSessionDomain::SimpleItems(
    ) const
    {
        return MakeShared<Gs2::UE5::Inventory::Domain::Iterator::FEzDescribeSimpleItemsIterator>(
            Domain->SimpleItems(
            )
        );
    }

    Gs2::UE5::Inventory::Domain::Model::FEzSimpleItemGameSessionDomainPtr FEzSimpleInventoryGameSessionDomain::SimpleItem(
        const FString ItemName
    ) const
    {
        return MakeShared<Gs2::UE5::Inventory::Domain::Model::FEzSimpleItemGameSessionDomain>(
            Domain->SimpleItem(
                ItemName
            ),
            ProfileValue
        );
    }
}
