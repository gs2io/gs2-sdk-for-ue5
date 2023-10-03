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

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

// ReSharper disable CppUnusedIncludeDirective

#include "Inventory/Domain/Gs2Inventory.h"
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
#include "Inventory/Domain/Model/ItemSet.h"
#include "Inventory/Domain/Model/ItemSetEntry.h"
#include "Inventory/Domain/Model/ReferenceOf.h"
#include "Inventory/Domain/Model/SimpleInventory.h"
#include "Inventory/Domain/Model/SimpleItem.h"
#include "Inventory/Domain/Model/BigInventory.h"
#include "Inventory/Domain/Model/BigItem.h"
#include "Inventory/Domain/Model/User.h"
#include "Inventory/Domain/Model/UserAccessToken.h"

namespace Gs2::Inventory::Domain
{

    FGs2InventoryDomain::FGs2InventoryDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Inventory::FGs2InventoryRestClient>(Session)),
        ParentKey("inventory")
    {
    }

    FGs2InventoryDomain::FGs2InventoryDomain(
        const FGs2InventoryDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FGs2InventoryDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        TSharedPtr<FGs2InventoryDomain> Self,
        const Request::FCreateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2InventoryDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const FCreateNamespaceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2InventoryDomain::FCreateNamespaceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FNamespaceDomain>> Result
    )
    {
        const auto Future = Self->Client->CreateNamespace(
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
                const auto ParentKey = FString("inventory:Namespace");
                const auto Key = Gs2::Inventory::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Inventory::Model::FNamespace::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Inventory::Domain::Model::FNamespaceDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2InventoryDomain::FCreateNamespaceTask>> FGs2InventoryDomain::CreateNamespace(
        Request::FCreateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateNamespaceTask>>(this->AsShared(), Request);
    }

    Gs2::Inventory::Domain::Iterator::FDescribeNamespacesIteratorPtr FGs2InventoryDomain::Namespaces(
    ) const
    {
        return MakeShared<Gs2::Inventory::Domain::Iterator::FDescribeNamespacesIterator>(
            Cache,
            Client
        );
    }

    Gs2::Core::Domain::CallbackID FGs2InventoryDomain::SubscribeNamespaces(
    TFunction<void()> Callback
    )
    {
        return Cache->ListSubscribe(
            Gs2::Inventory::Model::FNamespace::TypeName,
            "inventory:Namespace",
            Callback
        );
    }

    void FGs2InventoryDomain::UnsubscribeNamespaces(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->ListUnsubscribe(
            Gs2::Inventory::Model::FNamespace::TypeName,
            "inventory:Namespace",
            CallbackID
        );
    }

    TSharedPtr<Gs2::Inventory::Domain::Model::FNamespaceDomain> FGs2InventoryDomain::Namespace(
        const FString NamespaceName
    ) const
    {
        return MakeShared<Gs2::Inventory::Domain::Model::FNamespaceDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName == TEXT("") ? TOptional<FString>() : TOptional<FString>(NamespaceName)
        );
    }

    void FGs2InventoryDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
        if (Method == "AddCapacityByUserId") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Request);
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Inventory::Request::FAddCapacityByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FAddCapacityByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Inventory"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetInventoryName()
                );
                Cache->Put(
                    Gs2::Inventory::Model::FInventory::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "SetCapacityByUserId") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Request);
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Inventory::Request::FSetCapacityByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FSetCapacityByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Inventory"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetInventoryName()
                );
                Cache->Put(
                    Gs2::Inventory::Model::FInventory::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "AcquireItemSetByUserId") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Request);
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Inventory::Request::FAcquireItemSetByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FAcquireItemSetByUserIdResult::FromJson(ResultModelJson);
            {
                for (auto Item : *ResultModel->GetItems())
                {
                    const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheParentKey(
                        RequestModel->GetNamespaceName(),
                        RequestModel->GetUserId(),
                        RequestModel->GetInventoryName(),
                        "ItemSet"
                    );
                    const auto Key = Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheKey(
                        Item->GetItemName(),
                        Item->GetName()
                    );
                    if (Item->GetCount() == 0) {
                        Cache->Delete(
                            Gs2::Inventory::Model::FItemSet::TypeName,
                            ParentKey,
                            Key
                        );
                    }
                    else
                    {
                        Cache->Put(
                            Gs2::Inventory::Model::FItemSet::TypeName,
                            ParentKey,
                            Key,
                            Item,
                            Item->GetExpiresAt().IsSet() && *Item->GetExpiresAt() != 0 ? FDateTime::FromUnixTimestamp(*Item->GetExpiresAt()/1000) : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                        );
                    }
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
                        RequestModel->GetNamespaceName(),
                        RequestModel->GetUserId(),
                        RequestModel->GetInventoryName(),
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
                    Cache->Put(
                        Gs2::Inventory::Model::FItemSetEntry::TypeName,
                        ParentKey,
                        Key,
                        MakeShared<Gs2::Inventory::Model::FItemSetEntry>(*Group.Value),
                        FDateTime::FromUnixTimestamp(ExpiresAt / 1000)
                    );
                }
            }
            if (ResultModel->GetItemModel() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryModelDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetInventoryName(),
                    "ItemModel"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FItemModelDomain::CreateCacheKey(
                    ResultModel->GetItemModel()->GetName()
                );
                Cache->Put(
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
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Inventory"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheKey(
                    ResultModel->GetInventory()->GetInventoryName()
                );
                TSharedPtr<Gs2::Inventory::Model::FInventory> Item;
                auto bCacheHit = Cache->TryGet<Gs2::Inventory::Model::FInventory>(
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
                    Cache->Put(
                        Gs2::Inventory::Model::FInventory::TypeName,
                        ParentKey,
                        Key,
                        ResultModel->GetInventory(),
                        FDateTime::FromUnixTimestamp(ExpiresAt / 1000)
                    );
                }
            }
        }
        if (Method == "AddReferenceOfByUserId") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Request);
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Inventory::Request::FAddReferenceOfByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FAddReferenceOfByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItemSet() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    RequestModel->GetInventoryName(),
                    "ItemSet"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheKey(
                    ResultModel->GetItemSet()->GetItemName(),
                    ResultModel->GetItemSet()->GetName()
                );
                Cache->Put(
                    Gs2::Inventory::Model::FItemSet::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItemSet(),
                    ResultModel->GetItemSet()->GetExpiresAt().IsSet() && *ResultModel->GetItemSet()->GetExpiresAt() != 0 ? FDateTime::FromUnixTimestamp(*ResultModel->GetItemSet()->GetExpiresAt() / 1000) : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetItemModel() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryModelDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetInventoryName(),
                    "ItemModel"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FItemModelDomain::CreateCacheKey(
                    ResultModel->GetItemModel()->GetName()
                );
                Cache->Put(
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
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Inventory"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheKey(
                    ResultModel->GetInventory()->GetInventoryName()
                );
            }
        }
        if (Method == "DeleteReferenceOfByUserId") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Request);
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Inventory::Request::FDeleteReferenceOfByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FDeleteReferenceOfByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItemSet() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    RequestModel->GetInventoryName(),
                    "ItemSet"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheKey(
                    ResultModel->GetItemSet()->GetItemName(),
                    ResultModel->GetItemSet()->GetName()
                );
                Cache->Delete(Gs2::Inventory::Model::FItemSet::TypeName, ParentKey, Key);
            }
            if (ResultModel->GetItemModel() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryModelDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetInventoryName(),
                    "ItemModel"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FItemModelDomain::CreateCacheKey(
                    ResultModel->GetItemModel()->GetName()
                );
                Cache->Delete(Gs2::Inventory::Model::FItemModel::TypeName, ParentKey, Key);
            }
            if (ResultModel->GetInventory() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Inventory"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheKey(
                    ResultModel->GetInventory()->GetInventoryName()
                );
                Cache->Delete(Gs2::Inventory::Model::FInventory::TypeName, ParentKey, Key);
            }
        }
        if (Method == "AcquireSimpleItemsByUserId") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Request);
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Inventory::Request::FAcquireSimpleItemsByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FAcquireSimpleItemsByUserIdResult::FromJson(ResultModelJson);
            {
                for (auto Item : *ResultModel->GetItems())
                {
                    const auto ParentKey = Gs2::Inventory::Domain::Model::FSimpleInventoryDomain::CreateCacheParentKey(
                        RequestModel->GetNamespaceName(),
                        RequestModel->GetUserId(),
                        RequestModel->GetInventoryName(),
                        "SimpleItem"
                    );
                    const auto Key = Gs2::Inventory::Domain::Model::FSimpleItemDomain::CreateCacheKey(
                        Item->GetItemName()
                    );
                    Cache->Put(
                        Gs2::Inventory::Model::FSimpleItem::TypeName,
                        ParentKey,
                        Key,
                        Item,
                        FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                    );
                }
            }
        }
        if (Method == "AcquireBigItemByUserId") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Request);
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Inventory::Request::FAcquireBigItemByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FAcquireBigItemByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FBigInventoryDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    RequestModel->GetInventoryName(),
                    "BigItem"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FBigItemDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetItemName()
                );
                Cache->Put(
                    Gs2::Inventory::Model::FBigItem::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
    }

    void FGs2InventoryDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
        if (Method == "ConsumeItemSetByUserId") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Request);
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Inventory::Request::FConsumeItemSetByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FConsumeItemSetByUserIdResult::FromJson(ResultModelJson);
            {
                for (auto Item : *ResultModel->GetItems())
                {
                    const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheParentKey(
                        RequestModel->GetNamespaceName(),
                        RequestModel->GetUserId(),
                        RequestModel->GetInventoryName(),
                        "ItemSet"
                    );
                    const auto Key = Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheKey(
                        Item->GetItemName(),
                        Item->GetName()
                    );
                    if (Item->GetCount() == 0) {
                        Cache->Delete(
                            Gs2::Inventory::Model::FItemSet::TypeName,
                            ParentKey,
                            Key
                        );
                    }
                    else
                    {
                        Cache->Put(
                            Gs2::Inventory::Model::FItemSet::TypeName,
                            ParentKey,
                            Key,
                            Item,
                            Item->GetExpiresAt().IsSet() && *Item->GetExpiresAt() != 0 ? FDateTime::FromUnixTimestamp(*Item->GetExpiresAt()/1000) : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                        );
                    }
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
                        RequestModel->GetNamespaceName(),
                        RequestModel->GetUserId(),
                        RequestModel->GetInventoryName(),
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
                    Cache->Put(
                        Gs2::Inventory::Model::FItemSetEntry::TypeName,
                        ParentKey,
                        Key,
                        MakeShared<Gs2::Inventory::Model::FItemSetEntry>(*Group.Value),
                        FDateTime::FromUnixTimestamp(ExpiresAt / 1000)
                    );
                }
            }
            if (ResultModel->GetItemModel() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryModelDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetInventoryName(),
                    "ItemModel"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FItemModelDomain::CreateCacheKey(
                    ResultModel->GetItemModel()->GetName()
                );
                Cache->Put(
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
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Inventory"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheKey(
                    ResultModel->GetInventory()->GetInventoryName()
                );
                TSharedPtr<Gs2::Inventory::Model::FInventory> Item;
                auto bCacheHit = Cache->TryGet<Gs2::Inventory::Model::FInventory>(
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
                    Cache->Put(
                        Gs2::Inventory::Model::FInventory::TypeName,
                        ParentKey,
                        Key,
                        ResultModel->GetInventory(),
                        FDateTime::FromUnixTimestamp(ExpiresAt / 1000)
                    );
                }
            }
        }
        if (Method == "VerifyItemSetByUserId") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Request);
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Inventory::Request::FVerifyItemSetByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FVerifyItemSetByUserIdResult::FromJson(ResultModelJson);
            
        }
        if (Method == "VerifyReferenceOfByUserId") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Request);
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Inventory::Request::FVerifyReferenceOfByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FVerifyReferenceOfByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItemSet() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    RequestModel->GetInventoryName(),
                    "ItemSet"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheKey(
                    ResultModel->GetItemSet()->GetItemName(),
                    ResultModel->GetItemSet()->GetName()
                );
                Cache->Put(
                    Gs2::Inventory::Model::FItemSet::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItemSet(),
                    ResultModel->GetItemSet()->GetExpiresAt().IsSet() && *ResultModel->GetItemSet()->GetExpiresAt() != 0 ? FDateTime::FromUnixTimestamp(*ResultModel->GetItemSet()->GetExpiresAt() / 1000) : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetItemModel() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryModelDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetInventoryName(),
                    "ItemModel"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FItemModelDomain::CreateCacheKey(
                    ResultModel->GetItemModel()->GetName()
                );
                Cache->Put(
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
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Inventory"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheKey(
                    ResultModel->GetInventory()->GetInventoryName()
                );
            }
        }
        if (Method == "ConsumeSimpleItemsByUserId") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Request);
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Inventory::Request::FConsumeSimpleItemsByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FConsumeSimpleItemsByUserIdResult::FromJson(ResultModelJson);
            {
                for (auto Item : *ResultModel->GetItems())
                {
                    const auto ParentKey = Gs2::Inventory::Domain::Model::FSimpleInventoryDomain::CreateCacheParentKey(
                        RequestModel->GetNamespaceName(),
                        RequestModel->GetUserId(),
                        RequestModel->GetInventoryName(),
                        "SimpleItem"
                    );
                    const auto Key = Gs2::Inventory::Domain::Model::FSimpleItemDomain::CreateCacheKey(
                        Item->GetItemName()
                    );
                    Cache->Put(
                        Gs2::Inventory::Model::FSimpleItem::TypeName,
                        ParentKey,
                        Key,
                        Item,
                        FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                    );
                }
            }
        }
        if (Method == "VerifySimpleItemByUserId") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Request);
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Inventory::Request::FVerifySimpleItemByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FVerifySimpleItemByUserIdResult::FromJson(ResultModelJson);
            
        }
        if (Method == "ConsumeBigItemByUserId") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Request);
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Inventory::Request::FConsumeBigItemByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FConsumeBigItemByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FBigInventoryDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    RequestModel->GetInventoryName(),
                    "BigItem"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FBigItemDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetItemName()
                );
                Cache->Put(
                    Gs2::Inventory::Model::FBigItem::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "VerifyBigItemByUserId") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Request);
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Inventory::Request::FVerifyBigItemByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FVerifyBigItemByUserIdResult::FromJson(ResultModelJson);
            
        }
    }

    void FGs2InventoryDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result
    ) {
        if (Method == "add_capacity_by_user_id") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (!Job->GetArgs().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Job->GetArgs());
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (!Result->GetResult().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Result->GetResult());
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Inventory::Request::FAddCapacityByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FAddCapacityByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Inventory"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetInventoryName()
                );
                Cache->Put(
                    Gs2::Inventory::Model::FInventory::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "set_capacity_by_user_id") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (!Job->GetArgs().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Job->GetArgs());
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (!Result->GetResult().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Result->GetResult());
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Inventory::Request::FSetCapacityByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FSetCapacityByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Inventory"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetInventoryName()
                );
                Cache->Put(
                    Gs2::Inventory::Model::FInventory::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "acquire_item_set_by_user_id") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (!Job->GetArgs().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Job->GetArgs());
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (!Result->GetResult().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Result->GetResult());
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Inventory::Request::FAcquireItemSetByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FAcquireItemSetByUserIdResult::FromJson(ResultModelJson);
            {
                for (auto Item : *ResultModel->GetItems())
                {
                    const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheParentKey(
                        RequestModel->GetNamespaceName(),
                        RequestModel->GetUserId(),
                        RequestModel->GetInventoryName(),
                        "ItemSet"
                    );
                    const auto Key = Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheKey(
                        Item->GetItemName(),
                        Item->GetName()
                    );
                    if (Item->GetCount() == 0) {
                        Cache->Delete(
                            Gs2::Inventory::Model::FItemSet::TypeName,
                            ParentKey,
                            Key
                        );
                    }
                    else
                    {
                        Cache->Put(
                            Gs2::Inventory::Model::FItemSet::TypeName,
                            ParentKey,
                            Key,
                            Item,
                            Item->GetExpiresAt().IsSet() && *Item->GetExpiresAt() != 0 ? FDateTime::FromUnixTimestamp(*Item->GetExpiresAt()/1000) : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                        );
                    }
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
                        RequestModel->GetNamespaceName(),
                        RequestModel->GetUserId(),
                        RequestModel->GetInventoryName(),
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
                    Cache->Put(
                        Gs2::Inventory::Model::FItemSetEntry::TypeName,
                        ParentKey,
                        Key,
                        MakeShared<Gs2::Inventory::Model::FItemSetEntry>(*Group.Value),
                        FDateTime::FromUnixTimestamp(ExpiresAt / 1000)
                    );
                }
            }
            if (ResultModel->GetItemModel() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryModelDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetInventoryName(),
                    "ItemModel"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FItemModelDomain::CreateCacheKey(
                    ResultModel->GetItemModel()->GetName()
                );
                Cache->Put(
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
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Inventory"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheKey(
                    ResultModel->GetInventory()->GetInventoryName()
                );
                TSharedPtr<Gs2::Inventory::Model::FInventory> Item;
                auto bCacheHit = Cache->TryGet<Gs2::Inventory::Model::FInventory>(
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
                    Cache->Put(
                        Gs2::Inventory::Model::FInventory::TypeName,
                        ParentKey,
                        Key,
                        ResultModel->GetInventory(),
                        FDateTime::FromUnixTimestamp(ExpiresAt / 1000)
                    );
                }
            }
        }
        if (Method == "add_reference_of_by_user_id") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (!Job->GetArgs().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Job->GetArgs());
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (!Result->GetResult().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Result->GetResult());
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Inventory::Request::FAddReferenceOfByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FAddReferenceOfByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItemSet() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    RequestModel->GetInventoryName(),
                    "ItemSet"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheKey(
                    ResultModel->GetItemSet()->GetItemName(),
                    ResultModel->GetItemSet()->GetName()
                );
                Cache->Put(
                    Gs2::Inventory::Model::FItemSet::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItemSet(),
                    ResultModel->GetItemSet()->GetExpiresAt().IsSet() && *ResultModel->GetItemSet()->GetExpiresAt() != 0 ? FDateTime::FromUnixTimestamp(*ResultModel->GetItemSet()->GetExpiresAt() / 1000) : FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetItemModel() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryModelDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetInventoryName(),
                    "ItemModel"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FItemModelDomain::CreateCacheKey(
                    ResultModel->GetItemModel()->GetName()
                );
                Cache->Put(
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
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Inventory"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheKey(
                    ResultModel->GetInventory()->GetInventoryName()
                );
            }
        }
        if (Method == "delete_reference_of_by_user_id") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (!Job->GetArgs().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Job->GetArgs());
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (!Result->GetResult().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Result->GetResult());
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Inventory::Request::FDeleteReferenceOfByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FDeleteReferenceOfByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItemSet() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    RequestModel->GetInventoryName(),
                    "ItemSet"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheKey(
                    ResultModel->GetItemSet()->GetItemName(),
                    ResultModel->GetItemSet()->GetName()
                );
                Cache->Delete(Gs2::Inventory::Model::FItemSet::TypeName, ParentKey, Key);
            }
            if (ResultModel->GetItemModel() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryModelDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetInventoryName(),
                    "ItemModel"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FItemModelDomain::CreateCacheKey(
                    ResultModel->GetItemModel()->GetName()
                );
                Cache->Delete(Gs2::Inventory::Model::FItemModel::TypeName, ParentKey, Key);
            }
            if (ResultModel->GetInventory() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Inventory"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheKey(
                    ResultModel->GetInventory()->GetInventoryName()
                );
                Cache->Delete(Gs2::Inventory::Model::FInventory::TypeName, ParentKey, Key);
            }
        }
        if (Method == "acquire_simple_items_by_user_id") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (!Job->GetArgs().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Job->GetArgs());
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (!Result->GetResult().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Result->GetResult());
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Inventory::Request::FAcquireSimpleItemsByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FAcquireSimpleItemsByUserIdResult::FromJson(ResultModelJson);
            {
                for (auto Item : *ResultModel->GetItems())
                {
                    const auto ParentKey = Gs2::Inventory::Domain::Model::FSimpleInventoryDomain::CreateCacheParentKey(
                        RequestModel->GetNamespaceName(),
                        RequestModel->GetUserId(),
                        RequestModel->GetInventoryName(),
                        "SimpleItem"
                    );
                    const auto Key = Gs2::Inventory::Domain::Model::FSimpleItemDomain::CreateCacheKey(
                        Item->GetItemName()
                    );
                    Cache->Put(
                        Gs2::Inventory::Model::FSimpleItem::TypeName,
                        ParentKey,
                        Key,
                        Item,
                        FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                    );
                }
            }
        }
        if (Method == "acquire_big_item_by_user_id") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (!Job->GetArgs().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Job->GetArgs());
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (!Result->GetResult().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Result->GetResult());
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Inventory::Request::FAcquireBigItemByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Inventory::Result::FAcquireBigItemByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FBigInventoryDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    RequestModel->GetInventoryName(),
                    "BigItem"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FBigItemDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetItemName()
                );
                Cache->Put(
                    Gs2::Inventory::Model::FBigItem::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
    }

    void FGs2InventoryDomain::HandleNotification(
        const FString Action,
        const FString Payload
    ) {
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

