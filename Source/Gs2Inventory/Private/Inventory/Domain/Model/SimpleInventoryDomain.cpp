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

#include "Inventory/Domain/Model/SimpleInventory.h"
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
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Inventory::Domain::Model
{

    FSimpleInventoryDomain::FSimpleInventoryDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> InventoryName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Inventory::FGs2InventoryRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        InventoryName(InventoryName),
        ParentKey(Gs2::Inventory::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "SimpleInventory"
        ))
    {
    }

    FSimpleInventoryDomain::FSimpleInventoryDomain(
        const FSimpleInventoryDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        InventoryName(From.InventoryName),
        ParentKey(From.ParentKey)
    {

    }

    FSimpleInventoryDomain::FAcquireSimpleItemsTask::FAcquireSimpleItemsTask(
        const TSharedPtr<FSimpleInventoryDomain>& Self,
        const Request::FAcquireSimpleItemsByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSimpleInventoryDomain::FAcquireSimpleItemsTask::FAcquireSimpleItemsTask(
        const FAcquireSimpleItemsTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSimpleInventoryDomain::FAcquireSimpleItemsTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Inventory::Domain::Model::FSimpleItemDomain>>>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithInventoryName(Self->InventoryName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->AcquireSimpleItemsByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::Inventory::Domain::Model::FSimpleItemDomain>>>();
        for (auto i=0; i<ResultModel->GetItems()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::Inventory::Domain::Model::FSimpleItemDomain>(
                    Self->Gs2,
                    Self->Service,
                    Request->GetNamespaceName(),
                    (*ResultModel->GetItems())[i]->GetUserId(),
                    Request->GetInventoryName(),
                    (*ResultModel->GetItems())[i]->GetItemName()
                )
            );
            const auto ParentKey = Gs2::Inventory::Domain::Model::FSimpleInventoryDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->UserId,
                Self->InventoryName,
                "SimpleItem"
            );
            const auto Key = Gs2::Inventory::Domain::Model::FSimpleItemDomain::CreateCacheKey(
                (*ResultModel->GetItems())[i]->GetItemName()
            );
            Self->Gs2->Cache->Put(
                Gs2::Inventory::Model::FSimpleItem::TypeName,
                ParentKey,
                Key,
                (*ResultModel->GetItems())[i],
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSimpleInventoryDomain::FAcquireSimpleItemsTask>> FSimpleInventoryDomain::AcquireSimpleItems(
        Request::FAcquireSimpleItemsByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAcquireSimpleItemsTask>>(this->AsShared(), Request);
    }

    FSimpleInventoryDomain::FConsumeSimpleItemsTask::FConsumeSimpleItemsTask(
        const TSharedPtr<FSimpleInventoryDomain>& Self,
        const Request::FConsumeSimpleItemsByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSimpleInventoryDomain::FConsumeSimpleItemsTask::FConsumeSimpleItemsTask(
        const FConsumeSimpleItemsTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSimpleInventoryDomain::FConsumeSimpleItemsTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Inventory::Domain::Model::FSimpleItemDomain>>>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithInventoryName(Self->InventoryName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->ConsumeSimpleItemsByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::Inventory::Domain::Model::FSimpleItemDomain>>>();
        for (auto i=0; i<ResultModel->GetItems()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::Inventory::Domain::Model::FSimpleItemDomain>(
                    Self->Gs2,
                    Self->Service,
                    Request->GetNamespaceName(),
                    (*ResultModel->GetItems())[i]->GetUserId(),
                    Request->GetInventoryName(),
                    (*ResultModel->GetItems())[i]->GetItemName()
                )
            );
            const auto ParentKey = Gs2::Inventory::Domain::Model::FSimpleInventoryDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->UserId,
                Self->InventoryName,
                "SimpleItem"
            );
            const auto Key = Gs2::Inventory::Domain::Model::FSimpleItemDomain::CreateCacheKey(
                (*ResultModel->GetItems())[i]->GetItemName()
            );
            Self->Gs2->Cache->Put(
                Gs2::Inventory::Model::FSimpleItem::TypeName,
                ParentKey,
                Key,
                (*ResultModel->GetItems())[i],
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSimpleInventoryDomain::FConsumeSimpleItemsTask>> FSimpleInventoryDomain::ConsumeSimpleItems(
        Request::FConsumeSimpleItemsByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FConsumeSimpleItemsTask>>(this->AsShared(), Request);
    }

    FSimpleInventoryDomain::FSetSimpleItemsTask::FSetSimpleItemsTask(
        const TSharedPtr<FSimpleInventoryDomain>& Self,
        const Request::FSetSimpleItemsByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSimpleInventoryDomain::FSetSimpleItemsTask::FSetSimpleItemsTask(
        const FSetSimpleItemsTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSimpleInventoryDomain::FSetSimpleItemsTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Inventory::Domain::Model::FSimpleItemDomain>>>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithInventoryName(Self->InventoryName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->SetSimpleItemsByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::Inventory::Domain::Model::FSimpleItemDomain>>>();
        for (auto i=0; i<ResultModel->GetItems()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::Inventory::Domain::Model::FSimpleItemDomain>(
                    Self->Gs2,
                    Self->Service,
                    Request->GetNamespaceName(),
                    (*ResultModel->GetItems())[i]->GetUserId(),
                    Request->GetInventoryName(),
                    (*ResultModel->GetItems())[i]->GetItemName()
                )
            );
            const auto ParentKey = Gs2::Inventory::Domain::Model::FSimpleInventoryDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->UserId,
                Self->InventoryName,
                "SimpleItem"
            );
            const auto Key = Gs2::Inventory::Domain::Model::FSimpleItemDomain::CreateCacheKey(
                (*ResultModel->GetItems())[i]->GetItemName()
            );
            Self->Gs2->Cache->Put(
                Gs2::Inventory::Model::FSimpleItem::TypeName,
                ParentKey,
                Key,
                (*ResultModel->GetItems())[i],
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSimpleInventoryDomain::FSetSimpleItemsTask>> FSimpleInventoryDomain::SetSimpleItems(
        Request::FSetSimpleItemsByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSetSimpleItemsTask>>(this->AsShared(), Request);
    }

    FSimpleInventoryDomain::FDeleteSimpleItemsTask::FDeleteSimpleItemsTask(
        const TSharedPtr<FSimpleInventoryDomain>& Self,
        const Request::FDeleteSimpleItemsByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSimpleInventoryDomain::FDeleteSimpleItemsTask::FDeleteSimpleItemsTask(
        const FDeleteSimpleItemsTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSimpleInventoryDomain::FDeleteSimpleItemsTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FSimpleInventoryDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithInventoryName(Self->InventoryName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->DeleteSimpleItemsByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSimpleInventoryDomain::FDeleteSimpleItemsTask>> FSimpleInventoryDomain::DeleteSimpleItems(
        Request::FDeleteSimpleItemsByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteSimpleItemsTask>>(this->AsShared(), Request);
    }

    Gs2::Inventory::Domain::Iterator::FDescribeSimpleItemsByUserIdIteratorPtr FSimpleInventoryDomain::SimpleItems(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Inventory::Domain::Iterator::FDescribeSimpleItemsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            InventoryName,
            UserId,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FSimpleInventoryDomain::SubscribeSimpleItems(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Inventory::Model::FSimpleItem::TypeName,
            Gs2::Inventory::Domain::Model::FSimpleInventoryDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                InventoryName,
                "SimpleItem"
            ),
            Callback
        );
    }

    void FSimpleInventoryDomain::UnsubscribeSimpleItems(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Inventory::Model::FSimpleItem::TypeName,
            Gs2::Inventory::Domain::Model::FSimpleInventoryDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                InventoryName,
                "SimpleItem"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Inventory::Domain::Model::FSimpleItemDomain> FSimpleInventoryDomain::SimpleItem(
        const FString ItemName
    )
    {
        return MakeShared<Gs2::Inventory::Domain::Model::FSimpleItemDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            InventoryName,
            ItemName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ItemName)
        );
    }

    FString FSimpleInventoryDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> InventoryName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (InventoryName.IsSet() ? *InventoryName : "null") + ":" +
            ChildType;
    }

    FString FSimpleInventoryDomain::CreateCacheKey(
        TOptional<FString> InventoryName
    )
    {
        return FString("") +
            (InventoryName.IsSet() ? *InventoryName : "null");
    }

    FSimpleInventoryDomain::FModelTask::FModelTask(
        const TSharedPtr<FSimpleInventoryDomain> Self
    ): Self(Self)
    {

    }

    FSimpleInventoryDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSimpleInventoryDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FSimpleInventory>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Inventory::Model::FSimpleInventory> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Inventory::Model::FSimpleInventory>(
            Self->ParentKey,
            Gs2::Inventory::Domain::Model::FSimpleInventoryDomain::CreateCacheKey(
                Self->InventoryName
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSimpleInventoryDomain::FModelTask>> FSimpleInventoryDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSimpleInventoryDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FSimpleInventoryDomain::Subscribe(
        TFunction<void(Gs2::Inventory::Model::FSimpleInventoryPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Inventory::Model::FSimpleInventory::TypeName,
            ParentKey,
            Gs2::Inventory::Domain::Model::FSimpleInventoryDomain::CreateCacheKey(
                InventoryName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Inventory::Model::FSimpleInventory>(obj));
            }
        );
    }

    void FSimpleInventoryDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Inventory::Model::FSimpleInventory::TypeName,
            ParentKey,
            Gs2::Inventory::Domain::Model::FSimpleInventoryDomain::CreateCacheKey(
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

