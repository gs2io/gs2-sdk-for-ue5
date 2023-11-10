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

#include "Inventory/Domain/Model/SimpleInventoryModelMaster.h"
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
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Inventory::Domain::Model
{

    FSimpleInventoryModelMasterDomain::FSimpleInventoryModelMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> InventoryName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Inventory::FGs2InventoryRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        InventoryName(InventoryName),
        ParentKey(Gs2::Inventory::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "SimpleInventoryModelMaster"
        ))
    {
    }

    FSimpleInventoryModelMasterDomain::FSimpleInventoryModelMasterDomain(
        const FSimpleInventoryModelMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        InventoryName(From.InventoryName),
        ParentKey(From.ParentKey)
    {

    }

    FSimpleInventoryModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FSimpleInventoryModelMasterDomain>& Self,
        const Request::FGetSimpleInventoryModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSimpleInventoryModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSimpleInventoryModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FSimpleInventoryModelMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithInventoryName(Self->InventoryName);
        const auto Future = Self->Client->GetSimpleInventoryModelMaster(
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
                    "SimpleInventoryModelMaster"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FSimpleInventoryModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Inventory::Model::FSimpleInventoryModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FSimpleInventoryModelMasterDomain::FGetTask>> FSimpleInventoryModelMasterDomain::Get(
        Request::FGetSimpleInventoryModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FSimpleInventoryModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FSimpleInventoryModelMasterDomain>& Self,
        const Request::FUpdateSimpleInventoryModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSimpleInventoryModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSimpleInventoryModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FSimpleInventoryModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithInventoryName(Self->InventoryName);
        const auto Future = Self->Client->UpdateSimpleInventoryModelMaster(
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
                    "SimpleInventoryModelMaster"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FSimpleInventoryModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Inventory::Model::FSimpleInventoryModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FSimpleInventoryModelMasterDomain::FUpdateTask>> FSimpleInventoryModelMasterDomain::Update(
        Request::FUpdateSimpleInventoryModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FSimpleInventoryModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FSimpleInventoryModelMasterDomain>& Self,
        const Request::FDeleteSimpleInventoryModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSimpleInventoryModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSimpleInventoryModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FSimpleInventoryModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithInventoryName(Self->InventoryName);
        const auto Future = Self->Client->DeleteSimpleInventoryModelMaster(
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
                    "SimpleInventoryModelMaster"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FSimpleInventoryModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::Inventory::Model::FSimpleInventoryModelMaster::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSimpleInventoryModelMasterDomain::FDeleteTask>> FSimpleInventoryModelMasterDomain::Delete(
        Request::FDeleteSimpleInventoryModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FSimpleInventoryModelMasterDomain::FCreateSimpleItemModelMasterTask::FCreateSimpleItemModelMasterTask(
        const TSharedPtr<FSimpleInventoryModelMasterDomain>& Self,
        const Request::FCreateSimpleItemModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSimpleInventoryModelMasterDomain::FCreateSimpleItemModelMasterTask::FCreateSimpleItemModelMasterTask(
        const FCreateSimpleItemModelMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSimpleInventoryModelMasterDomain::FCreateSimpleItemModelMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FSimpleItemModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithInventoryName(Self->InventoryName);
        const auto Future = Self->Client->CreateSimpleItemModelMaster(
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
                const auto ParentKey = Gs2::Inventory::Domain::Model::FSimpleInventoryModelMasterDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->InventoryName,
                    "SimpleItemModelMaster"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FSimpleItemModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Inventory::Model::FSimpleItemModelMaster::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Inventory::Domain::Model::FSimpleItemModelMasterDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Request->GetInventoryName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSimpleInventoryModelMasterDomain::FCreateSimpleItemModelMasterTask>> FSimpleInventoryModelMasterDomain::CreateSimpleItemModelMaster(
        Request::FCreateSimpleItemModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateSimpleItemModelMasterTask>>(this->AsShared(), Request);
    }

    Gs2::Inventory::Domain::Iterator::FDescribeSimpleItemModelMastersIteratorPtr FSimpleInventoryModelMasterDomain::SimpleItemModelMasters(
    ) const
    {
        return MakeShared<Gs2::Inventory::Domain::Iterator::FDescribeSimpleItemModelMastersIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            InventoryName
        );
    }

    Gs2::Core::Domain::CallbackID FSimpleInventoryModelMasterDomain::SubscribeSimpleItemModelMasters(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Inventory::Model::FSimpleItemModelMaster::TypeName,
            Gs2::Inventory::Domain::Model::FSimpleInventoryModelMasterDomain::CreateCacheParentKey(
                NamespaceName,
                InventoryName,
                "SimpleItemModelMaster"
            ),
            Callback
        );
    }

    void FSimpleInventoryModelMasterDomain::UnsubscribeSimpleItemModelMasters(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Inventory::Model::FSimpleItemModelMaster::TypeName,
            Gs2::Inventory::Domain::Model::FSimpleInventoryModelMasterDomain::CreateCacheParentKey(
                NamespaceName,
                InventoryName,
                "SimpleItemModelMaster"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Inventory::Domain::Model::FSimpleItemModelMasterDomain> FSimpleInventoryModelMasterDomain::SimpleItemModelMaster(
        const FString ItemName
    )
    {
        return MakeShared<Gs2::Inventory::Domain::Model::FSimpleItemModelMasterDomain>(
            Gs2,
            Service,
            NamespaceName,
            InventoryName,
            ItemName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ItemName)
        );
    }

    FString FSimpleInventoryModelMasterDomain::CreateCacheParentKey(
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

    FString FSimpleInventoryModelMasterDomain::CreateCacheKey(
        TOptional<FString> InventoryName
    )
    {
        return FString("") +
            (InventoryName.IsSet() ? *InventoryName : "null");
    }

    FSimpleInventoryModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FSimpleInventoryModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FSimpleInventoryModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSimpleInventoryModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FSimpleInventoryModelMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Inventory::Model::FSimpleInventoryModelMaster> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Inventory::Model::FSimpleInventoryModelMaster>(
            Self->ParentKey,
            Gs2::Inventory::Domain::Model::FSimpleInventoryModelMasterDomain::CreateCacheKey(
                Self->InventoryName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Inventory::Request::FGetSimpleInventoryModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Inventory::Domain::Model::FSimpleInventoryModelMasterDomain::CreateCacheKey(
                    Self->InventoryName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Inventory::Model::FSimpleInventoryModelMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "simpleInventoryModelMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Inventory::Model::FSimpleInventoryModelMaster>(
                Self->ParentKey,
                Gs2::Inventory::Domain::Model::FSimpleInventoryModelMasterDomain::CreateCacheKey(
                    Self->InventoryName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSimpleInventoryModelMasterDomain::FModelTask>> FSimpleInventoryModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSimpleInventoryModelMasterDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FSimpleInventoryModelMasterDomain::Subscribe(
        TFunction<void(Gs2::Inventory::Model::FSimpleInventoryModelMasterPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Inventory::Model::FSimpleInventoryModelMaster::TypeName,
            ParentKey,
            Gs2::Inventory::Domain::Model::FSimpleInventoryModelMasterDomain::CreateCacheKey(
                InventoryName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Inventory::Model::FSimpleInventoryModelMaster>(obj));
            }
        );
    }

    void FSimpleInventoryModelMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Inventory::Model::FSimpleInventoryModelMaster::TypeName,
            ParentKey,
            Gs2::Inventory::Domain::Model::FSimpleInventoryModelMasterDomain::CreateCacheKey(
                InventoryName
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

