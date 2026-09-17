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

#include "Inventory/Domain/SpeculativeExecutor/Verify/VerifyBigItemByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Inventory/Domain/SpeculativeExecutor/BigItemMutationSpeculativeCommit.h"
#include "Inventory/Model/Cache/BigItem.h"

namespace Gs2::Inventory::Domain::SpeculativeExecutor
{
namespace
{
using Private::FBigInteger;

bool VerifyBigItemCompare(const FString& Left, const FString& Right, const FString& Type)
{
    const bool LeftNegative = Left.StartsWith(TEXT("-"));
    const bool RightNegative = Right.StartsWith(TEXT("-"));
    const FString LeftMagnitude = LeftNegative || Left.StartsWith(TEXT("+")) ? Left.Mid(1) : Left;
    const FString RightMagnitude = RightNegative || Right.StartsWith(TEXT("+")) ? Right.Mid(1) : Right;
    int32 Magnitude = 0;
    if (LeftNegative != RightNegative) Magnitude = LeftNegative ? -1 : 1;
    else if (LeftMagnitude.Len() != RightMagnitude.Len())
        Magnitude = LeftMagnitude.Len() < RightMagnitude.Len() ? -1 : 1;
    else if (LeftMagnitude != RightMagnitude)
        Magnitude = FCString::Strcmp(*LeftMagnitude, *RightMagnitude) < 0 ? -1 : 1;
    if (LeftNegative && RightNegative) Magnitude = -Magnitude;
    if (Type == TEXT("less")) return Magnitude < 0;
    if (Type == TEXT("lessEqual")) return Magnitude <= 0;
    if (Type == TEXT("greater")) return Magnitude > 0;
    if (Type == TEXT("greaterEqual")) return Magnitude >= 0;
    if (Type == TEXT("equal")) return Magnitude == 0;
    if (Type == TEXT("notEqual")) return Magnitude != 0;
    return false;
}

bool VerifyBigItemValidType(const FString& Type)
{
    return Type == TEXT("less") || Type == TEXT("lessEqual") || Type == TEXT("greater") ||
        Type == TEXT("greaterEqual") || Type == TEXT("equal") || Type == TEXT("notEqual");
}

bool VerifyBigItemPredicate(
    const Gs2::Inventory::Model::FBigItemPtr& Item,
    const FString& ExpectedId, const FString& UserId, const FString& ItemName,
    const FString& VerifyType, const FString& RequestCount)
{
    if (!Item.IsValid() || !Item->GetItemId().IsSet() || Item->GetItemId().Get(FString()) != ExpectedId ||
        !Item->GetUserId().IsSet() || Item->GetUserId().Get(FString()) != UserId ||
        !Item->GetItemName().IsSet() || Item->GetItemName().Get(FString()) != ItemName ||
        !Item->GetCount().IsSet()) return false;
    FBigInteger Current;
    FBigInteger Requested;
    if (!FBigInteger::TryParse(Item->GetCount().Get(FString()), Current) ||
        !FBigInteger::TryParse(RequestCount, Requested)) return false;
    return VerifyBigItemCompare(Current.ToString(), Requested.ToString(), VerifyType);
}
}

    FString FVerifyBigItemByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Inventory:VerifyBigItemByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyBigItemByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr&, const Gs2::Auth::Model::FAccessTokenPtr&,
        const Gs2::Inventory::Request::FVerifyBigItemByUserIdRequestPtr&, Gs2::Inventory::Model::FBigItemPtr)
    { return nullptr; }

    FVerifyBigItemByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FVerifyBigItemByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FVerifyBigItemByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyBigItemByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
        if (AccessToken.IsValid()) Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::Inventory::Request::FVerifyBigItemByUserIdRequestPtr Prepared = nullptr;
        if (Request.IsValid()) Prepared = MakeShared<Gs2::Inventory::Request::FVerifyBigItemByUserIdRequest>(*Request);
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Token.IsValid() || !Prepared.IsValid() ||
            !Token->GetUserId().IsSet() || Token->GetUserId().Get(FString()).IsEmpty()) return nullptr;
        if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}"))
            Prepared->WithUserId(Token->GetUserId());
        if (!Prepared->GetNamespaceName().IsSet() || Prepared->GetNamespaceName().Get(FString()).IsEmpty() ||
            !Prepared->GetInventoryName().IsSet() || Prepared->GetInventoryName().Get(FString()).IsEmpty() ||
            !Prepared->GetItemName().IsSet() || Prepared->GetItemName().Get(FString()).IsEmpty() ||
            !Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != Token->GetUserId().Get(FString()) ||
            !Prepared->GetVerifyType().IsSet() || !VerifyBigItemValidType(Prepared->GetVerifyType().Get(FString())) ||
            !Prepared->GetCount().IsSet()) return nullptr;
        const auto NamespaceName = Prepared->GetNamespaceName();
        const FString UserId = Token->GetUserId().Get(FString());
        const FString InventoryName = Prepared->GetInventoryName().Get(FString());
        const FString ItemName = Prepared->GetItemName().Get(FString());
        const FString VerifyType = Prepared->GetVerifyType().Get(FString());
        const FString RequestCount = Prepared->GetCount().Get(FString());
        const auto TimeOffset = Token->GetTimeOffset();
        const FString ExpectedId = Private::BigItemExpectedId(
            Domain->RestSession->RegionName(), Domain->RestSession->OwnerId(), NamespaceName.Get(FString()),
            UserId, InventoryName, ItemName);
        Gs2::Inventory::Model::FBigItemPtr Cached;
        if (!Gs2::Inventory::Model::Cache::FBigItemCache::TryGet(
            Domain->Cache, NamespaceName, UserId, InventoryName, ItemName, TimeOffset, &Cached)) return nullptr;
        if (!Cached.IsValid()) Cached = MakeShared<Gs2::Inventory::Model::FBigItem>()
            ->WithItemId(ExpectedId)->WithUserId(UserId)->WithItemName(ItemName)->WithCount(FString(TEXT("0")));
        if (!Cached->GetItemId().IsSet() || Cached->GetItemId().Get(FString()) != ExpectedId ||
            !Cached->GetUserId().IsSet() || Cached->GetUserId().Get(FString()) != UserId ||
            !Cached->GetItemName().IsSet() || Cached->GetItemName().Get(FString()) != ItemName ||
            !Cached->GetCount().IsSet()) return nullptr;
        FBigInteger CurrentCount;
        FBigInteger RequestedCount;
        if (!FBigInteger::TryParse(Cached->GetCount().Get(FString()), CurrentCount) ||
            !FBigInteger::TryParse(RequestCount, RequestedCount)) return nullptr;
        if (!VerifyBigItemPredicate(Cached, ExpectedId, UserId, ItemName, VerifyType, RequestCount))
        {
            const auto Details = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("count"), TEXT("invalid"), TEXT("")));
            return MakeShared<Gs2::Core::Model::FBadRequestError>(Details);
        }
        const auto Guard = [Cache = Domain->Cache, NamespaceName, UserId, InventoryName, ItemName, TimeOffset,
            ExpectedId, VerifyType, RequestCount]()
        {
            Gs2::Inventory::Model::FBigItemPtr Current;
            if (!Gs2::Inventory::Model::Cache::FBigItemCache::TryGet(
                Cache, NamespaceName, UserId, InventoryName, ItemName, TimeOffset, &Current)) return false;
            if (!Current.IsValid()) Current = MakeShared<Gs2::Inventory::Model::FBigItem>()
                ->WithItemId(ExpectedId)->WithUserId(UserId)->WithItemName(ItemName)->WithCount(FString(TEXT("0")));
            return VerifyBigItemPredicate(Current, ExpectedId, UserId, ItemName, VerifyType, RequestCount);
        };
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(
            MakeShared<TFunction<void()>>([]() {}), Guard);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVerifyBigItemByUserIdSpeculativeExecutor::FCommitTask>> FVerifyBigItemByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FVerifyBigItemByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    TSharedPtr<FAsyncTask<FVerifyBigItemByUserIdSpeculativeExecutor::FCommitTask>> FVerifyBigItemByUserIdSpeculativeExecutor::ExecuteInverse(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FVerifyBigItemByUserIdRequestPtr& Request
    )
    {
        if (!Request.IsValid()) return nullptr;
        auto Inverse = Gs2::Inventory::Request::FVerifyBigItemByUserIdRequest::FromJson(Request->ToJson());
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

    Gs2::Inventory::Request::FVerifyBigItemByUserIdRequestPtr FVerifyBigItemByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inventory::Request::FVerifyBigItemByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (!Request.IsValid()) return Request;
        bool Apply = Request->GetMultiplyValueSpecifyingQuantity().IsSet() ?
            Request->GetMultiplyValueSpecifyingQuantity().Get(false) :
            (Request->GetVerifyType().IsSet() && (Request->GetVerifyType().Get(FString()) == TEXT("greater") ||
                Request->GetVerifyType().Get(FString()) == TEXT("greaterEqual")));
        if (!Apply) return Request;
        if (!Request->GetCount().IsSet()) return nullptr;
        FBigInteger Count, Value;
        if (!FBigInteger::TryParse(Request->GetCount().Get(FString()), Count) ||
            !FBigInteger::TryApplyRate(Count, Rate, Value)) return nullptr;
        Request->WithCount(Value.ToString());
        return Request;
    }

    Gs2::Inventory::Request::FVerifyBigItemByUserIdRequestPtr FVerifyBigItemByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inventory::Request::FVerifyBigItemByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (!Request.IsValid()) return Request;
        bool Apply = Request->GetMultiplyValueSpecifyingQuantity().IsSet() ?
            Request->GetMultiplyValueSpecifyingQuantity().Get(false) :
            (Request->GetVerifyType().IsSet() && (Request->GetVerifyType().Get(FString()) == TEXT("greater") ||
                Request->GetVerifyType().Get(FString()) == TEXT("greaterEqual")));
        if (!Apply) return Request;
        if (!Request->GetCount().IsSet()) return nullptr;
        FBigInteger Count, Value;
        if (!FBigInteger::TryParse(Request->GetCount().Get(FString()), Count) ||
            !FBigInteger::TryApplyRate(Count, Rate.ToString(), Value)) return nullptr;
        Request->WithCount(Value.ToString());
        return Request;
    }
}
