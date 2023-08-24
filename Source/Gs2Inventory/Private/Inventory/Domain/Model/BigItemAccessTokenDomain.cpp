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

#include "Inventory/Domain/Model/BigItemAccessToken.h"
#include "Inventory/Domain/Model/BigItem.h"
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

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Inventory::Domain::Model
{

    FBigItemAccessTokenDomain::FBigItemAccessTokenDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> InventoryName,
        const TOptional<FString> ItemName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Inventory::FGs2InventoryRestClient>(Session)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        InventoryName(InventoryName),
        ItemName(ItemName),
        ParentKey(Gs2::Inventory::Domain::Model::FBigInventoryDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            InventoryName,
            "BigItem"
        ))
    {
    }

    FBigItemAccessTokenDomain::FBigItemAccessTokenDomain(
        const FBigItemAccessTokenDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FBigItemAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FBigItemAccessTokenDomain> Self,
        const Request::FGetBigItemRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FBigItemAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FBigItemAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FBigItem>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithInventoryName(Self->InventoryName)
            ->WithItemName(Self->ItemName);
        const auto Future = Self->Client->GetBigItem(
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
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FBigInventoryDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    Self->InventoryName,
                    "BigItem"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FBigItemDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetItemName()
                );
                Self->Cache->Put(
                    Gs2::Inventory::Model::FBigItem::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetItemModel() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FBigInventoryModelDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->InventoryName,
                    "BigItemModel"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FBigItemModelDomain::CreateCacheKey(
                    ResultModel->GetItemModel()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Inventory::Model::FBigItemModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItemModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBigItemAccessTokenDomain::FGetTask>> FBigItemAccessTokenDomain::Get(
        Request::FGetBigItemRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FBigItemAccessTokenDomain::FConsumeTask::FConsumeTask(
        const TSharedPtr<FBigItemAccessTokenDomain> Self,
        const Request::FConsumeBigItemRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FBigItemAccessTokenDomain::FConsumeTask::FConsumeTask(
        const FConsumeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FBigItemAccessTokenDomain::FConsumeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FBigItemAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithInventoryName(Self->InventoryName)
            ->WithItemName(Self->ItemName);
        const auto Future = Self->Client->ConsumeBigItem(
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
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Inventory::Domain::Model::FBigInventoryDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    Self->InventoryName,
                    "BigItem"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FBigItemDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetItemName()
                );
                Self->Cache->Put(
                    Gs2::Inventory::Model::FBigItem::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBigItemAccessTokenDomain::FConsumeTask>> FBigItemAccessTokenDomain::Consume(
        Request::FConsumeBigItemRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FConsumeTask>>(this->AsShared(), Request);
    }

    FString FBigItemAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> InventoryName,
        TOptional<FString> ItemName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (InventoryName.IsSet() ? *InventoryName : "null") + ":" +
            (ItemName.IsSet() ? *ItemName : "null") + ":" +
            ChildType;
    }

    FString FBigItemAccessTokenDomain::CreateCacheKey(
        TOptional<FString> ItemName
    )
    {
        return FString() +
            (ItemName.IsSet() ? *ItemName : "null");
    }

    FBigItemAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FBigItemAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FBigItemAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FBigItemAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FBigItem>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Inventory::Model::FBigItem> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Inventory::Model::FBigItem>(
            Self->ParentKey,
            Gs2::Inventory::Domain::Model::FBigItemDomain::CreateCacheKey(
                Self->ItemName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Inventory::Request::FGetBigItemRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Inventory::Domain::Model::FBigItemDomain::CreateCacheKey(
                    Self->ItemName
                );
                Self->Cache->Put(
                    Gs2::Inventory::Model::FBigItem::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "bigItem")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Inventory::Model::FBigItem>(
                Self->ParentKey,
                Gs2::Inventory::Domain::Model::FBigItemDomain::CreateCacheKey(
                    Self->ItemName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBigItemAccessTokenDomain::FModelTask>> FBigItemAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FBigItemAccessTokenDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
