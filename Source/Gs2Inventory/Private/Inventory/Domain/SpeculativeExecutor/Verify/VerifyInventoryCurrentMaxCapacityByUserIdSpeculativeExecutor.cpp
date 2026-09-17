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

#include "Inventory/Domain/SpeculativeExecutor/Verify/VerifyInventoryCurrentMaxCapacityByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Inventory/Domain/SpeculativeExecutor/SimpleItemMutationSpeculativeCommit.h"
#include "Inventory/Model/Cache/Inventory.h"

namespace Gs2::Inventory::Domain::SpeculativeExecutor
{
namespace
{
using Private::FSimpleItemRate;
bool VerifyCapacityType(const FString& Type)
{
    return Type == TEXT("less") || Type == TEXT("lessEqual") || Type == TEXT("greater") ||
        Type == TEXT("greaterEqual") || Type == TEXT("equal") || Type == TEXT("notEqual");
}
bool VerifyCapacityValue(const Gs2::Inventory::Model::FInventoryPtr& Item, const FString& Id,
    const FString& UserId, const FString& Name, const FString& Type, int32 Count)
{
    if (!Item.IsValid() || !Item->GetInventoryId().IsSet() || Item->GetInventoryId().Get(FString()) != Id ||
        !Item->GetUserId().IsSet() || Item->GetUserId().Get(FString()) != UserId ||
        !Item->GetInventoryName().IsSet() || Item->GetInventoryName().Get(FString()) != Name ||
        !Item->GetCurrentInventoryMaxCapacity().IsSet()) return false;
    const int32 Current = Item->GetCurrentInventoryMaxCapacity().Get(0);
    if (Type == TEXT("less")) return Current < Count;
    if (Type == TEXT("lessEqual")) return Current <= Count;
    if (Type == TEXT("greater")) return Current > Count;
    if (Type == TEXT("greaterEqual")) return Current >= Count;
    if (Type == TEXT("equal")) return Current == Count;
    if (Type == TEXT("notEqual")) return Current != Count;
    return false;
}
bool VerifyCapacityFits(const FString& Text, int32& Out)
{
    const bool Negative = Text.StartsWith(TEXT("-"));
    FString Magnitude = (Negative || Text.StartsWith(TEXT("+"))) ? Text.Mid(1) : Text;
    while (Magnitude.Len() > 1 && Magnitude[0] == TEXT('0')) Magnitude = Magnitude.Mid(1);
    const FString Limit = Negative ? TEXT("2147483648") : TEXT("2147483647");
    if (Magnitude.IsEmpty() || Magnitude.Len() > Limit.Len() ||
        (Magnitude.Len() == Limit.Len() && FCString::Strcmp(*Magnitude, *Limit) > 0)) return false;
    Out = FCString::Atoi(*Text);
    return true;
}
bool VerifyCapacityRate(int32 Count, double Rate, int32& Out)
{
    FSimpleItemRate Value;
    return FSimpleItemRate::TryApplyRate(FSimpleItemRate::FromInt64(Count), Rate, Value) &&
        VerifyCapacityFits(Value.ToString(), Out);
}
bool VerifyCapacityRate(int32 Count, const FString& Rate, int32& Out)
{
    FSimpleItemRate Value;
    return FSimpleItemRate::TryApplyRate(FSimpleItemRate::FromInt64(Count), Rate, Value) &&
        VerifyCapacityFits(Value.ToString(), Out);
}
}

    FString FVerifyInventoryCurrentMaxCapacityByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Inventory:VerifyInventoryCurrentMaxCapacityByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyInventoryCurrentMaxCapacityByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr&, const Gs2::Auth::Model::FAccessTokenPtr&,
        const Gs2::Inventory::Request::FVerifyInventoryCurrentMaxCapacityByUserIdRequestPtr&, Gs2::Inventory::Model::FInventoryPtr)
    { return nullptr; }

    FVerifyInventoryCurrentMaxCapacityByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FVerifyInventoryCurrentMaxCapacityByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FVerifyInventoryCurrentMaxCapacityByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyInventoryCurrentMaxCapacityByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
        if (AccessToken.IsValid()) Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::Inventory::Request::FVerifyInventoryCurrentMaxCapacityByUserIdRequestPtr Prepared = nullptr;
        if (Request.IsValid()) Prepared = MakeShared<Gs2::Inventory::Request::FVerifyInventoryCurrentMaxCapacityByUserIdRequest>(*Request);
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Token.IsValid() || !Prepared.IsValid() ||
            !Token->GetUserId().IsSet() || Token->GetUserId().Get(FString()).IsEmpty()) return nullptr;
        if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}"))
            Prepared->WithUserId(Token->GetUserId());
        if (!Prepared->GetNamespaceName().IsSet() || Prepared->GetNamespaceName().Get(FString()).IsEmpty() ||
            !Prepared->GetInventoryName().IsSet() || Prepared->GetInventoryName().Get(FString()).IsEmpty() ||
            !Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != Token->GetUserId().Get(FString()) ||
            !Prepared->GetVerifyType().IsSet() || !VerifyCapacityType(Prepared->GetVerifyType().Get(FString())) ||
            !Prepared->GetCurrentInventoryMaxCapacity().IsSet()) return nullptr;
        const auto NamespaceName = Prepared->GetNamespaceName();
        const FString UserId = Token->GetUserId().Get(FString());
        const FString InventoryName = Prepared->GetInventoryName().Get(FString());
        const FString VerifyType = Prepared->GetVerifyType().Get(FString());
        const int32 RequestCapacity = Prepared->GetCurrentInventoryMaxCapacity().Get(0);
        const auto TimeOffset = Token->GetTimeOffset();
        const FString ExpectedId = FString::Printf(
            TEXT("grn:gs2:%s:%s:inventory:%s:user:%s:inventory:%s"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName.Get(FString()),
            *UserId, *InventoryName);
        Gs2::Inventory::Model::FInventoryPtr Cached;
        if (!Gs2::Inventory::Model::Cache::FInventoryCache::TryGet(
            Domain->Cache, NamespaceName, UserId, InventoryName, TimeOffset, &Cached) || !Cached.IsValid()) return nullptr;
        if (!Cached->GetInventoryId().IsSet() || Cached->GetInventoryId().Get(FString()) != ExpectedId ||
            !Cached->GetUserId().IsSet() || Cached->GetUserId().Get(FString()) != UserId ||
            !Cached->GetInventoryName().IsSet() || Cached->GetInventoryName().Get(FString()) != InventoryName ||
            !Cached->GetCurrentInventoryMaxCapacity().IsSet()) return nullptr;
        if (!VerifyCapacityValue(Cached, ExpectedId, UserId, InventoryName, VerifyType, RequestCapacity))
        {
            const auto Details = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("count"), TEXT("invalid"), TEXT("")));
            return MakeShared<Gs2::Core::Model::FBadRequestError>(Details);
        }
        const auto Guard = [Cache = Domain->Cache, NamespaceName, UserId, InventoryName, TimeOffset,
            ExpectedId, VerifyType, RequestCapacity]()
        {
            Gs2::Inventory::Model::FInventoryPtr Current;
            if (!Gs2::Inventory::Model::Cache::FInventoryCache::TryGet(
                Cache, NamespaceName, UserId, InventoryName, TimeOffset, &Current) || !Current.IsValid()) return false;
            return VerifyCapacityValue(Current, ExpectedId, UserId, InventoryName, VerifyType, RequestCapacity);
        };
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(
            MakeShared<TFunction<void()>>([]() {}), Guard);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVerifyInventoryCurrentMaxCapacityByUserIdSpeculativeExecutor::FCommitTask>> FVerifyInventoryCurrentMaxCapacityByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FVerifyInventoryCurrentMaxCapacityByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    TSharedPtr<FAsyncTask<FVerifyInventoryCurrentMaxCapacityByUserIdSpeculativeExecutor::FCommitTask>> FVerifyInventoryCurrentMaxCapacityByUserIdSpeculativeExecutor::ExecuteInverse(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FVerifyInventoryCurrentMaxCapacityByUserIdRequestPtr& Request
    )
    {
        if (!Request.IsValid()) return nullptr;
        auto Inverse = Gs2::Inventory::Request::FVerifyInventoryCurrentMaxCapacityByUserIdRequest::FromJson(Request->ToJson());
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

    Gs2::Inventory::Request::FVerifyInventoryCurrentMaxCapacityByUserIdRequestPtr FVerifyInventoryCurrentMaxCapacityByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inventory::Request::FVerifyInventoryCurrentMaxCapacityByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (!Request.IsValid()) return Request;
        if (!Request->GetMultiplyValueSpecifyingQuantity().IsSet() ||
            !Request->GetMultiplyValueSpecifyingQuantity().Get(false)) return Request;
        if (!Request->GetCurrentInventoryMaxCapacity().IsSet()) return nullptr;
        int32 Value = 0;
        if (!VerifyCapacityRate(Request->GetCurrentInventoryMaxCapacity().Get(0), Rate, Value)) return nullptr;
        Request->WithCurrentInventoryMaxCapacity(Value);
        return Request;
    }

    Gs2::Inventory::Request::FVerifyInventoryCurrentMaxCapacityByUserIdRequestPtr FVerifyInventoryCurrentMaxCapacityByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inventory::Request::FVerifyInventoryCurrentMaxCapacityByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (!Request.IsValid()) return Request;
        if (!Request->GetMultiplyValueSpecifyingQuantity().IsSet() ||
            !Request->GetMultiplyValueSpecifyingQuantity().Get(false)) return Request;
        if (!Request->GetCurrentInventoryMaxCapacity().IsSet()) return nullptr;
        int32 Value = 0;
        if (!VerifyCapacityRate(Request->GetCurrentInventoryMaxCapacity().Get(0), Rate.ToString(), Value)) return nullptr;
        Request->WithCurrentInventoryMaxCapacity(Value);
        return Request;
    }
}
