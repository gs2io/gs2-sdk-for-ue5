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

#include "Inventory/Domain/SpeculativeExecutor/Verify/VerifyItemSetByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Inventory/Domain/SpeculativeExecutor/SimpleItemMutationSpeculativeCommit.h"
#include "Inventory/Model/Cache/ItemSet.h"
#include "Inventory/Domain/Model/ItemSetEntry.h"

namespace Gs2::Inventory::Domain::SpeculativeExecutor
{
namespace
{
using Private::FSimpleItemRate;
bool VerifyItemSetType(const FString& Type)
{
    return Type == TEXT("less") || Type == TEXT("lessEqual") || Type == TEXT("greater") ||
        Type == TEXT("greaterEqual") || Type == TEXT("equal") || Type == TEXT("notEqual");
}
bool VerifyItemSetFits(const FString& Text, int64& Out)
{
    const bool Negative = Text.StartsWith(TEXT("-"));
    FString Magnitude = (Negative || Text.StartsWith(TEXT("+"))) ? Text.Mid(1) : Text;
    if (Magnitude.IsEmpty()) return false;
    while (Magnitude.Len() > 1 && Magnitude[0] == TEXT('0')) Magnitude = Magnitude.Mid(1);
    const FString Limit = Negative ? TEXT("9223372036854775808") : TEXT("9223372036854775807");
    if (Magnitude.Len() > Limit.Len() || (Magnitude.Len() == Limit.Len() && FCString::Strcmp(*Magnitude, *Limit) > 0)) return false;
    Out = FCString::Atoi64(*Text);
    return true;
}
bool VerifyItemSetRate(int64 Count, double Rate, int64& Out)
{
    FSimpleItemRate Value;
    return FSimpleItemRate::TryApplyRate(FSimpleItemRate::FromInt64(Count), Rate, Value) && VerifyItemSetFits(Value.ToString(), Out);
}
bool VerifyItemSetRate(int64 Count, const FString& Rate, int64& Out)
{
    FSimpleItemRate Value;
    return FSimpleItemRate::TryApplyRate(FSimpleItemRate::FromInt64(Count), Rate, Value) && VerifyItemSetFits(Value.ToString(), Out);
}
bool VerifyItemSetArray(const TArray<Gs2::Inventory::Model::FItemSetPtr>& Items, const FString& ExpectedRegion,
    const FString& ExpectedOwner, const FString& NamespaceName, const FString& UserId,
    const FString& InventoryName, const FString& ItemName, const TOptional<FString>& ItemSetName, int64 RequestCount,
    const FString& VerifyType)
{
    uint64 Bits = 0;
    for (const auto& Item : Items)
    {
        if (!Item.IsValid() || !Item->GetName().IsSet() || Item->GetName().Get(FString()).IsEmpty() ||
            (ItemSetName.IsSet() && Item->GetName().Get(FString()) != ItemSetName.Get(FString())) ||
            !Item->GetItemSetId().IsSet() || !Item->GetUserId().IsSet() || Item->GetUserId().Get(FString()) != UserId ||
            !Item->GetInventoryName().IsSet() || Item->GetInventoryName().Get(FString()) != InventoryName ||
            !Item->GetItemName().IsSet() || Item->GetItemName().Get(FString()) != ItemName || !Item->GetCount().IsSet()) return false;
        const FString ExpectedId = FString::Printf(TEXT("grn:gs2:%s:%s:inventory:%s:user:%s:inventory:%s:item:%s:itemSet:%s"),
            *ExpectedRegion, *ExpectedOwner, *NamespaceName, *UserId, *InventoryName, *ItemName, *Item->GetName().Get(FString()));
        if (Item->GetItemSetId().Get(FString()) != ExpectedId) return false;
        Bits += static_cast<uint64>(Item->GetCount().Get(0));
    }
    int64 Sum = 0;
    FMemory::Memcpy(&Sum, &Bits, sizeof(Sum));
    if (VerifyType == TEXT("less")) return Sum < RequestCount;
    if (VerifyType == TEXT("lessEqual")) return Sum <= RequestCount;
    if (VerifyType == TEXT("greater")) return Sum > RequestCount;
    if (VerifyType == TEXT("greaterEqual")) return Sum >= RequestCount;
    if (VerifyType == TEXT("equal")) return Sum == RequestCount;
    if (VerifyType == TEXT("notEqual")) return Sum != RequestCount;
    return false;
}
}

    FString FVerifyItemSetByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Inventory:VerifyItemSetByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyItemSetByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr&, const Gs2::Auth::Model::FAccessTokenPtr&,
        const Gs2::Inventory::Request::FVerifyItemSetByUserIdRequestPtr&, TSharedPtr<TArray<Gs2::Inventory::Model::FItemSetPtr>>)
    { return nullptr; }

    FVerifyItemSetByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FVerifyItemSetByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FVerifyItemSetByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyItemSetByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
        if (AccessToken.IsValid()) Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::Inventory::Request::FVerifyItemSetByUserIdRequestPtr Prepared = nullptr;
        if (Request.IsValid()) Prepared = MakeShared<Gs2::Inventory::Request::FVerifyItemSetByUserIdRequest>(*Request);
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Token.IsValid() || !Prepared.IsValid() ||
            !Token->GetUserId().IsSet() || Token->GetUserId().Get(FString()).IsEmpty()) return nullptr;
        if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}"))
            Prepared->WithUserId(Token->GetUserId());
        if (!Prepared->GetNamespaceName().IsSet() || Prepared->GetNamespaceName().Get(FString()).IsEmpty() ||
            !Prepared->GetInventoryName().IsSet() || Prepared->GetInventoryName().Get(FString()).IsEmpty() ||
            !Prepared->GetItemName().IsSet() || Prepared->GetItemName().Get(FString()).IsEmpty() ||
            !Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != Token->GetUserId().Get(FString()) ||
            !Prepared->GetVerifyType().IsSet() || !VerifyItemSetType(Prepared->GetVerifyType().Get(FString())) ||
            !Prepared->GetCount().IsSet()) return nullptr;
        const auto NamespaceName = Prepared->GetNamespaceName();
        const FString UserId = Token->GetUserId().Get(FString());
        const FString InventoryName = Prepared->GetInventoryName().Get(FString());
        const FString ItemName = Prepared->GetItemName().Get(FString());
        const auto ItemSetName = Prepared->GetItemSetName();
        const FString VerifyType = Prepared->GetVerifyType().Get(FString());
        const int64 RequestCount = Prepared->GetCount().Get(0);
        const auto TimeOffset = Token->GetTimeOffset();
        const FString Region = Domain->RestSession->RegionName();
        const FString Owner = Domain->RestSession->OwnerId();
        TArray<Gs2::Inventory::Model::FItemSetPtr> Snapshot;
        Gs2::Inventory::Model::FItemSetEntryPtr Aggregate;
        if (!ItemSetName.IsSet())
        {
            const FString Parent = Gs2::Inventory::Model::Cache::FItemSetCache::CreateCacheParentKey(
                NamespaceName, UserId, InventoryName, TimeOffset);
            if (!Domain->Cache->TryGet<Gs2::Inventory::Model::FItemSetEntry>(
                Parent, ItemName + TEXT(":any"), &Aggregate) || !Aggregate.IsValid()) return nullptr;
            Snapshot = Aggregate->Value;
        }
        else
        {
            Gs2::Inventory::Model::FItemSetPtr Cached;
            if (!Gs2::Inventory::Model::Cache::FItemSetCache::TryGet(
                Domain->Cache, NamespaceName, UserId, InventoryName, ItemName, ItemSetName, TimeOffset, &Cached)) return nullptr;
            if (Cached.IsValid()) Snapshot.Add(Cached);
        }
        if (!VerifyItemSetArray(Snapshot, Region, Owner, NamespaceName.Get(FString()), UserId, InventoryName,
            ItemName, ItemSetName, RequestCount, VerifyType))
        {
            const auto Details = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("count"), TEXT("invalid"), TEXT("")));
            return MakeShared<Gs2::Core::Model::FBadRequestError>(Details);
        }
        const auto Guard = [Cache = Domain->Cache, NamespaceName, UserId, InventoryName, ItemName, ItemSetName,
            TimeOffset, Region, Owner, VerifyType, RequestCount]()
        {
            TArray<Gs2::Inventory::Model::FItemSetPtr> CurrentItems;
            if (!ItemSetName.IsSet())
            {
                const FString Parent = Gs2::Inventory::Model::Cache::FItemSetCache::CreateCacheParentKey(
                    NamespaceName, UserId, InventoryName, TimeOffset);
                Gs2::Inventory::Model::FItemSetEntryPtr Entry;
                if (!Cache->TryGet<Gs2::Inventory::Model::FItemSetEntry>(
                    Parent, ItemName + TEXT(":any"), &Entry) || !Entry.IsValid()) return false;
                CurrentItems = Entry->Value;
            }
            else
            {
                Gs2::Inventory::Model::FItemSetPtr Current;
                if (!Gs2::Inventory::Model::Cache::FItemSetCache::TryGet(
                    Cache, NamespaceName, UserId, InventoryName, ItemName, ItemSetName, TimeOffset, &Current)) return false;
                if (Current.IsValid()) CurrentItems.Add(Current);
            }
            return VerifyItemSetArray(CurrentItems, Region, Owner, NamespaceName.Get(FString()), UserId,
                InventoryName, ItemName, ItemSetName, RequestCount, VerifyType);
        };
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(
            MakeShared<TFunction<void()>>([]() {}), Guard);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVerifyItemSetByUserIdSpeculativeExecutor::FCommitTask>> FVerifyItemSetByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FVerifyItemSetByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    TSharedPtr<FAsyncTask<FVerifyItemSetByUserIdSpeculativeExecutor::FCommitTask>> FVerifyItemSetByUserIdSpeculativeExecutor::ExecuteInverse(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FVerifyItemSetByUserIdRequestPtr& Request
    )
    {
        if (!Request.IsValid()) return nullptr;
        auto Inverse = Gs2::Inventory::Request::FVerifyItemSetByUserIdRequest::FromJson(Request->ToJson());
        if (!Inverse.IsValid() || !Inverse->GetVerifyType().IsSet()) return nullptr;
        const FString VerifyType = Inverse->GetVerifyType().Get(FString());
        if (VerifyType == TEXT("less")) Inverse->WithVerifyType(TOptional<FString>(TEXT("greaterEqual")));
        else if (VerifyType == TEXT("lessEqual")) Inverse->WithVerifyType(TOptional<FString>(TEXT("greater")));
        else if (VerifyType == TEXT("greater")) Inverse->WithVerifyType(TOptional<FString>(TEXT("lessEqual")));
        else if (VerifyType == TEXT("greaterEqual")) Inverse->WithVerifyType(TOptional<FString>(TEXT("less")));
        else if (VerifyType == TEXT("equal")) Inverse->WithVerifyType(TOptional<FString>(TEXT("notEqual")));
        else if (VerifyType == TEXT("notEqual")) Inverse->WithVerifyType(TOptional<FString>(TEXT("equal")));
        else return nullptr;
        return Execute(Domain, Service, AccessToken, Inverse);
    }

    Gs2::Inventory::Request::FVerifyItemSetByUserIdRequestPtr FVerifyItemSetByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inventory::Request::FVerifyItemSetByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (!Request.IsValid()) return Request;
        const bool Apply = Request->GetMultiplyValueSpecifyingQuantity().IsSet() ?
            Request->GetMultiplyValueSpecifyingQuantity().Get(false) :
            (Request->GetVerifyType().IsSet() && (Request->GetVerifyType().Get(FString()) == TEXT("greater") ||
                Request->GetVerifyType().Get(FString()) == TEXT("greaterEqual")));
        if (!Apply) return Request;
        if (!Request->GetCount().IsSet()) return nullptr;
        int64 Value = 0;
        if (!VerifyItemSetRate(Request->GetCount().Get(0), Rate, Value)) return nullptr;
        Request->WithCount(Value);
        return Request;
    }

    Gs2::Inventory::Request::FVerifyItemSetByUserIdRequestPtr FVerifyItemSetByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inventory::Request::FVerifyItemSetByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (!Request.IsValid()) return Request;
        const bool Apply = Request->GetMultiplyValueSpecifyingQuantity().IsSet() ?
            Request->GetMultiplyValueSpecifyingQuantity().Get(false) :
            (Request->GetVerifyType().IsSet() && (Request->GetVerifyType().Get(FString()) == TEXT("greater") ||
                Request->GetVerifyType().Get(FString()) == TEXT("greaterEqual")));
        if (!Apply) return Request;
        if (!Request->GetCount().IsSet()) return nullptr;
        int64 Value = 0;
        if (!VerifyItemSetRate(Request->GetCount().Get(0), Rate.ToString(), Value)) return nullptr;
        Request->WithCount(Value);
        return Request;
    }
}
