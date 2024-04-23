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

#include "Inventory/Domain/Model/ReferenceOfAccessToken.h"
#include "Inventory/Domain/Model/ReferenceOf.h"
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
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Inventory::Domain::Model
{

    FReferenceOfAccessTokenDomain::FReferenceOfAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> InventoryName,
        const TOptional<FString> ItemName,
        const TOptional<FString> ItemSetName,
        const TOptional<FString> ReferenceOf
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
        ReferenceOf(ReferenceOf),
        ParentKey(Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            InventoryName,
            ItemName,
            ItemSetName,
            "ReferenceOf"
        ))
    {
    }

    FReferenceOfAccessTokenDomain::FReferenceOfAccessTokenDomain(
        const FReferenceOfAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        InventoryName(From.InventoryName),
        ItemName(From.ItemName),
        ItemSetName(From.ItemSetName),
        ReferenceOf(From.ReferenceOf),
        ParentKey(From.ParentKey)
    {

    }

    FReferenceOfAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FReferenceOfAccessTokenDomain>& Self,
        const Request::FGetReferenceOfRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FReferenceOfAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FReferenceOfAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<FString>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithInventoryName(Self->InventoryName)
            ->WithItemName(Self->ItemName)
            ->WithItemSetName(Self->ItemSetName)
            ->WithReferenceOf(Self->ReferenceOf);
        const auto Future = Self->Client->GetReferenceOf(
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
                Self->Gs2->Cache->Put(
                    Gs2::Inventory::Model::FInventory::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetInventory(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = MakeShared<FString>(*ResultModel->GetItem());
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReferenceOfAccessTokenDomain::FGetTask>> FReferenceOfAccessTokenDomain::Get(
        Request::FGetReferenceOfRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FReferenceOfAccessTokenDomain::FVerifyTask::FVerifyTask(
        const TSharedPtr<FReferenceOfAccessTokenDomain>& Self,
        const Request::FVerifyReferenceOfRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FReferenceOfAccessTokenDomain::FVerifyTask::FVerifyTask(
        const FVerifyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FReferenceOfAccessTokenDomain::FVerifyTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FReferenceOfAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithInventoryName(Self->InventoryName)
            ->WithItemName(Self->ItemName)
            ->WithItemSetName(Self->ItemSetName)
            ->WithReferenceOf(Self->ReferenceOf);
        const auto Future = Self->Client->VerifyReferenceOf(
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
                Self->Gs2->Cache->Put(
                    Gs2::Inventory::Model::FInventory::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetInventory(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
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

    TSharedPtr<FAsyncTask<FReferenceOfAccessTokenDomain::FVerifyTask>> FReferenceOfAccessTokenDomain::Verify(
        Request::FVerifyReferenceOfRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyTask>>(this->AsShared(), Request);
    }

    FReferenceOfAccessTokenDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FReferenceOfAccessTokenDomain>& Self,
        const Request::FDeleteReferenceOfRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FReferenceOfAccessTokenDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FReferenceOfAccessTokenDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Domain::Model::FReferenceOfAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithInventoryName(Self->InventoryName)
            ->WithItemName(Self->ItemName)
            ->WithItemSetName(Self->ItemSetName)
            ->WithReferenceOf(Self->ReferenceOf);
        const auto Future = Self->Client->DeleteReferenceOf(
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
                Self->Gs2->Cache->Delete(Gs2::Inventory::Model::FItemSet::TypeName, ParentKey, Key);
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
                    Self->UserId(),
                    "Inventory"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FInventoryDomain::CreateCacheKey(
                    ResultModel->GetInventory()->GetInventoryName()
                );
                Self->Gs2->Cache->Delete(Gs2::Inventory::Model::FInventory::TypeName, ParentKey, Key);
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

    TSharedPtr<FAsyncTask<FReferenceOfAccessTokenDomain::FDeleteTask>> FReferenceOfAccessTokenDomain::Delete(
        Request::FDeleteReferenceOfRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FReferenceOfAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> InventoryName,
        TOptional<FString> ItemName,
        TOptional<FString> ItemSetName,
        TOptional<FString> ReferenceOf,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (InventoryName.IsSet() ? *InventoryName : "null") + ":" +
            (ItemName.IsSet() ? *ItemName : "null") + ":" +
            (ItemSetName.IsSet() ? *ItemSetName : "null") + ":" +
            (ReferenceOf.IsSet() ? *ReferenceOf : "null") + ":" +
            ChildType;
    }

    FString FReferenceOfAccessTokenDomain::CreateCacheKey(
        TOptional<FString> ReferenceOf
    )
    {
        return FString("") +
            (ReferenceOf.IsSet() ? *ReferenceOf : "null");
    }

    FReferenceOfAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FReferenceOfAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FReferenceOfAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FReferenceOfAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<FString>> Result
    )
    {
        const auto ParentKey = Gs2::Inventory::Domain::Model::FItemSetDomain::CreateCacheParentKey(
            Self->NamespaceName,
            Self->UserId(),
            Self->InventoryName,
            Self->ItemName,
            Self->ItemSetName,
            "ReferenceOf"
        );
        // ReSharper disable once CppLocalVariableMayBeConst
        Gs2::Inventory::Model::FReferenceOfPtr Value;
        const auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Inventory::Model::FReferenceOf>(
            ParentKey,
            Gs2::Inventory::Domain::Model::FReferenceOfDomain::CreateCacheKey(
                Self->ReferenceOf
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Inventory::Request::FGetReferenceOfRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Inventory::Domain::Model::FReferenceOfDomain::CreateCacheKey(
                    Self->ReferenceOf
                );
                Self->Gs2->Cache->Put(
                    Gs2::Inventory::Model::FReferenceOf::TypeName,
                    ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "referenceOf")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Inventory::Model::FReferenceOf>(
                ParentKey,
                Gs2::Inventory::Domain::Model::FReferenceOfDomain::CreateCacheKey(
                    Self->ReferenceOf
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        if (Value.IsValid())
        {
            *Result = MakeShared<FString>(*Value->GetName());
        }

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReferenceOfAccessTokenDomain::FModelTask>> FReferenceOfAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FReferenceOfAccessTokenDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

