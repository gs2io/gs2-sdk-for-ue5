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

#include "Inventory/Domain/Model/BigInventoryModelMaster.h"
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

    FBigInventoryModelMasterDomain::FBigInventoryModelMasterDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> InventoryName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Inventory::FGs2InventoryRestClient>(Session)),
        NamespaceName(NamespaceName),
        InventoryName(InventoryName),
        ParentKey(Gs2::Inventory::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "BigInventoryModelMaster"
        ))
    {
    }

    FBigInventoryModelMasterDomain::FBigInventoryModelMasterDomain(
        const FBigInventoryModelMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        InventoryName(From.InventoryName),
        ParentKey(From.ParentKey)
    {

    }

    FBigInventoryModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FBigInventoryModelMasterDomain> Self,
        const Request::FGetBigInventoryModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FBigInventoryModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FBigInventoryModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FBigInventoryModelMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithInventoryName(Self->InventoryName);
        const auto Future = Self->Client->GetBigInventoryModelMaster(
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
                const auto ParentKey = Gs2::Inventory::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "BigInventoryModelMaster"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FBigInventoryModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Inventory::Model::FBigInventoryModelMaster::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBigInventoryModelMasterDomain::FGetTask>> FBigInventoryModelMasterDomain::Get(
        Request::FGetBigInventoryModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FBigInventoryModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FBigInventoryModelMasterDomain> Self,
        const Request::FUpdateBigInventoryModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FBigInventoryModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FBigInventoryModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FBigInventoryModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithInventoryName(Self->InventoryName);
        const auto Future = Self->Client->UpdateBigInventoryModelMaster(
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
                const auto ParentKey = Gs2::Inventory::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "BigInventoryModelMaster"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FBigInventoryModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Inventory::Model::FBigInventoryModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FBigInventoryModelMasterDomain::FUpdateTask>> FBigInventoryModelMasterDomain::Update(
        Request::FUpdateBigInventoryModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FBigInventoryModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FBigInventoryModelMasterDomain> Self,
        const Request::FDeleteBigInventoryModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FBigInventoryModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FBigInventoryModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FBigInventoryModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithInventoryName(Self->InventoryName);
        const auto Future = Self->Client->DeleteBigInventoryModelMaster(
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
                const auto ParentKey = Gs2::Inventory::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "BigInventoryModelMaster"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FBigInventoryModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete(Gs2::Inventory::Model::FBigInventoryModelMaster::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBigInventoryModelMasterDomain::FDeleteTask>> FBigInventoryModelMasterDomain::Delete(
        Request::FDeleteBigInventoryModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FBigInventoryModelMasterDomain::FCreateBigItemModelMasterTask::FCreateBigItemModelMasterTask(
        const TSharedPtr<FBigInventoryModelMasterDomain> Self,
        const Request::FCreateBigItemModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FBigInventoryModelMasterDomain::FCreateBigItemModelMasterTask::FCreateBigItemModelMasterTask(
        const FCreateBigItemModelMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FBigInventoryModelMasterDomain::FCreateBigItemModelMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FBigItemModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithInventoryName(Self->InventoryName);
        const auto Future = Self->Client->CreateBigItemModelMaster(
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
                const auto ParentKey = Gs2::Inventory::Domain::Model::FBigInventoryModelMasterDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->InventoryName,
                    "BigItemModelMaster"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FBigItemModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Inventory::Model::FBigItemModelMaster::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Inventory::Domain::Model::FBigItemModelMasterDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            Request->GetNamespaceName(),
            Request->GetInventoryName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBigInventoryModelMasterDomain::FCreateBigItemModelMasterTask>> FBigInventoryModelMasterDomain::CreateBigItemModelMaster(
        Request::FCreateBigItemModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateBigItemModelMasterTask>>(this->AsShared(), Request);
    }

    Gs2::Inventory::Domain::Iterator::FDescribeBigItemModelMastersIteratorPtr FBigInventoryModelMasterDomain::BigItemModelMasters(
    ) const
    {
        return MakeShared<Gs2::Inventory::Domain::Iterator::FDescribeBigItemModelMastersIterator>(
            Cache,
            Client,
            NamespaceName,
            InventoryName
        );
    }

    TSharedPtr<Gs2::Inventory::Domain::Model::FBigItemModelMasterDomain> FBigInventoryModelMasterDomain::BigItemModelMaster(
        const FString ItemName
    ) const
    {
        return MakeShared<Gs2::Inventory::Domain::Model::FBigItemModelMasterDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            InventoryName,
            ItemName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ItemName)
        );
    }

    FString FBigInventoryModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> InventoryName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (InventoryName.IsSet() ? *InventoryName : "null") + ":" +
            ChildType;
    }

    FString FBigInventoryModelMasterDomain::CreateCacheKey(
        TOptional<FString> InventoryName
    )
    {
        return FString("") +
            (InventoryName.IsSet() ? *InventoryName : "null");
    }

    FBigInventoryModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FBigInventoryModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FBigInventoryModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FBigInventoryModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FBigInventoryModelMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Inventory::Model::FBigInventoryModelMaster> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Inventory::Model::FBigInventoryModelMaster>(
            Self->ParentKey,
            Gs2::Inventory::Domain::Model::FBigInventoryModelMasterDomain::CreateCacheKey(
                Self->InventoryName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Inventory::Request::FGetBigInventoryModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Inventory::Domain::Model::FBigInventoryModelMasterDomain::CreateCacheKey(
                    Self->InventoryName
                );
                Self->Cache->Put(
                    Gs2::Inventory::Model::FBigInventoryModelMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "bigInventoryModelMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Inventory::Model::FBigInventoryModelMaster>(
                Self->ParentKey,
                Gs2::Inventory::Domain::Model::FBigInventoryModelMasterDomain::CreateCacheKey(
                    Self->InventoryName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBigInventoryModelMasterDomain::FModelTask>> FBigInventoryModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FBigInventoryModelMasterDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

