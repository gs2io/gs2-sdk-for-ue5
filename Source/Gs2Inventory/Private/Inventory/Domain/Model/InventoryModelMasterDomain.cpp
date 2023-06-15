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

#include "Inventory/Domain/Model/InventoryModelMaster.h"
#include "Inventory/Domain/Model/Namespace.h"
#include "Inventory/Domain/Model/InventoryModelMaster.h"
#include "Inventory/Domain/Model/InventoryModel.h"
#include "Inventory/Domain/Model/ItemModelMaster.h"
#include "Inventory/Domain/Model/ItemModel.h"
#include "Inventory/Domain/Model/CurrentItemModelMaster.h"
#include "Inventory/Domain/Model/Inventory.h"
#include "Inventory/Domain/Model/InventoryAccessToken.h"
#include "Inventory/Domain/Model/ItemSet.h"
#include "Inventory/Domain/Model/ItemSetAccessToken.h"
#include "Inventory/Domain/Model/ReferenceOf.h"
#include "Inventory/Domain/Model/ReferenceOfAccessToken.h"
#include "Inventory/Domain/Model/User.h"
#include "Inventory/Domain/Model/UserAccessToken.h"
#include "Inventory/Domain/Model/ItemSetEntry.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Inventory::Domain::Model
{

    FInventoryModelMasterDomain::FInventoryModelMasterDomain(
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
            "InventoryModelMaster"
        ))
    {
    }

    FInventoryModelMasterDomain::FInventoryModelMasterDomain(
        const FInventoryModelMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FInventoryModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FInventoryModelMasterDomain> Self,
        const Request::FGetInventoryModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FInventoryModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FInventoryModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FInventoryModelMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithInventoryName(Self->InventoryName);
        const auto Future = Self->Client->GetInventoryModelMaster(
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
                    "InventoryModelMaster"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FInventoryModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Inventory::Model::FInventoryModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FInventoryModelMasterDomain::FGetTask>> FInventoryModelMasterDomain::Get(
        Request::FGetInventoryModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FInventoryModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FInventoryModelMasterDomain> Self,
        const Request::FUpdateInventoryModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FInventoryModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FInventoryModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FInventoryModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithInventoryName(Self->InventoryName);
        const auto Future = Self->Client->UpdateInventoryModelMaster(
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
                    "InventoryModelMaster"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FInventoryModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Inventory::Model::FInventoryModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FInventoryModelMasterDomain::FUpdateTask>> FInventoryModelMasterDomain::Update(
        Request::FUpdateInventoryModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FInventoryModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FInventoryModelMasterDomain> Self,
        const Request::FDeleteInventoryModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FInventoryModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FInventoryModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FInventoryModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithInventoryName(Self->InventoryName);
        const auto Future = Self->Client->DeleteInventoryModelMaster(
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
                    "InventoryModelMaster"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FInventoryModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete(Gs2::Inventory::Model::FInventoryModelMaster::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FInventoryModelMasterDomain::FDeleteTask>> FInventoryModelMasterDomain::Delete(
        Request::FDeleteInventoryModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FInventoryModelMasterDomain::FCreateItemModelMasterTask::FCreateItemModelMasterTask(
        const TSharedPtr<FInventoryModelMasterDomain> Self,
        const Request::FCreateItemModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FInventoryModelMasterDomain::FCreateItemModelMasterTask::FCreateItemModelMasterTask(
        const FCreateItemModelMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FInventoryModelMasterDomain::FCreateItemModelMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FItemModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithInventoryName(Self->InventoryName);
        const auto Future = Self->Client->CreateItemModelMaster(
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
                const auto ParentKey = Gs2::Inventory::Domain::Model::FInventoryModelMasterDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->InventoryName,
                    "ItemModelMaster"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FItemModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Inventory::Model::FItemModelMaster::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Inventory::Domain::Model::FItemModelMasterDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetInventoryName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FInventoryModelMasterDomain::FCreateItemModelMasterTask>> FInventoryModelMasterDomain::CreateItemModelMaster(
        Request::FCreateItemModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateItemModelMasterTask>>(this->AsShared(), Request);
    }

    Gs2::Inventory::Domain::Iterator::FDescribeItemModelMastersIteratorPtr FInventoryModelMasterDomain::ItemModelMasters(
    ) const
    {
        return MakeShared<Gs2::Inventory::Domain::Iterator::FDescribeItemModelMastersIterator>(
            Cache,
            Client,
            NamespaceName,
            InventoryName
        );
    }

    TSharedPtr<Gs2::Inventory::Domain::Model::FItemModelMasterDomain> FInventoryModelMasterDomain::ItemModelMaster(
        const FString ItemName
    ) const
    {
        return MakeShared<Gs2::Inventory::Domain::Model::FItemModelMasterDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            InventoryName,
            ItemName
        );
    }

    FString FInventoryModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> InventoryName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (InventoryName.IsSet() ? *InventoryName : "null") + ":" +
            ChildType;
    }

    FString FInventoryModelMasterDomain::CreateCacheKey(
        TOptional<FString> InventoryName
    )
    {
        return FString() +
            (InventoryName.IsSet() ? *InventoryName : "null");
    }

    FInventoryModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FInventoryModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FInventoryModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FInventoryModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FInventoryModelMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Inventory::Model::FInventoryModelMaster> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Inventory::Model::FInventoryModelMaster>(
            Self->ParentKey,
            Gs2::Inventory::Domain::Model::FInventoryModelMasterDomain::CreateCacheKey(
                Self->InventoryName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Inventory::Request::FGetInventoryModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Inventory::Domain::Model::FInventoryModelMasterDomain::CreateCacheKey(
                    Self->InventoryName
                );
                Self->Cache->Put(
                    Gs2::Inventory::Model::FInventoryModelMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "inventoryModelMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Inventory::Model::FInventoryModelMaster>(
                Self->ParentKey,
                Gs2::Inventory::Domain::Model::FInventoryModelMasterDomain::CreateCacheKey(
                    Self->InventoryName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FInventoryModelMasterDomain::FModelTask>> FInventoryModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FInventoryModelMasterDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

