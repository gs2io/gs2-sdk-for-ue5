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

#include "Inventory/Domain/SpeculativeExecutor/Acquire/AcquireItemSetWithGradeByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Auth/Model/AccessToken.h"
#include "Inventory/Model/Cache/Inventory.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace
{
    FString InventorySnapshot(const Gs2::Inventory::Model::FInventoryPtr& Item)
    {
        FString Value;
        auto Writer = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Value);
        FJsonSerializer::Serialize(Item->ToJson().ToSharedRef(), Writer);
        return Value;
    }
}

namespace Gs2::Inventory::Domain::SpeculativeExecutor
{

    FString FAcquireItemSetWithGradeByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Inventory:AcquireItemSetWithGradeByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FAcquireItemSetWithGradeByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FAcquireItemSetWithGradeByUserIdRequestPtr& Request,
        Gs2::Inventory::Model::FItemSetPtr Item
    )
    {
        UE_LOG(Gs2Log, Warning, TEXT("Speculative execution not supported on this action: %s"), ToCStr(Action()))
        return nullptr;
    }

    FAcquireItemSetWithGradeByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FAcquireItemSetWithGradeByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FAcquireItemSetWithGradeByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FAcquireItemSetWithGradeByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
        if (AccessToken.IsValid()) Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::Inventory::Request::FAcquireItemSetWithGradeByUserIdRequestPtr Prepared = nullptr;
        if (Request.IsValid()) Prepared = MakeShared<Gs2::Inventory::Request::FAcquireItemSetWithGradeByUserIdRequest>(*Request);
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Token.IsValid() ||
            !Token->GetUserId().IsSet() || Token->GetUserId().Get(FString()).IsEmpty() || !Prepared.IsValid()) return nullptr;
        if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}")) Prepared->WithUserId(Token->GetUserId());
        if (!Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != Token->GetUserId().Get(FString())) return nullptr;
        const auto NamespaceName = Prepared->GetNamespaceName();
        const auto InventoryName = Prepared->GetInventoryName();
        const auto UserId = Token->GetUserId();
        const auto TimeOffset = Token->GetTimeOffset();
        const auto ExpectedId = FString::Printf(TEXT("grn:gs2:%s:%s:inventory:%s:user:%s:inventory:%s"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName.Get(FString()), *UserId.Get(FString()), *InventoryName.Get(FString()));
        Gs2::Inventory::Model::FInventoryPtr Item;
        if (!Gs2::Inventory::Model::Cache::FInventoryCache::TryGet(Domain->Cache, NamespaceName, UserId.Get(FString()), InventoryName, TimeOffset, &Item) ||
            !Item.IsValid() || Item->GetInventoryId().Get(FString()) != ExpectedId || Item->GetUserId().Get(FString()) != UserId.Get(FString()) ||
            Item->GetInventoryName().Get(FString()) != InventoryName.Get(FString()) || !Item->GetCurrentInventoryCapacityUsage().IsSet() ||
            !Item->GetCurrentInventoryMaxCapacity().IsSet() || Item->GetCurrentInventoryCapacityUsage().Get(0) >= Item->GetCurrentInventoryMaxCapacity().Get(0) ||
            !Item->GetRevision().IsSet() || Item->GetRevision().Get(0) < 0) return nullptr;
        const auto Snapshot = InventorySnapshot(Item);
        const int64 UpdatedAt = static_cast<int64>(FDateTime::UtcNow().ToUnixTimestampDecimal() * 1000.0) + static_cast<int64>(TimeOffset.Get(0)) * 1000;
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(MakeShared<TFunction<void()>>(
            [DomainCopy = Domain, NamespaceName, InventoryName, UserId = UserId.Get(FString()), TimeOffset, ExpectedId, Snapshot, UpdatedAt]()
        {
            Gs2::Inventory::Model::FInventoryPtr Live;
            if (!Gs2::Inventory::Model::Cache::FInventoryCache::TryGet(DomainCopy->Cache, NamespaceName, UserId, InventoryName, TimeOffset, &Live) ||
                !Live.IsValid() || Live->GetInventoryId().Get(FString()) != ExpectedId || Live->GetUserId().Get(FString()) != UserId ||
                Live->GetInventoryName().Get(FString()) != InventoryName || !Live->GetCurrentInventoryCapacityUsage().IsSet() ||
                !Live->GetCurrentInventoryMaxCapacity().IsSet() || Live->GetCurrentInventoryCapacityUsage().Get(0) >= Live->GetCurrentInventoryMaxCapacity().Get(0) ||
                !Live->GetRevision().IsSet() || Live->GetRevision().Get(0) < 0 ||
                (Live->GetRevision().Get(0) > 0 && InventorySnapshot(Live) != Snapshot)) return;
            const int64 Usage = static_cast<int64>(Live->GetCurrentInventoryCapacityUsage().Get(0)) + 1;
            if (Usage < TNumericLimits<int32>::Min() || Usage > TNumericLimits<int32>::Max()) return;
            auto Changed = MakeShared<Gs2::Inventory::Model::FInventory>(*Live);
            Changed->WithCurrentInventoryCapacityUsage(static_cast<int32>(Usage))->WithUpdatedAt(UpdatedAt)->WithRevision(0);
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

    TSharedPtr<FAsyncTask<FAcquireItemSetWithGradeByUserIdSpeculativeExecutor::FCommitTask>> FAcquireItemSetWithGradeByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FAcquireItemSetWithGradeByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Inventory::Request::FAcquireItemSetWithGradeByUserIdRequestPtr FAcquireItemSetWithGradeByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inventory::Request::FAcquireItemSetWithGradeByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Inventory::Request::FAcquireItemSetWithGradeByUserIdRequestPtr FAcquireItemSetWithGradeByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inventory::Request::FAcquireItemSetWithGradeByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
