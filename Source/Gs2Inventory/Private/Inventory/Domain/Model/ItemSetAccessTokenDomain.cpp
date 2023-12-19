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

#include "Inventory/Domain/Model/ItemSetAccessToken.h"
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

    FItemSetAccessTokenDomain::FItemSetAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> InventoryName,
        const TOptional<FString> ItemName,
        const TOptional<FString> ItemSetName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Inventory::FGs2InventoryRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        InventoryName(InventoryName),
        ItemName(ItemName),
        ItemSetName(ItemSetName),
        ParentKey(Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            InventoryName,
            "ItemSet"
        ))
    {
    }

    FItemSetAccessTokenDomain::FItemSetAccessTokenDomain(
        const FItemSetAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        InventoryName(From.InventoryName),
        ItemName(From.ItemName),
        ItemSetName(From.ItemSetName),
        ParentKey(From.ParentKey)
    {

    }

    FItemSetAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FItemSetAccessTokenDomain>& Self,
        const Request::FGetItemSetRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FItemSetAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FItemSetAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Inventory::Model::FItemSet>>>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithInventoryName(Self->InventoryName)
            ->WithItemName(Self->ItemName)
            ->WithItemSetName(Self->ItemSetName);
        const auto Future = Self->Client->GetItemSet(
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
                        Self->UserId(),
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
                        Self->UserId(),
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
                        Self->UserId(),
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
                    Self->UserId(),
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

    TSharedPtr<FAsyncTask<FItemSetAccessTokenDomain::FGetTask>> FItemSetAccessTokenDomain::Get(
        Request::FGetItemSetRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FItemSetAccessTokenDomain::FGetItemWithSignatureTask::FGetItemWithSignatureTask(
        const TSharedPtr<FItemSetAccessTokenDomain>& Self,
        const Request::FGetItemWithSignatureRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FItemSetAccessTokenDomain::FGetItemWithSignatureTask::FGetItemWithSignatureTask(
        const FGetItemWithSignatureTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FItemSetAccessTokenDomain::FGetItemWithSignatureTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FItemSetAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithInventoryName(Self->InventoryName)
            ->WithItemName(Self->ItemName)
            ->WithItemSetName(Self->ItemSetName);
        const auto Future = Self->Client->GetItemWithSignature(
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
                        Self->UserId(),
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
                        Self->UserId(),
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
                        Self->UserId(),
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
                    Self->UserId(),
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
        Gs2::Inventory::Domain::Model::FItemSetAccessTokenDomainPtr Domain = nullptr;
        if (ResultModel->GetItems()->Num() > 0) {
            Domain = MakeShared<Gs2::Inventory::Domain::Model::FItemSetAccessTokenDomain>(
                Self->Gs2,
                Self->Service,
                Request->GetNamespaceName(),
                Self->AccessToken,
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

    TSharedPtr<FAsyncTask<FItemSetAccessTokenDomain::FGetItemWithSignatureTask>> FItemSetAccessTokenDomain::GetItemWithSignature(
        Request::FGetItemWithSignatureRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetItemWithSignatureTask>>(this->AsShared(), Request);
    }

    FItemSetAccessTokenDomain::FConsumeTask::FConsumeTask(
        const TSharedPtr<FItemSetAccessTokenDomain>& Self,
        const Request::FConsumeItemSetRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FItemSetAccessTokenDomain::FConsumeTask::FConsumeTask(
        const FConsumeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FItemSetAccessTokenDomain::FConsumeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FItemSetAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithInventoryName(Self->InventoryName)
            ->WithItemName(Self->ItemName)
            ->WithItemSetName(Self->ItemSetName);
        const auto Future = Self->Client->ConsumeItemSet(
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
                        Self->UserId(),
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
                        Self->UserId(),
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
                        Self->UserId(),
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
                    Self->UserId(),
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
        Gs2::Inventory::Domain::Model::FItemSetAccessTokenDomainPtr Domain = nullptr;
        if (ResultModel->GetItems()->Num() > 0) {
            Domain = MakeShared<Gs2::Inventory::Domain::Model::FItemSetAccessTokenDomain>(
                Self->Gs2,
                Self->Service,
                Request->GetNamespaceName(),
                Self->AccessToken,
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

    TSharedPtr<FAsyncTask<FItemSetAccessTokenDomain::FConsumeTask>> FItemSetAccessTokenDomain::Consume(
        Request::FConsumeItemSetRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FConsumeTask>>(this->AsShared(), Request);
    }

    FItemSetAccessTokenDomain::FVerifyTask::FVerifyTask(
        const TSharedPtr<FItemSetAccessTokenDomain>& Self,
        const Request::FVerifyItemSetRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FItemSetAccessTokenDomain::FVerifyTask::FVerifyTask(
        const FVerifyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FItemSetAccessTokenDomain::FVerifyTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FItemSetAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithInventoryName(Self->InventoryName)
            ->WithItemName(Self->ItemName)
            ->WithItemSetName(Self->ItemSetName);
        const auto Future = Self->Client->VerifyItemSet(
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

    TSharedPtr<FAsyncTask<FItemSetAccessTokenDomain::FVerifyTask>> FItemSetAccessTokenDomain::Verify(
        Request::FVerifyItemSetRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyTask>>(this->AsShared(), Request);
    }

    FItemSetAccessTokenDomain::FAddReferenceOfTask::FAddReferenceOfTask(
        const TSharedPtr<FItemSetAccessTokenDomain>& Self,
        const Request::FAddReferenceOfRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FItemSetAccessTokenDomain::FAddReferenceOfTask::FAddReferenceOfTask(
        const FAddReferenceOfTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FItemSetAccessTokenDomain::FAddReferenceOfTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FReferenceOfAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithInventoryName(Self->InventoryName)
            ->WithItemName(Self->ItemName)
            ->WithItemSetName(Self->ItemSetName);
        const auto Future = Self->Client->AddReferenceOf(
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
                    Self->UserId(),
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
                    Self->UserId(),
                    "Inventory"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheKey(
                    ResultModel->GetInventory()->GetInventoryName()
                );
            }
        }
        const auto Domain = MakeShared<Gs2::Inventory::Domain::Model::FReferenceOfAccessTokenDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Self->AccessToken,
            Request->GetInventoryName(),
            Request->GetItemName(),
            Request->GetItemSetName(),
            Request->GetReferenceOf()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FItemSetAccessTokenDomain::FAddReferenceOfTask>> FItemSetAccessTokenDomain::AddReferenceOf(
        Request::FAddReferenceOfRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAddReferenceOfTask>>(this->AsShared(), Request);
    }

    Gs2::Inventory::Domain::Iterator::FDescribeReferenceOfIteratorPtr FItemSetAccessTokenDomain::ReferenceOves(
    ) const
    {
        return MakeShared<Gs2::Inventory::Domain::Iterator::FDescribeReferenceOfIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            InventoryName,
            AccessToken,
            ItemName,
            ItemSetName
        );
    }

    TSharedPtr<Gs2::Inventory::Domain::Model::FReferenceOfAccessTokenDomain> FItemSetAccessTokenDomain::ReferenceOf(
        const FString ReferenceOf
    )
    {
        return MakeShared<Gs2::Inventory::Domain::Model::FReferenceOfAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            InventoryName,
            ItemName,
            ItemSetName,
            ReferenceOf == TEXT("") ? TOptional<FString>() : TOptional<FString>(ReferenceOf)
        );
    }

    FString FItemSetAccessTokenDomain::CreateCacheParentKey(
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

    FString FItemSetAccessTokenDomain::CreateCacheKey(
        TOptional<FString> ItemName,
        TOptional<FString> ItemSetName
    )
    {
        return FString("") +
            (ItemName.IsSet() ? *ItemName : "null") + ":" + 
            (ItemSetName.IsSet() ? *ItemSetName : "null");
    }

    FItemSetAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FItemSetAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FItemSetAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FItemSetAccessTokenDomain::FModelTask::Action(
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
                MakeShared<Gs2::Inventory::Request::FGetItemSetRequest>()
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

    TSharedPtr<FAsyncTask<FItemSetAccessTokenDomain::FModelTask>> FItemSetAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FItemSetAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FItemSetAccessTokenDomain::Subscribe(
        TFunction<void(TSharedPtr<Gs2::Inventory::Model::FItemSetEntry>)> Callback
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
                Callback(StaticCastSharedPtr<Gs2::Inventory::Model::FItemSetEntry>(obj));
            }
        );
    }

    void FItemSetAccessTokenDomain::Unsubscribe(
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

