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

#include "Inventory/Domain/SpeculativeExecutor/Acquire/AddCapacityByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Auth/Model/AccessToken.h"
#include "Inventory/Domain/Gs2Inventory.h"
#include "Inventory/Model/Cache/Inventory.h"
#include "Inventory/Model/Cache/InventoryModel.h"

namespace Gs2::Inventory::Domain::SpeculativeExecutor
{

    FString FAddCapacityByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Inventory:AddCapacityByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FAddCapacityByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FAddCapacityByUserIdRequestPtr& Request,
        Gs2::Inventory::Model::FInventoryPtr Item
    )
    {
        Item->WithCurrentInventoryMaxCapacity(*Item->GetCurrentInventoryMaxCapacity() + *Request->GetAddCapacityValue());
        return nullptr;
    }

    FAddCapacityByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FAddCapacityByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FAddCapacityByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FAddCapacityByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
        if (AccessToken.IsValid()) Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::Inventory::Request::FAddCapacityByUserIdRequestPtr Prepared = nullptr;
        if (Request.IsValid()) Prepared = MakeShared<Gs2::Inventory::Request::FAddCapacityByUserIdRequest>(*Request);
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Token.IsValid() ||
            !Token->GetUserId().IsSet() || Token->GetUserId().Get(FString()).IsEmpty() || !Prepared.IsValid()) return nullptr;
        if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}")) Prepared->WithUserId(Token->GetUserId());
        if (!Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != Token->GetUserId().Get(FString()) ||
            !Prepared->GetNamespaceName().IsSet() || Prepared->GetNamespaceName().Get(FString()).IsEmpty() ||
            !Prepared->GetInventoryName().IsSet() || Prepared->GetInventoryName().Get(FString()).IsEmpty() ||
            !Prepared->GetAddCapacityValue().IsSet()) return nullptr;
        const auto UserId = Token->GetUserId().Get(FString());
        const auto TimeOffset = Token->GetTimeOffset();
        const auto NamespaceName = Prepared->GetNamespaceName().Get(FString());
        const auto InventoryName = Prepared->GetInventoryName().Get(FString());
        const auto ExpectedItemId = FString::Printf(TEXT("grn:gs2:%s:%s:inventory:%s:user:%s:inventory:%s"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName, *UserId, *InventoryName);
        const auto ExpectedModelId = FString::Printf(TEXT("grn:gs2:%s:%s:inventory:%s:model:%s"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName, *InventoryName);
        Gs2::Inventory::Model::FInventoryPtr Item;
        Gs2::Inventory::Model::FInventoryModelPtr ModelItem;
        const bool FoundItem = Gs2::Inventory::Model::Cache::FInventoryCache::TryGet(Domain->Cache, NamespaceName, UserId, InventoryName, TimeOffset, &Item);
        const bool FoundModel = Gs2::Inventory::Model::Cache::FInventoryModelCache::TryGet(Domain->Cache, NamespaceName, InventoryName, TOptional<int32>(), &ModelItem);
        if (!FoundItem || !FoundModel || !Item.IsValid() || !ModelItem.IsValid() ||
            Item->GetInventoryId().Get(FString()) != ExpectedItemId || Item->GetUserId().Get(FString()) != UserId ||
            Item->GetInventoryName().Get(FString()) != InventoryName || !Item->GetCurrentInventoryMaxCapacity().IsSet() ||
            ModelItem->GetInventoryModelId().Get(FString()) != ExpectedModelId || ModelItem->GetName().Get(FString()) != InventoryName ||
            !ModelItem->GetMaxCapacity().IsSet()) return nullptr;
        const auto PreparedRevision = Item->GetRevision();
        const auto PreparedMaxCapacity = ModelItem->GetMaxCapacity();
        const auto AddCapacity = Prepared->GetAddCapacityValue().Get(0);
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(MakeShared<TFunction<void()>>(
            [DomainCopy = Domain, NamespaceName, InventoryName, UserId, TimeOffset, ExpectedItemId, ExpectedModelId, PreparedRevision, PreparedMaxCapacity, AddCapacity]()
        {
            Gs2::Inventory::Model::FInventoryPtr LiveItem;
            Gs2::Inventory::Model::FInventoryModelPtr LiveModel;
            const bool FoundLiveItem = Gs2::Inventory::Model::Cache::FInventoryCache::TryGet(DomainCopy->Cache, NamespaceName, UserId, InventoryName, TimeOffset, &LiveItem);
            const bool FoundLiveModel = Gs2::Inventory::Model::Cache::FInventoryModelCache::TryGet(DomainCopy->Cache, NamespaceName, InventoryName, TOptional<int32>(), &LiveModel);
            if (!FoundLiveItem || !FoundLiveModel || !LiveItem.IsValid() || !LiveModel.IsValid() ||
                LiveItem->GetInventoryId().Get(FString()) != ExpectedItemId || LiveItem->GetUserId().Get(FString()) != UserId ||
                LiveItem->GetInventoryName().Get(FString()) != InventoryName || !LiveItem->GetCurrentInventoryMaxCapacity().IsSet() ||
                LiveModel->GetInventoryModelId().Get(FString()) != ExpectedModelId || LiveModel->GetName().Get(FString()) != InventoryName ||
                !LiveModel->GetMaxCapacity().IsSet() || LiveModel->GetMaxCapacity() != PreparedMaxCapacity ||
                (LiveItem->GetRevision().Get(0) > 0 && LiveItem->GetRevision() != PreparedRevision)) return;
            const int64 ChangedCapacity = FMath::Min<int64>(static_cast<int64>(LiveItem->GetCurrentInventoryMaxCapacity().Get(0)) + AddCapacity, LiveModel->GetMaxCapacity().Get(0));
            if (ChangedCapacity < TNumericLimits<int32>::Min() || ChangedCapacity > TNumericLimits<int32>::Max()) return;
            auto Changed = MakeShared<Gs2::Inventory::Model::FInventory>(*LiveItem);
            Changed->WithCurrentInventoryMaxCapacity(static_cast<int32>(ChangedCapacity))->WithRevision(0);
            DomainCopy->Cache->Put(
                Gs2::Inventory::Model::FInventory::TypeName,
                Gs2::Inventory::Model::Cache::FInventoryCache::CreateCacheParentKey(NamespaceName, UserId, TimeOffset),
                Gs2::Inventory::Model::Cache::FInventoryCache::CreateCacheKey(InventoryName),
                Changed,
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }));
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAddCapacityByUserIdSpeculativeExecutor::FCommitTask>> FAddCapacityByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FAddCapacityByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Inventory::Request::FAddCapacityByUserIdRequestPtr FAddCapacityByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inventory::Request::FAddCapacityByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (Request->GetAddCapacityValue().IsSet())
        {
            Request->WithAddCapacityValue(*Request->GetAddCapacityValue() * Rate);
        }
        return Request;
    }

    Gs2::Inventory::Request::FAddCapacityByUserIdRequestPtr FAddCapacityByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inventory::Request::FAddCapacityByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (Request->GetAddCapacityValue().IsSet())
        {
            Rate.Multiply(*Request->GetAddCapacityValue());
            Request->WithAddCapacityValue(Rate.ToInt());
        }
        return Request;
    }
}
