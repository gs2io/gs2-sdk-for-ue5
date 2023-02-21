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

#include "Inventory/Domain/Model/InventoryModel.h"
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

    FInventoryModelDomain::FInventoryModelDomain(
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
            "InventoryModel"
        ))
    {
    }

    FInventoryModelDomain::FInventoryModelDomain(
        const FInventoryModelDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FInventoryModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FInventoryModelDomain> Self,
        const Request::FGetInventoryModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FInventoryModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FInventoryModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FInventoryModel>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithInventoryName(Self->InventoryName);
        const auto Future = Self->Client->GetInventoryModel(
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
                    "InventoryModel"
                );
                const auto Key = Gs2::Inventory::Domain::Model::FInventoryModelDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put<Gs2::Inventory::Model::FInventoryModel>(
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

    TSharedPtr<FAsyncTask<FInventoryModelDomain::FGetTask>> FInventoryModelDomain::Get(
        Request::FGetInventoryModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    Gs2::Inventory::Domain::Iterator::FDescribeItemModelsIteratorPtr FInventoryModelDomain::ItemModels(
    ) const
    {
        return MakeShared<Gs2::Inventory::Domain::Iterator::FDescribeItemModelsIterator>(
            Cache,
            Client,
            NamespaceName,
            InventoryName
        );
    }

    TSharedPtr<Gs2::Inventory::Domain::Model::FItemModelDomain> FInventoryModelDomain::ItemModel(
        const FString ItemName
    ) const
    {
        return MakeShared<Gs2::Inventory::Domain::Model::FItemModelDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            InventoryName,
            ItemName
        );
    }

    FString FInventoryModelDomain::CreateCacheParentKey(
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

    FString FInventoryModelDomain::CreateCacheKey(
        TOptional<FString> InventoryName
    )
    {
        return FString() +
            (InventoryName.IsSet() ? *InventoryName : "null");
    }

    FInventoryModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FInventoryModelDomain> Self
    ): Self(Self)
    {

    }

    FInventoryModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FInventoryModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Inventory::Model::FInventoryModel>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Inventory::Model::FInventoryModel>(
            Self->ParentKey,
            Gs2::Inventory::Domain::Model::FInventoryModelDomain::CreateCacheKey(
                Self->InventoryName
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Inventory::Request::FGetInventoryModelRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "inventoryModel")
                    {
                        Self->Cache->Delete<Gs2::Inventory::Model::FInventoryModel>(
                            Self->ParentKey,
                            Gs2::Inventory::Domain::Model::FInventoryModelDomain::CreateCacheKey(
                                Self->InventoryName
                            )
                        );
                    }
                    else
                    {
                        return Future->GetTask().Error();
                    }
                }
                else
                {
                    return Future->GetTask().Error();
                }
            }
            Value = Self->Cache->Get<Gs2::Inventory::Model::FInventoryModel>(
                Self->ParentKey,
                Gs2::Inventory::Domain::Model::FInventoryModelDomain::CreateCacheKey(
                    Self->InventoryName
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FInventoryModelDomain::FModelTask>> FInventoryModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FInventoryModelDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

