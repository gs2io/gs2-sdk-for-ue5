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

#include "Inventory/Domain/SpeculativeExecutor/Acquire/AddReferenceOfByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Inventory/Model/Cache/ItemSet.h"

namespace Gs2::Inventory::Domain::SpeculativeExecutor
{
namespace
{
    FString AddReferenceOfExpectedItemSetId(
        const FString& Region,
        const FString& OwnerId,
        const FString& NamespaceName,
        const FString& UserId,
        const FString& InventoryName,
        const FString& ItemName,
        const FString& ItemSetName
    )
    {
        return FString::Printf(
            TEXT("grn:gs2:%s:%s:inventory:%s:user:%s:inventory:%s:item:%s:itemSet:%s"),
            *Region, *OwnerId, *NamespaceName, *UserId, *InventoryName, *ItemName, *ItemSetName
        );
    }

    class FAddReferenceOfMutationSpeculativeCommit final
    {
        const Gs2::Core::Domain::FCacheDatabasePtr Cache;
        const TOptional<FString> NamespaceName;
        const FString UserId;
        const FString InventoryName;
        const FString ItemName;
        const FString ItemSetName;
        const TOptional<int32> TimeOffset;
        const FString ExpectedItemSetId;
        const TFunction<Gs2::Inventory::Model::FItemSetPtr(const Gs2::Inventory::Model::FItemSetPtr&)> Transform;

        bool IsExpected(const Gs2::Inventory::Model::FItemSetPtr& Item) const
        {
            return Item.IsValid() && Item->GetItemSetId().IsSet() && Item->GetItemSetId().Get(FString()) == ExpectedItemSetId &&
                Item->GetName().IsSet() && Item->GetName().Get(FString()) == ItemSetName &&
                Item->GetUserId().IsSet() && Item->GetUserId().Get(FString()) == UserId &&
                Item->GetInventoryName().IsSet() && Item->GetInventoryName().Get(FString()) == InventoryName &&
                Item->GetItemName().IsSet() && Item->GetItemName().Get(FString()) == ItemName &&
                Item->GetReferenceOf().IsValid();
        }

    public:
        FAddReferenceOfMutationSpeculativeCommit(
            const Gs2::Core::Domain::FCacheDatabasePtr& InCache,
            const TOptional<FString>& InNamespaceName,
            const FString& InUserId,
            const FString& InInventoryName,
            const FString& InItemName,
            const FString& InItemSetName,
            const TOptional<int32>& InTimeOffset,
            const FString& InExpectedItemSetId,
            const TFunction<Gs2::Inventory::Model::FItemSetPtr(const Gs2::Inventory::Model::FItemSetPtr&)>& InTransform
        ):
            Cache(InCache), NamespaceName(InNamespaceName), UserId(InUserId), InventoryName(InInventoryName),
            ItemName(InItemName), ItemSetName(InItemSetName), TimeOffset(InTimeOffset),
            ExpectedItemSetId(InExpectedItemSetId), Transform(InTransform)
        {
        }

        FString CompositionKey() const
        {
            return Gs2::Inventory::Model::Cache::FItemSetCache::CreateCacheParentKey(
                NamespaceName, UserId, InventoryName, TimeOffset
            ) + TEXT(":") + Gs2::Inventory::Model::Cache::FItemSetCache::CreateCacheKey(ItemName, ItemSetName);
        }

        bool TryCompose(const TSharedPtr<void>& Current, bool HasCurrent, TSharedPtr<void>& Next) const
        {
            try
            {
                Gs2::Inventory::Model::FItemSetPtr Item;
                if (HasCurrent)
                {
                    Item = StaticCastSharedPtr<Gs2::Inventory::Model::FItemSet>(Current);
                }
                else if (!Gs2::Inventory::Model::Cache::FItemSetCache::TryGet(
                    Cache, NamespaceName, UserId, InventoryName, ItemName, ItemSetName, TimeOffset, &Item
                ))
                {
                    Next = nullptr;
                    return false;
                }
                if (!IsExpected(Item))
                {
                    Next = nullptr;
                    return false;
                }
                const auto Changed = Transform(Item);
                if (!IsExpected(Changed))
                {
                    Next = nullptr;
                    return false;
                }
                Next = Changed;
                return true;
            }
            catch (...)
            {
                Next = nullptr;
                return false;
            }
        }

        void Commit(const TSharedPtr<void>& State) const
        {
            try
            {
                const auto Item = StaticCastSharedPtr<Gs2::Inventory::Model::FItemSet>(State);
                if (!IsExpected(Item)) return;
                Gs2::Inventory::Model::Cache::FItemSetCache::Put(
                    Cache, NamespaceName, UserId, InventoryName, ItemName, ItemSetName, TimeOffset, Item
                );
            }
            catch (...) { }
        }
    };
}

FString FAddReferenceOfByUserIdSpeculativeExecutor::Action()
{
    return FString("Gs2Inventory:AddReferenceOfByUserId");
}

Gs2::Core::Model::FGs2ErrorPtr FAddReferenceOfByUserIdSpeculativeExecutor::Transform(
    const Gs2::Core::Domain::FGs2Ptr&, const Gs2::Auth::Model::FAccessTokenPtr&,
    const Gs2::Inventory::Request::FAddReferenceOfByUserIdRequestPtr&, Gs2::Inventory::Model::FReferenceOfPtr
)
{
    return nullptr;
}

FAddReferenceOfByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
    const Gs2::Core::Domain::FGs2Ptr& Domain,
    const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
    const Gs2::Inventory::Request::FAddReferenceOfByUserIdRequestPtr& Request
): Domain(Domain), Service(Service), AccessToken(AccessToken), Request(Request) {}

FAddReferenceOfByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(const FCommitTask& From):
    Domain(From.Domain), Service(From.Service), AccessToken(From.AccessToken), Request(From.Request) {}

Gs2::Core::Model::FGs2ErrorPtr FAddReferenceOfByUserIdSpeculativeExecutor::FCommitTask::Action(
    TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
)
{
    *Result = nullptr;
    Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
    if (AccessToken.IsValid()) Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
    Gs2::Inventory::Request::FAddReferenceOfByUserIdRequestPtr Prepared = nullptr;
    if (Request.IsValid())
    {
        Prepared = MakeShared<Gs2::Inventory::Request::FAddReferenceOfByUserIdRequest>();
        Prepared->WithNamespaceName(Request->GetNamespaceName())
            ->WithInventoryName(Request->GetInventoryName())
            ->WithUserId(Request->GetUserId())
            ->WithItemName(Request->GetItemName())
            ->WithItemSetName(Request->GetItemSetName())
            ->WithReferenceOf(Request->GetReferenceOf())
            ->WithTimeOffsetToken(Request->GetTimeOffsetToken())
            ->WithDuplicationAvoider(Request->GetDuplicationAvoider());
    }
    if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Token.IsValid() || !Prepared.IsValid() ||
        !Token->GetUserId().IsSet() || Token->GetUserId().Get(FString()).IsEmpty()) return nullptr;
    if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}"))
        Prepared->WithUserId(Token->GetUserId());
    if (!Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != Token->GetUserId().Get(FString()) ||
        !Prepared->GetReferenceOf().IsSet()) return nullptr;

    const auto NamespaceName = Prepared->GetNamespaceName();
    const auto InventoryName = Prepared->GetInventoryName();
    const auto ItemName = Prepared->GetItemName();
    const auto ItemSetName = Prepared->GetItemSetName();
    const auto UserId = Token->GetUserId();
    const auto TimeOffset = Token->GetTimeOffset();
    const int64 UpdatedAt = static_cast<int64>(FDateTime::UtcNow().ToUnixTimestampDecimal() * 1000.0) +
        static_cast<int64>(TimeOffset.Get(0)) * 1000;
    const FString ExpectedId = AddReferenceOfExpectedItemSetId(
        Domain->RestSession->RegionName(), Domain->RestSession->OwnerId(), NamespaceName.Get(FString()),
        UserId.Get(FString()), InventoryName.Get(FString()), ItemName.Get(FString()), ItemSetName.Get(FString())
    );
    Gs2::Inventory::Model::FItemSetPtr Cached;
    if (!Gs2::Inventory::Model::Cache::FItemSetCache::TryGet(
        Domain->Cache, NamespaceName, UserId, InventoryName, ItemName, ItemSetName, TimeOffset, &Cached
    ) || !Cached.IsValid() || !Cached->GetItemSetId().IsSet() || Cached->GetItemSetId().Get(FString()) != ExpectedId ||
        !Cached->GetReferenceOf().IsValid()) return nullptr;

    const FString Reference = Prepared->GetReferenceOf().Get(FString());
    const auto Commit = MakeShared<FAddReferenceOfMutationSpeculativeCommit>(
        Domain->Cache, NamespaceName, UserId.Get(FString()), InventoryName.Get(FString()),
        ItemName.Get(FString()), ItemSetName.Get(FString()), TimeOffset, ExpectedId,
        [Reference, UpdatedAt](const Gs2::Inventory::Model::FItemSetPtr& Current)
        {
            if (!Current.IsValid() || !Current->GetReferenceOf().IsValid()) return Gs2::Inventory::Model::FItemSetPtr(nullptr);
            for (const auto& Existing : *Current->GetReferenceOf())
                if (Existing == Reference) return Gs2::Inventory::Model::FItemSetPtr(nullptr);
            auto References = MakeShared<TArray<FString>>();
            for (const auto& Existing : *Current->GetReferenceOf()) References->Add(Existing);
            References->Add(Reference);
            Gs2::Inventory::Model::FItemSetPtr Changed = MakeShared<Gs2::Inventory::Model::FItemSet>(*Current);
            if (!Changed.IsValid()) return Gs2::Inventory::Model::FItemSetPtr(nullptr);
            Changed->WithReferenceOf(References)->WithUpdatedAt(UpdatedAt);
            return Changed;
        }
    );
    *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateComposable(
        Commit->CompositionKey(),
        [Commit](const TSharedPtr<void>& Current, bool HasCurrent, TSharedPtr<void>& Next)
        { return Commit->TryCompose(Current, HasCurrent, Next); },
        [Commit](const TSharedPtr<void>& State) { Commit->Commit(State); }
    );
    return nullptr;
}

TSharedPtr<FAsyncTask<FAddReferenceOfByUserIdSpeculativeExecutor::FCommitTask>> FAddReferenceOfByUserIdSpeculativeExecutor::Execute(
    const Gs2::Core::Domain::FGs2Ptr& Domain,
    const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
    const Gs2::Inventory::Request::FAddReferenceOfByUserIdRequestPtr& Request
)
{
    return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
}

Gs2::Inventory::Request::FAddReferenceOfByUserIdRequestPtr FAddReferenceOfByUserIdSpeculativeExecutor::Rate(
    const Gs2::Inventory::Request::FAddReferenceOfByUserIdRequestPtr& Request, const double
)
{
    return Request;
}

Gs2::Inventory::Request::FAddReferenceOfByUserIdRequestPtr FAddReferenceOfByUserIdSpeculativeExecutor::Rate(
    const Gs2::Inventory::Request::FAddReferenceOfByUserIdRequestPtr& Request, TBigInt<1024, false>
)
{
    return Request;
}
}
