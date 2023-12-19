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
 *
 * deny overwrite
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Inventory/Domain/Model/ItemSet.h"
#include "Inventory/Domain/Model/Namespace.h"
#include "Inventory/Domain/Model/InventoryModelMaster.h"
#include "Inventory/Domain/Model/InventoryModel.h"
#include "Inventory/Domain/Model/ItemModelMaster.h"
#include "Inventory/Domain/Model/ItemModel.h"
#include "Inventory/Domain/Model/SimpleInventoryModelMaster.h"
#include "Inventory/Domain/Model/SimpleInventoryModel.h"
#include "Inventory/Domain/Model/SimpleItemModelMaster.h"
#include "Inventory/Domain/Model/SimpleItemModel.h"
#include "Inventory/Domain/Model/BigInventoryModelMaster.h"
#include "Inventory/Domain/Model/BigInventoryModel.h"
#include "Inventory/Domain/Model/BigItemModelMaster.h"
#include "Inventory/Domain/Model/BigItemModel.h"
#include "Inventory/Domain/Model/CurrentItemModelMaster.h"
#include "Inventory/Domain/Model/Inventory.h"
#include "Inventory/Domain/Model/InventoryAccessToken.h"
#include "Inventory/Domain/Model/ItemSet.h"
#include "Inventory/Domain/Model/ItemSetAccessToken.h"
#include "Inventory/Domain/Model/ReferenceOf.h"
#include "Inventory/Domain/Model/ReferenceOfAccessToken.h"
#include "Inventory/Domain/Model/SimpleInventory.h"
#include "Inventory/Domain/Model/SimpleInventoryAccessToken.h"
#include "Inventory/Domain/Model/SimpleItem.h"
#include "Inventory/Domain/Model/SimpleItemAccessToken.h"
#include "Inventory/Domain/Model/BigInventory.h"
#include "Inventory/Domain/Model/BigInventoryAccessToken.h"
#include "Inventory/Domain/Model/BigItem.h"
#include "Inventory/Domain/Model/BigItemAccessToken.h"
#include "Inventory/Domain/Model/User.h"
#include "Inventory/Domain/Model/UserAccessToken.h"
#include "Inventory/Domain/Model/ItemSetEntry.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Inventory::Domain::Model
{

    FItemSetDomain::FItemSetDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> InventoryName,
        const TOptional<FString> ItemName,
        const TOptional<FString> ItemSetName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Inventory::FGs2InventoryRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        InventoryName(InventoryName),
        ItemName(ItemName),
        ItemSetName(ItemSetName),
        ParentKey(Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            InventoryName,
            "ItemSet"
        ))
    {
    }

    FItemSetDomain::FItemSetDomain(
        const FItemSetDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        InventoryName(From.InventoryName),
        ItemName(From.ItemName),
        ItemSetName(From.ItemSetName),
        ParentKey(From.ParentKey)
    {

    }

    FItemSetDomain::FGetTask::FGetTask(
        const TSharedPtr<FItemSetDomain>& Self,
        const Request::FGetItemSetByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FItemSetDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FItemSetDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Inventory::Model::FItemSet>>>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithInventoryName(Self->InventoryName)
            ->WithItemName(Self->ItemName)
            ->WithItemSetName(Self->ItemSetName);
        const auto Future = Self->Client->GetItemSetByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            {
                for (auto Item : *ResultModel->GetItems())
                {
                    const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheParentKey(
                        Self->NamespaceName,
                        Self->UserId,
                        Self->InventoryName,
                        "ItemSet"
                    );
                    const auto Key = Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheKey(
                        Item->GetItemName(),
                        Item->GetName()
                    );
                    if (Item->GetCount() == 0) {
                        Self->Gs2->Cache->Put(
                            Gs2::Inventory::Model::FItemSetEntry::TypeName,
                            ParentKey,
                            Key,
                            nullptr,
                            Item->GetExpiresAt().IsSet() && *Item->GetExpiresAt() != 0 ? FDateTime::FromUnixTimestamp(*Item->GetExpiresAt()/1000) : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                        );
                    }
                    else
                    {
                        Self->Gs2->Cache->Put(
                            Gs2::Inventory::Model::FItemSetEntry::TypeName,
                            ParentKey,
                            Key,
                            MakeShared<Gs2::Inventory::Model::FItemSetEntry>(Item),
                            Item->GetExpiresAt().IsSet() && *Item->GetExpiresAt() != 0 ? FDateTime::FromUnixTimestamp(*Item->GetExpiresAt()/1000) : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                        );
                    }
                }
                if (ResultModel->GetItems()->Num() == 0)
                {
                    const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheParentKey(
                        Self->NamespaceName,
                        Self->UserId,
                        Self->InventoryName,
                        "ItemSet"
                    );
                    const auto Key = Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheKey(
                        Self->ItemName,
                        TOptional<FString>()
                        );
                    Self->Gs2->Cache->Put(
                        Gs2::Inventory::Model::FItemSetEntry::TypeName,
                        Self->ParentKey,
                        Key,
                        MakeShared<Gs2::Inventory::Model::FItemSetEntry>(*ResultModel->GetItems()),
                        FDateTime::FromUnixTimestamp((FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)).ToUnixTimestamp())
                    );
                }
                TMap<FString, TSharedPtr<TArray<Gs2::Inventory::Model::FItemSetPtr>>> Groups;
                for (auto Item : *ResultModel->GetItems())
                {
                    if (!Groups.Contains(*Item->GetItemName()))
                    {
                        Groups.Add(*Item->GetItemName(), MakeShared<TArray<Gs2::Inventory::Model::FItemSetPtr>>());
                    }
                    Groups[*Item->GetItemName()]->Add(Item);
                }
                for (auto Group : Groups)
                {
                    const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheParentKey(
                        Self->NamespaceName,
                        Self->UserId,
                        Self->InventoryName,
                        "ItemSet"
                    );
                    const auto Key = Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheKey(
                        Group.Key,
                        TOptional<FString>()
                    );
                    int64 ExpiresAt = (FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)).ToUnixTimestamp() * 1000;
                    for (auto Item : *Group.Value)
                    {
                        if (Item->GetExpiresAt().IsSet())
                        {
                            if (*Item->GetExpiresAt() != 0 && ExpiresAt > *Item->GetExpiresAt())
                            {
                                ExpiresAt = *Item->GetExpiresAt();
                            }
                        }
                    }
                    Self->Gs2->Cache->Put(
                        Gs2::Inventory::Model::FItemSetEntry::TypeName,
                        Self->ParentKey,
                        Key,
                        MakeShared<Gs2::Inventory::Model::FItemSetEntry>(*Group.Value),
                        FDateTime::FromUnixTimestamp(ExpiresAt / 1000)
                    );
                }
            }
            if (ResultModel->GetItemModel() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryModelDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->InventoryName,
                    "ItemModel"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FItemModelDomain::CreateCacheKey(
                    ResultModel->GetItemModel()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Inventory::Model::FItemModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItemModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetInventory() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Inventory"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheKey(
                    ResultModel->GetInventory()->GetInventoryName()
                );
                TSharedPtr<Gs2::Inventory::Model::FInventory> Item;
                auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Inventory::Model::FInventory>(
                    ParentKey,
                    Key,
                    &Item
                );
                if (Item == nullptr || *Item->GetRevision() < *ResultModel->GetInventory()->GetRevision())
                {
                    int64 ExpiresAt = (FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)).ToUnixTimestamp() * 1000;
                    for (auto Item2 : *ResultModel->GetItems())
                    {
                        if (Item2->GetExpiresAt().IsSet())
                        {
                            if (*Item2->GetExpiresAt() != 0 && ExpiresAt > *Item2->GetExpiresAt())
                            {
                                ExpiresAt = *Item2->GetExpiresAt();
                            }
                        }
                    }
                    Self->Gs2->Cache->Put(
                        Gs2::Inventory::Model::FInventory::TypeName,
                        ParentKey,
                        Key,
                        ResultModel->GetInventory(),
                        FDateTime::FromUnixTimestamp(ExpiresAt / 1000)
                    );
                }
            }
        }
        *Result = ResultModel->GetItems();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FItemSetDomain::FGetTask>> FItemSetDomain::Get(
        Request::FGetItemSetByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FItemSetDomain::FGetItemWithSignatureTask::FGetItemWithSignatureTask(
        const TSharedPtr<FItemSetDomain>& Self,
        const Request::FGetItemWithSignatureByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FItemSetDomain::FGetItemWithSignatureTask::FGetItemWithSignatureTask(
        const FGetItemWithSignatureTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FItemSetDomain::FGetItemWithSignatureTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FItemSetDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithInventoryName(Self->InventoryName)
            ->WithItemName(Self->ItemName)
            ->WithItemSetName(Self->ItemSetName);
        const auto Future = Self->Client->GetItemWithSignatureByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            {
                for (auto Item : *ResultModel->GetItems())
                {
                    const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheParentKey(
                        Self->NamespaceName,
                        Self->UserId,
                        Self->InventoryName,
                        "ItemSet"
                    );
                    const auto Key = Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheKey(
                        Item->GetItemName(),
                        Item->GetName()
                    );
                    if (Item->GetCount() == 0) {
                        Self->Gs2->Cache->Put(
                            Gs2::Inventory::Model::FItemSetEntry::TypeName,
                            ParentKey,
                            Key,
                            nullptr,
                            Item->GetExpiresAt().IsSet() && *Item->GetExpiresAt() != 0 ? FDateTime::FromUnixTimestamp(*Item->GetExpiresAt()/1000) : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                        );
                    }
                    else
                    {
                        Self->Gs2->Cache->Put(
                            Gs2::Inventory::Model::FItemSetEntry::TypeName,
                            ParentKey,
                            Key,
                            MakeShared<Gs2::Inventory::Model::FItemSetEntry>(Item),
                            Item->GetExpiresAt().IsSet() && *Item->GetExpiresAt() != 0 ? FDateTime::FromUnixTimestamp(*Item->GetExpiresAt()/1000) : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                        );
                    }
                }
                if (ResultModel->GetItems()->Num() == 0)
                {
                    const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheParentKey(
                        Self->NamespaceName,
                        Self->UserId,
                        Self->InventoryName,
                        "ItemSet"
                    );
                    const auto Key = Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheKey(
                        Self->ItemName,
                        TOptional<FString>()
                        );
                    Self->Gs2->Cache->Put(
                        Gs2::Inventory::Model::FItemSetEntry::TypeName,
                        Self->ParentKey,
                        Key,
                        MakeShared<Gs2::Inventory::Model::FItemSetEntry>(*ResultModel->GetItems()),
                        FDateTime::FromUnixTimestamp((FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)).ToUnixTimestamp())
                    );
                }
                TMap<FString, TSharedPtr<TArray<Gs2::Inventory::Model::FItemSetPtr>>> Groups;
                for (auto Item : *ResultModel->GetItems())
                {
                    if (!Groups.Contains(*Item->GetItemName()))
                    {
                        Groups.Add(*Item->GetItemName(), MakeShared<TArray<Gs2::Inventory::Model::FItemSetPtr>>());
                    }
                    Groups[*Item->GetItemName()]->Add(Item);
                }
                for (auto Group : Groups)
                {
                    const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheParentKey(
                        Self->NamespaceName,
                        Self->UserId,
                        Self->InventoryName,
                        "ItemSet"
                    );
                    const auto Key = Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheKey(
                        Group.Key,
                        TOptional<FString>()
                    );
                    int64 ExpiresAt = (FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)).ToUnixTimestamp() * 1000;
                    for (auto Item : *Group.Value)
                    {
                        if (Item->GetExpiresAt().IsSet())
                        {
                            if (*Item->GetExpiresAt() != 0 && ExpiresAt > *Item->GetExpiresAt())
                            {
                                ExpiresAt = *Item->GetExpiresAt();
                            }
                        }
                    }
                    Self->Gs2->Cache->Put(
                        Gs2::Inventory::Model::FItemSetEntry::TypeName,
                        Self->ParentKey,
                        Key,
                        MakeShared<Gs2::Inventory::Model::FItemSetEntry>(*Group.Value),
                        FDateTime::FromUnixTimestamp(ExpiresAt / 1000)
                    );
                }
            }
            if (ResultModel->GetItemModel() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryModelDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->InventoryName,
                    "ItemModel"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FItemModelDomain::CreateCacheKey(
                    ResultModel->GetItemModel()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Inventory::Model::FItemModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItemModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetInventory() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Inventory"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheKey(
                    ResultModel->GetInventory()->GetInventoryName()
                );
                TSharedPtr<Gs2::Inventory::Model::FInventory> Item;
                auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Inventory::Model::FInventory>(
                    ParentKey,
                    Key,
                    &Item
                );
                if (Item == nullptr || *Item->GetRevision() < *ResultModel->GetInventory()->GetRevision())
                {
                    int64 ExpiresAt = (FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)).ToUnixTimestamp() * 1000;
                    for (auto Item2 : *ResultModel->GetItems())
                    {
                        if (Item2->GetExpiresAt().IsSet())
                        {
                            if (*Item2->GetExpiresAt() != 0 && ExpiresAt > *Item2->GetExpiresAt())
                            {
                                ExpiresAt = *Item2->GetExpiresAt();
                            }
                        }
                    }
                    Self->Gs2->Cache->Put(
                        Gs2::Inventory::Model::FInventory::TypeName,
                        ParentKey,
                        Key,
                        ResultModel->GetInventory(),
                        FDateTime::FromUnixTimestamp(ExpiresAt / 1000)
                    );
                }
            }
        }
        Gs2::Inventory::Domain::Model::FItemSetDomainPtr Domain = nullptr;
        if (ResultModel->GetItems()->Num() > 0) {
            Domain = MakeShared<Gs2::Inventory::Domain::Model::FItemSetDomain>(
                Self->Gs2,
                Self->Service,
                Request->GetNamespaceName(),
                (*ResultModel->GetItems())[0]->GetUserId(),
                (*ResultModel->GetItems())[0]->GetInventoryName(),
                (*ResultModel->GetItems())[0]->GetItemName(),
                (*ResultModel->GetItems())[0]->GetName()
            );
        } else {
            Domain = Self;
        }
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetBody().IsSet())
            {
                Self->Body = Domain->Body = ResultModel->GetBody();
            }
            if (ResultModel->GetSignature().IsSet())
            {
                Self->Signature = Domain->Signature = ResultModel->GetSignature();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FItemSetDomain::FGetItemWithSignatureTask>> FItemSetDomain::GetItemWithSignature(
        Request::FGetItemWithSignatureByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetItemWithSignatureTask>>(this->AsShared(), Request);
    }

    FItemSetDomain::FAcquireTask::FAcquireTask(
        const TSharedPtr<FItemSetDomain>& Self,
        const Request::FAcquireItemSetByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FItemSetDomain::FAcquireTask::FAcquireTask(
        const FAcquireTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FItemSetDomain::FAcquireTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FItemSetDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithInventoryName(Self->InventoryName)
            ->WithItemName(Self->ItemName)
            ->WithItemSetName(Self->ItemSetName);
        const auto Future = Self->Client->AcquireItemSetByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            {
                for (auto Item : *ResultModel->GetItems())
                {
                    const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheParentKey(
                        Self->NamespaceName,
                        Self->UserId,
                        Self->InventoryName,
                        "ItemSet"
                    );
                    const auto Key = Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheKey(
                        Item->GetItemName(),
                        Item->GetName()
                    );
                    if (Item->GetCount() == 0) {
                        Self->Gs2->Cache->Put(
                            Gs2::Inventory::Model::FItemSetEntry::TypeName,
                            ParentKey,
                            Key,
                            nullptr,
                            Item->GetExpiresAt().IsSet() && *Item->GetExpiresAt() != 0 ? FDateTime::FromUnixTimestamp(*Item->GetExpiresAt()/1000) : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                        );
                    }
                    else
                    {
                        Self->Gs2->Cache->Put(
                            Gs2::Inventory::Model::FItemSetEntry::TypeName,
                            ParentKey,
                            Key,
                            MakeShared<Gs2::Inventory::Model::FItemSetEntry>(Item),
                            Item->GetExpiresAt().IsSet() && *Item->GetExpiresAt() != 0 ? FDateTime::FromUnixTimestamp(*Item->GetExpiresAt()/1000) : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                        );
                    }
                }
                if (ResultModel->GetItems()->Num() == 0)
                {
                    const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheParentKey(
                        Self->NamespaceName,
                        Self->UserId,
                        Self->InventoryName,
                        "ItemSet"
                    );
                    const auto Key = Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheKey(
                        Self->ItemName,
                        TOptional<FString>()
                        );
                    Self->Gs2->Cache->Put(
                        Gs2::Inventory::Model::FItemSetEntry::TypeName,
                        Self->ParentKey,
                        Key,
                        MakeShared<Gs2::Inventory::Model::FItemSetEntry>(*ResultModel->GetItems()),
                        FDateTime::FromUnixTimestamp((FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)).ToUnixTimestamp())
                    );
                }
                TMap<FString, TSharedPtr<TArray<Gs2::Inventory::Model::FItemSetPtr>>> Groups;
                for (auto Item : *ResultModel->GetItems())
                {
                    if (!Groups.Contains(*Item->GetItemName()))
                    {
                        Groups.Add(*Item->GetItemName(), MakeShared<TArray<Gs2::Inventory::Model::FItemSetPtr>>());
                    }
                    Groups[*Item->GetItemName()]->Add(Item);
                }
                for (auto Group : Groups)
                {
                    const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheParentKey(
                        Self->NamespaceName,
                        Self->UserId,
                        Self->InventoryName,
                        "ItemSet"
                    );
                    const auto Key = Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheKey(
                        Group.Key,
                        TOptional<FString>()
                    );
                    int64 ExpiresAt = (FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)).ToUnixTimestamp() * 1000;
                    for (auto Item : *Group.Value)
                    {
                        if (Item->GetExpiresAt().IsSet())
                        {
                            if (*Item->GetExpiresAt() != 0 && ExpiresAt > *Item->GetExpiresAt())
                            {
                                ExpiresAt = *Item->GetExpiresAt();
                            }
                        }
                    }
                    Self->Gs2->Cache->Put(
                        Gs2::Inventory::Model::FItemSetEntry::TypeName,
                        Self->ParentKey,
                        Key,
                        MakeShared<Gs2::Inventory::Model::FItemSetEntry>(*Group.Value),
                        FDateTime::FromUnixTimestamp(ExpiresAt / 1000)
                    );
                }
            }
            if (ResultModel->GetItemModel() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryModelDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->InventoryName,
                    "ItemModel"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FItemModelDomain::CreateCacheKey(
                    ResultModel->GetItemModel()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Inventory::Model::FItemModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItemModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetInventory() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Inventory"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheKey(
                    ResultModel->GetInventory()->GetInventoryName()
                );
                TSharedPtr<Gs2::Inventory::Model::FInventory> Item;
                auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Inventory::Model::FInventory>(
                    ParentKey,
                    Key,
                    &Item
                );
                if (Item == nullptr || *Item->GetRevision() < *ResultModel->GetInventory()->GetRevision())
                {
                    int64 ExpiresAt = (FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)).ToUnixTimestamp() * 1000;
                    for (auto Item2 : *ResultModel->GetItems())
                    {
                        if (Item2->GetExpiresAt().IsSet())
                        {
                            if (*Item2->GetExpiresAt() != 0 && ExpiresAt > *Item2->GetExpiresAt())
                            {
                                ExpiresAt = *Item2->GetExpiresAt();
                            }
                        }
                    }
                    Self->Gs2->Cache->Put(
                        Gs2::Inventory::Model::FInventory::TypeName,
                        ParentKey,
                        Key,
                        ResultModel->GetInventory(),
                        FDateTime::FromUnixTimestamp(ExpiresAt / 1000)
                    );
                }
            }
        }
        Gs2::Inventory::Domain::Model::FItemSetDomainPtr Domain = nullptr;
        if (ResultModel->GetItems()->Num() > 0) {
            Domain = MakeShared<Gs2::Inventory::Domain::Model::FItemSetDomain>(
                Self->Gs2,
                Self->Service,
                Request->GetNamespaceName(),
                (*ResultModel->GetItems())[0]->GetUserId(),
                (*ResultModel->GetItems())[0]->GetInventoryName(),
                (*ResultModel->GetItems())[0]->GetItemName(),
                (*ResultModel->GetItems())[0]->GetName()
            );
        } else {
            Domain = Self;
        }
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetOverflowCount().IsSet())
            {
                Self->OverflowCount = Domain->OverflowCount = ResultModel->GetOverflowCount();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FItemSetDomain::FAcquireTask>> FItemSetDomain::Acquire(
        Request::FAcquireItemSetByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAcquireTask>>(this->AsShared(), Request);
    }

    FItemSetDomain::FConsumeTask::FConsumeTask(
        const TSharedPtr<FItemSetDomain>& Self,
        const Request::FConsumeItemSetByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FItemSetDomain::FConsumeTask::FConsumeTask(
        const FConsumeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FItemSetDomain::FConsumeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FItemSetDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithInventoryName(Self->InventoryName)
            ->WithItemName(Self->ItemName)
            ->WithItemSetName(Self->ItemSetName);
        const auto Future = Self->Client->ConsumeItemSetByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            {
                for (auto Item : *ResultModel->GetItems())
                {
                    const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheParentKey(
                        Self->NamespaceName,
                        Self->UserId,
                        Self->InventoryName,
                        "ItemSet"
                    );
                    const auto Key = Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheKey(
                        Item->GetItemName(),
                        Item->GetName()
                    );
                    if (Item->GetCount() == 0) {
                        Self->Gs2->Cache->Put(
                            Gs2::Inventory::Model::FItemSetEntry::TypeName,
                            ParentKey,
                            Key,
                            nullptr,
                            Item->GetExpiresAt().IsSet() && *Item->GetExpiresAt() != 0 ? FDateTime::FromUnixTimestamp(*Item->GetExpiresAt()/1000) : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                        );
                    }
                    else
                    {
                        Self->Gs2->Cache->Put(
                            Gs2::Inventory::Model::FItemSetEntry::TypeName,
                            ParentKey,
                            Key,
                            MakeShared<Gs2::Inventory::Model::FItemSetEntry>(Item),
                            Item->GetExpiresAt().IsSet() && *Item->GetExpiresAt() != 0 ? FDateTime::FromUnixTimestamp(*Item->GetExpiresAt()/1000) : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                        );
                    }
                }
                if (ResultModel->GetItems()->Num() == 0)
                {
                    const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheParentKey(
                        Self->NamespaceName,
                        Self->UserId,
                        Self->InventoryName,
                        "ItemSet"
                    );
                    const auto Key = Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheKey(
                        Self->ItemName,
                        TOptional<FString>()
                        );
                    Self->Gs2->Cache->Put(
                        Gs2::Inventory::Model::FItemSetEntry::TypeName,
                        Self->ParentKey,
                        Key,
                        MakeShared<Gs2::Inventory::Model::FItemSetEntry>(*ResultModel->GetItems()),
                        FDateTime::FromUnixTimestamp((FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)).ToUnixTimestamp())
                    );
                }
                TMap<FString, TSharedPtr<TArray<Gs2::Inventory::Model::FItemSetPtr>>> Groups;
                for (auto Item : *ResultModel->GetItems())
                {
                    if (!Groups.Contains(*Item->GetItemName()))
                    {
                        Groups.Add(*Item->GetItemName(), MakeShared<TArray<Gs2::Inventory::Model::FItemSetPtr>>());
                    }
                    Groups[*Item->GetItemName()]->Add(Item);
                }
                for (auto Group : Groups)
                {
                    const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheParentKey(
                        Self->NamespaceName,
                        Self->UserId,
                        Self->InventoryName,
                        "ItemSet"
                    );
                    const auto Key = Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheKey(
                        Group.Key,
                        TOptional<FString>()
                    );
                    int64 ExpiresAt = (FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)).ToUnixTimestamp() * 1000;
                    for (auto Item : *Group.Value)
                    {
                        if (Item->GetExpiresAt().IsSet())
                        {
                            if (*Item->GetExpiresAt() != 0 && ExpiresAt > *Item->GetExpiresAt())
                            {
                                ExpiresAt = *Item->GetExpiresAt();
                            }
                        }
                    }
                    Self->Gs2->Cache->Put(
                        Gs2::Inventory::Model::FItemSetEntry::TypeName,
                        Self->ParentKey,
                        Key,
                        MakeShared<Gs2::Inventory::Model::FItemSetEntry>(*Group.Value),
                        FDateTime::FromUnixTimestamp(ExpiresAt / 1000)
                    );
                }
            }
            if (ResultModel->GetItemModel() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryModelDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->InventoryName,
                    "ItemModel"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FItemModelDomain::CreateCacheKey(
                    ResultModel->GetItemModel()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Inventory::Model::FItemModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItemModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetInventory() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Inventory"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheKey(
                    ResultModel->GetInventory()->GetInventoryName()
                );
                TSharedPtr<Gs2::Inventory::Model::FInventory> Item;
                auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Inventory::Model::FInventory>(
                    ParentKey,
                    Key,
                    &Item
                );
                if (Item == nullptr || *Item->GetRevision() < *ResultModel->GetInventory()->GetRevision())
                {
                    int64 ExpiresAt = (FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)).ToUnixTimestamp() * 1000;
                    for (auto Item2 : *ResultModel->GetItems())
                    {
                        if (Item2->GetExpiresAt().IsSet())
                        {
                            if (*Item2->GetExpiresAt() != 0 && ExpiresAt > *Item2->GetExpiresAt())
                            {
                                ExpiresAt = *Item2->GetExpiresAt();
                            }
                        }
                    }
                    Self->Gs2->Cache->Put(
                        Gs2::Inventory::Model::FInventory::TypeName,
                        ParentKey,
                        Key,
                        ResultModel->GetInventory(),
                        FDateTime::FromUnixTimestamp(ExpiresAt / 1000)
                    );
                }
            }
        }
        Gs2::Inventory::Domain::Model::FItemSetDomainPtr Domain = nullptr;
        if (ResultModel->GetItems()->Num() > 0) {
            Domain = MakeShared<Gs2::Inventory::Domain::Model::FItemSetDomain>(
                Self->Gs2,
                Self->Service,
                Request->GetNamespaceName(),
                (*ResultModel->GetItems())[0]->GetUserId(),
                (*ResultModel->GetItems())[0]->GetInventoryName(),
                (*ResultModel->GetItems())[0]->GetItemName(),
                (*ResultModel->GetItems())[0]->GetName()
            );
        } else {
            Domain = Self;
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FItemSetDomain::FConsumeTask>> FItemSetDomain::Consume(
        Request::FConsumeItemSetByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FConsumeTask>>(this->AsShared(), Request);
    }

    FItemSetDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FItemSetDomain>& Self,
        const Request::FDeleteItemSetByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FItemSetDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FItemSetDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FItemSetDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithInventoryName(Self->InventoryName)
            ->WithItemName(Self->ItemName)
            ->WithItemSetName(Self->ItemSetName);
        const auto Future = Self->Client->DeleteItemSetByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            {
                for (auto Item : *ResultModel->GetItems())
                {
                    const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheParentKey(
                        Self->NamespaceName,
                        Self->UserId,
                        Self->InventoryName,
                        "ItemSet"
                    );
                    const auto Key = Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheKey(
                        Item->GetItemName(),
                        Item->GetName()
                    );
                    Self->Gs2->Cache->Put(
                        Gs2::Inventory::Model::FItemSetEntry::TypeName,
                        ParentKey,
                        Key,
                        nullptr,
                        FDateTime::FromUnixTimestamp((FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)).ToUnixTimestamp())
                    );
                }
                if (ResultModel->GetItems()->Num() == 0)
                {
                    const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheParentKey(
                        Self->NamespaceName,
                        Self->UserId,
                        Self->InventoryName,
                        "ItemSet"
                    );
                    const auto Key = Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheKey(
                        Self->ItemName,
                        TOptional<FString>()
                        );
                    Self->Gs2->Cache->Put(
                        Gs2::Inventory::Model::FItemSetEntry::TypeName,
                        Self->ParentKey,
                        Key,
                        MakeShared<Gs2::Inventory::Model::FItemSetEntry>(*ResultModel->GetItems()),
                        FDateTime::FromUnixTimestamp((FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)).ToUnixTimestamp())
                    );
                }
                TMap<FString, TSharedPtr<TArray<Gs2::Inventory::Model::FItemSetPtr>>> Groups;
                for (auto Item : *ResultModel->GetItems())
                {
                    if (!Groups.Contains(*Item->GetItemName()))
                    {
                        Groups.Add(*Item->GetItemName(), MakeShared<TArray<Gs2::Inventory::Model::FItemSetPtr>>());
                    }
                    Groups[*Item->GetItemName()]->Add(Item);
                }
                for (auto Group : Groups)
                {
                    const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheParentKey(
                        Self->NamespaceName,
                        Self->UserId,
                        Self->InventoryName,
                        "ItemSet"
                    );
                    const auto Key = Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheKey(
                        Group.Key,
                        TOptional<FString>()
                    );
                    int64 ExpiresAt = (FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)).ToUnixTimestamp() * 1000;
                    for (auto Item : *Group.Value)
                    {
                        if (Item->GetExpiresAt().IsSet())
                        {
                            if (*Item->GetExpiresAt() != 0 && ExpiresAt > *Item->GetExpiresAt())
                            {
                                ExpiresAt = *Item->GetExpiresAt();
                            }
                        }
                    }
                    Self->Gs2->Cache->Put(
                        Gs2::Inventory::Model::FItemSetEntry::TypeName,
                        Self->ParentKey,
                        Key,
                        MakeShared<Gs2::Inventory::Model::FItemSetEntry>(*Group.Value),
                        FDateTime::FromUnixTimestamp(ExpiresAt / 1000)
                    );
                }
            }
            if (ResultModel->GetItemModel() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryModelDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->InventoryName,
                    "ItemModel"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FItemModelDomain::CreateCacheKey(
                    ResultModel->GetItemModel()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::Inventory::Model::FItemModel::TypeName, ParentKey, Key);
            }
            if (ResultModel->GetInventory() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Inventory"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheKey(
                    ResultModel->GetInventory()->GetInventoryName()
                );
                Self->Gs2->Cache->Delete(Gs2::Inventory::Model::FInventory::TypeName, ParentKey, Key);
            }
        }
        Gs2::Inventory::Domain::Model::FItemSetDomainPtr Domain = nullptr;
        if (ResultModel->GetItems()->Num() > 0) {
            Domain = MakeShared<Gs2::Inventory::Domain::Model::FItemSetDomain>(
                Self->Gs2,
                Self->Service,
                Request->GetNamespaceName(),
                (*ResultModel->GetItems())[0]->GetUserId(),
                (*ResultModel->GetItems())[0]->GetInventoryName(),
                (*ResultModel->GetItems())[0]->GetItemName(),
                (*ResultModel->GetItems())[0]->GetName()
            );
        } else {
            Domain = Self;
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FItemSetDomain::FDeleteTask>> FItemSetDomain::Delete(
        Request::FDeleteItemSetByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FItemSetDomain::FVerifyTask::FVerifyTask(
        const TSharedPtr<FItemSetDomain>& Self,
        const Request::FVerifyItemSetByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FItemSetDomain::FVerifyTask::FVerifyTask(
        const FVerifyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FItemSetDomain::FVerifyTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FItemSetDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithInventoryName(Self->InventoryName)
            ->WithItemName(Self->ItemName)
            ->WithItemSetName(Self->ItemSetName);
        const auto Future = Self->Client->VerifyItemSetByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
        }
        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FItemSetDomain::FVerifyTask>> FItemSetDomain::Verify(
        Request::FVerifyItemSetByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyTask>>(this->AsShared(), Request);
    }

    FItemSetDomain::FAddReferenceOfTask::FAddReferenceOfTask(
        const TSharedPtr<FItemSetDomain>& Self,
        const Request::FAddReferenceOfByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FItemSetDomain::FAddReferenceOfTask::FAddReferenceOfTask(
        const FAddReferenceOfTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FItemSetDomain::FAddReferenceOfTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FReferenceOfDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithInventoryName(Self->InventoryName)
            ->WithItemName(Self->ItemName)
            ->WithItemSetName(Self->ItemSetName);
        const auto Future = Self->Client->AddReferenceOfByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItemSet() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    Self->InventoryName,
                    "ItemSet"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheKey(
                    ResultModel->GetItemSet()->GetItemName(),
                    ResultModel->GetItemSet()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Inventory::Model::FItemSetEntry::TypeName,
                    ParentKey,
                    Key,
                    MakeShared<Gs2::Inventory::Model::FItemSetEntry>(ResultModel->GetItemSet()),
                    ResultModel->GetItemSet()->GetExpiresAt().IsSet() && *ResultModel->GetItemSet()->GetExpiresAt() != 0 ? FDateTime::FromUnixTimestamp(*ResultModel->GetItemSet()->GetExpiresAt() / 1000) : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetItemModel() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryModelDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->InventoryName,
                    "ItemModel"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FItemModelDomain::CreateCacheKey(
                    ResultModel->GetItemModel()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Inventory::Model::FItemModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItemModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetInventory() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Inventory"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheKey(
                    ResultModel->GetInventory()->GetInventoryName()
                );
            }
        }
        const auto Domain = MakeShared<Gs2::Inventory::Domain::Model::FReferenceOfDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Request->GetUserId(),
            Request->GetInventoryName(),
            Request->GetItemName(),
            Request->GetItemSetName(),
            Request->GetReferenceOf()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FItemSetDomain::FAddReferenceOfTask>> FItemSetDomain::AddReferenceOf(
        Request::FAddReferenceOfByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAddReferenceOfTask>>(this->AsShared(), Request);
    }

    Gs2::Inventory::Domain::Iterator::FDescribeReferenceOfByUserIdIteratorPtr FItemSetDomain::ReferenceOves(
    ) const
    {
        return MakeShared<Gs2::Inventory::Domain::Iterator::FDescribeReferenceOfByUserIdIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            InventoryName,
            UserId,
            ItemName,
            ItemSetName
        );
    }

    TSharedPtr<Gs2::Inventory::Domain::Model::FReferenceOfDomain> FItemSetDomain::ReferenceOf(
        const FString ReferenceOf
    )
    {
        return MakeShared<Gs2::Inventory::Domain::Model::FReferenceOfDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            InventoryName,
            ItemName,
            ItemSetName,
            ReferenceOf
        );
    }

    FString FItemSetDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> InventoryName,
        TOptional<FString> ItemName,
        TOptional<FString> ItemSetName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (InventoryName.IsSet() ? *InventoryName : "null") + ":" +
            (ItemName.IsSet() ? *ItemName : "null") + ":" +
            (ItemSetName.IsSet() ? *ItemSetName : "null") + ":" +
            ChildType;
    }

    FString FItemSetDomain::CreateCacheKey(
        TOptional<FString> ItemName,
        TOptional<FString> ItemSetName
    )
    {
        return FString("") +
            (ItemName.IsSet() ? *ItemName : "null") + ":" + 
            (ItemSetName.IsSet() ? *ItemSetName : "null");
    }

    FItemSetDomain::FModelTask::FModelTask(
        const TSharedPtr<FItemSetDomain> Self
    ): Self(Self)
    {

    }

    FItemSetDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FItemSetDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<TArray<Gs2::Inventory::Model::FItemSetPtr>>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        Gs2::Inventory::Model::FItemSetEntryPtr Value;
        const auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Inventory::Model::FItemSetEntry>(
            Self->ParentKey,
            Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheKey(
                Self->ItemName,
                TOptional<FString>()
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Inventory::Request::FGetItemSetByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheKey(
                    Self->ItemName,
                    Self->ItemSetName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Inventory::Model::FItemSetEntry::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "itemSet")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Inventory::Model::FItemSetEntry>(
                Self->ParentKey,
                Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheKey(
                    Self->ItemName,
                    TOptional<FString>()
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        if (Value != nullptr)
        {
            *Result = MakeShared<TArray<Inventory::Model::FItemSetPtr>>(Value->Value);
        }

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FItemSetDomain::FModelTask>> FItemSetDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FItemSetDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FItemSetDomain::Subscribe(
        TFunction<void(Inventory::Model::FItemSetEntryPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Inventory::Model::FItemSetEntry::TypeName,
            ParentKey,
            Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheKey(
                ItemName,
                ItemSetName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Inventory::Model::FItemSetEntry>(obj));
            }
        );
    }

    void FItemSetDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Inventory::Model::FItemSetEntry::TypeName,
            ParentKey,
            Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheKey(
                ItemName,
                ItemSetName
            ),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

