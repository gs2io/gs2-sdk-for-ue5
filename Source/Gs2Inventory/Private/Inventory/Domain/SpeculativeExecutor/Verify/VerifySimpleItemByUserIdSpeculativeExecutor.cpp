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

#include "Inventory/Domain/SpeculativeExecutor/Verify/VerifySimpleItemByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Inventory/Domain/SpeculativeExecutor/SimpleItemMutationSpeculativeCommit.h"
#include "Inventory/Model/Cache/SimpleItem.h"

namespace Gs2::Inventory::Domain::SpeculativeExecutor
{
namespace
{
using Private::FSimpleItemRate;
bool VerifySimpleItemType(const FString& Type)
{
    return Type == TEXT("less") || Type == TEXT("lessEqual") || Type == TEXT("greater") ||
        Type == TEXT("greaterEqual") || Type == TEXT("equal") || Type == TEXT("notEqual");
}
bool VerifySimpleItemFits(const FString& Text, int64& Out)
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
bool VerifySimpleItemValue(const Gs2::Inventory::Model::FSimpleItemPtr& Item, const FString& Id,
    const FString& UserId, const FString& Name, const FString& Type, int64 Count)
{
    if (!Item.IsValid() || !Item->GetItemId().IsSet() || Item->GetItemId().Get(FString()) != Id ||
        !Item->GetUserId().IsSet() || Item->GetUserId().Get(FString()) != UserId ||
        !Item->GetItemName().IsSet() || Item->GetItemName().Get(FString()) != Name || !Item->GetCount().IsSet()) return false;
    const int64 Current = Item->GetCount().Get(0);
    if (Type == TEXT("less")) return Current < Count;
    if (Type == TEXT("lessEqual")) return Current <= Count;
    if (Type == TEXT("greater")) return Current > Count;
    if (Type == TEXT("greaterEqual")) return Current >= Count;
    if (Type == TEXT("equal")) return Current == Count;
    if (Type == TEXT("notEqual")) return Current != Count;
    return false;
}
bool VerifySimpleItemRate(int64 Count, double Rate, int64& Out)
{
    FSimpleItemRate Value;
    return FSimpleItemRate::TryApplyRate(FSimpleItemRate::FromInt64(Count), Rate, Value) &&
        VerifySimpleItemFits(Value.ToString(), Out);
}
bool VerifySimpleItemRate(int64 Count, const FString& Rate, int64& Out)
{
    FSimpleItemRate Value;
    return FSimpleItemRate::TryApplyRate(FSimpleItemRate::FromInt64(Count), Rate, Value) &&
        VerifySimpleItemFits(Value.ToString(), Out);
}
}

    FString FVerifySimpleItemByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Inventory:VerifySimpleItemByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifySimpleItemByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr&, const Gs2::Auth::Model::FAccessTokenPtr&,
        const Gs2::Inventory::Request::FVerifySimpleItemByUserIdRequestPtr&, Gs2::Inventory::Model::FSimpleItemPtr)
    { return nullptr; }

    FVerifySimpleItemByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FVerifySimpleItemByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FVerifySimpleItemByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifySimpleItemByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
        if (AccessToken.IsValid()) Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::Inventory::Request::FVerifySimpleItemByUserIdRequestPtr Prepared = nullptr;
        if (Request.IsValid()) Prepared = MakeShared<Gs2::Inventory::Request::FVerifySimpleItemByUserIdRequest>(*Request);
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Token.IsValid() || !Prepared.IsValid() ||
            !Token->GetUserId().IsSet() || Token->GetUserId().Get(FString()).IsEmpty()) return nullptr;
        if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}"))
            Prepared->WithUserId(Token->GetUserId());
        if (!Prepared->GetNamespaceName().IsSet() || Prepared->GetNamespaceName().Get(FString()).IsEmpty() ||
            !Prepared->GetInventoryName().IsSet() || Prepared->GetInventoryName().Get(FString()).IsEmpty() ||
            !Prepared->GetItemName().IsSet() || Prepared->GetItemName().Get(FString()).IsEmpty() ||
            !Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != Token->GetUserId().Get(FString()) ||
            !Prepared->GetVerifyType().IsSet() || !VerifySimpleItemType(Prepared->GetVerifyType().Get(FString())) ||
            !Prepared->GetCount().IsSet()) return nullptr;
        const auto NamespaceName = Prepared->GetNamespaceName();
        const FString UserId = Token->GetUserId().Get(FString());
        const FString InventoryName = Prepared->GetInventoryName().Get(FString());
        const FString ItemName = Prepared->GetItemName().Get(FString());
        const FString VerifyType = Prepared->GetVerifyType().Get(FString());
        const int64 RequestCount = Prepared->GetCount().Get(0);
        const auto TimeOffset = Token->GetTimeOffset();
        const FString ExpectedId = FString::Printf(
            TEXT("grn:gs2:%s:%s:inventory:%s:user:%s:simple:inventory:%s:item:%s"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName.Get(FString()),
            *UserId, *InventoryName, *ItemName);
        Gs2::Inventory::Model::FSimpleItemPtr Cached;
        if (!Gs2::Inventory::Model::Cache::FSimpleItemCache::TryGet(
            Domain->Cache, NamespaceName, UserId, InventoryName, ItemName, TimeOffset, &Cached)) return nullptr;
    if (!Cached.IsValid()) Cached = MakeShared<Gs2::Inventory::Model::FSimpleItem>()
        ->WithItemId(ExpectedId)->WithUserId(UserId)->WithItemName(ItemName)->WithCount(TOptional<int64>(0));
        if (!Cached->GetItemId().IsSet() || Cached->GetItemId().Get(FString()) != ExpectedId ||
            !Cached->GetUserId().IsSet() || Cached->GetUserId().Get(FString()) != UserId ||
            !Cached->GetItemName().IsSet() || Cached->GetItemName().Get(FString()) != ItemName ||
            !Cached->GetCount().IsSet()) return nullptr;
        if (!VerifySimpleItemValue(Cached, ExpectedId, UserId, ItemName, VerifyType, RequestCount))
        {
            const auto Details = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("count"), TEXT("invalid"), TEXT("")));
            return MakeShared<Gs2::Core::Model::FBadRequestError>(Details);
        }
        const auto Guard = [Cache = Domain->Cache, NamespaceName, UserId, InventoryName, ItemName, TimeOffset,
            ExpectedId, VerifyType, RequestCount]()
        {
            Gs2::Inventory::Model::FSimpleItemPtr Current;
            if (!Gs2::Inventory::Model::Cache::FSimpleItemCache::TryGet(
                Cache, NamespaceName, UserId, InventoryName, ItemName, TimeOffset, &Current)) return false;
            if (!Current.IsValid()) Current = MakeShared<Gs2::Inventory::Model::FSimpleItem>()
                ->WithItemId(ExpectedId)->WithUserId(UserId)->WithItemName(ItemName)->WithCount(TOptional<int64>(0));
            return VerifySimpleItemValue(Current, ExpectedId, UserId, ItemName, VerifyType, RequestCount);
        };
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(
            MakeShared<TFunction<void()>>([]() {}), Guard);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVerifySimpleItemByUserIdSpeculativeExecutor::FCommitTask>> FVerifySimpleItemByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FVerifySimpleItemByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    TSharedPtr<FAsyncTask<FVerifySimpleItemByUserIdSpeculativeExecutor::FCommitTask>> FVerifySimpleItemByUserIdSpeculativeExecutor::ExecuteInverse(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FVerifySimpleItemByUserIdRequestPtr& Request
    )
    {
        if (!Request.IsValid()) return nullptr;
        auto Inverse = Gs2::Inventory::Request::FVerifySimpleItemByUserIdRequest::FromJson(Request->ToJson());
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

    Gs2::Inventory::Request::FVerifySimpleItemByUserIdRequestPtr FVerifySimpleItemByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inventory::Request::FVerifySimpleItemByUserIdRequestPtr& Request,
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
        if (!VerifySimpleItemRate(Request->GetCount().Get(0), Rate, Value)) return nullptr;
        Request->WithCount(Value);
        return Request;
    }

    Gs2::Inventory::Request::FVerifySimpleItemByUserIdRequestPtr FVerifySimpleItemByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inventory::Request::FVerifySimpleItemByUserIdRequestPtr& Request,
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
        if (!VerifySimpleItemRate(Request->GetCount().Get(0), Rate.ToString(), Value)) return nullptr;
        Request->WithCount(Value);
        return Request;
    }
}
