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

#include "Inventory/Domain/SpeculativeExecutor/Verify/VerifyReferenceOfByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Inventory/Model/Cache/ItemSet.h"

namespace Gs2::Inventory::Domain::SpeculativeExecutor
{
namespace
{
bool VerifyReferenceType(const FString& Type)
{
    return Type == TEXT("not_entry") || Type == TEXT("already_entry") || Type == TEXT("empty") || Type == TEXT("not_empty");
}
bool VerifyReferenceValue(const Gs2::Inventory::Model::FItemSetPtr& Item, const FString& Id,
    const FString& UserId, const FString& InventoryName, const FString& ItemName, const FString& ItemSetName,
    const FString& ReferenceOf, const FString& VerifyType)
{
    if (!Item.IsValid() || !Item->GetItemSetId().IsSet() || Item->GetItemSetId().Get(FString()) != Id ||
        !Item->GetName().IsSet() || Item->GetName().Get(FString()) != ItemSetName ||
        !Item->GetUserId().IsSet() || Item->GetUserId().Get(FString()) != UserId ||
        !Item->GetInventoryName().IsSet() || Item->GetInventoryName().Get(FString()) != InventoryName ||
        !Item->GetItemName().IsSet() || Item->GetItemName().Get(FString()) != ItemName ||
        !Item->GetReferenceOf().IsValid()) return false;
    const TArray<FString> References = *Item->GetReferenceOf();
    const bool Contains = References.Contains(ReferenceOf);
    if (VerifyType == TEXT("not_entry")) return !Contains;
    if (VerifyType == TEXT("already_entry")) return Contains;
    if (VerifyType == TEXT("empty")) return References.Num() == 0;
    if (VerifyType == TEXT("not_empty")) return References.Num() != 0;
    return false;
}
}

    FString FVerifyReferenceOfByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Inventory:VerifyReferenceOfByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyReferenceOfByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr&, const Gs2::Auth::Model::FAccessTokenPtr&,
        const Gs2::Inventory::Request::FVerifyReferenceOfByUserIdRequestPtr&, TSharedPtr<TArray<FString>>)
    { return nullptr; }

    FVerifyReferenceOfByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FVerifyReferenceOfByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FVerifyReferenceOfByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyReferenceOfByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
        if (AccessToken.IsValid()) Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::Inventory::Request::FVerifyReferenceOfByUserIdRequestPtr Prepared = nullptr;
        if (Request.IsValid()) Prepared = MakeShared<Gs2::Inventory::Request::FVerifyReferenceOfByUserIdRequest>(*Request);
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Token.IsValid() || !Prepared.IsValid() ||
            !Token->GetUserId().IsSet() || Token->GetUserId().Get(FString()).IsEmpty()) return nullptr;
        if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}"))
            Prepared->WithUserId(Token->GetUserId());
        if (!Prepared->GetNamespaceName().IsSet() || Prepared->GetNamespaceName().Get(FString()).IsEmpty() ||
            !Prepared->GetInventoryName().IsSet() || Prepared->GetInventoryName().Get(FString()).IsEmpty() ||
            !Prepared->GetItemName().IsSet() || Prepared->GetItemName().Get(FString()).IsEmpty() ||
            !Prepared->GetItemSetName().IsSet() || Prepared->GetItemSetName().Get(FString()).IsEmpty() ||
            !Prepared->GetReferenceOf().IsSet() || !Prepared->GetVerifyType().IsSet() ||
            !VerifyReferenceType(Prepared->GetVerifyType().Get(FString())) ||
            !Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != Token->GetUserId().Get(FString())) return nullptr;
        const auto NamespaceName = Prepared->GetNamespaceName();
        const FString UserId = Token->GetUserId().Get(FString());
        const FString InventoryName = Prepared->GetInventoryName().Get(FString());
        const FString ItemName = Prepared->GetItemName().Get(FString());
        const FString ItemSetName = Prepared->GetItemSetName().Get(FString());
        const FString ReferenceOf = Prepared->GetReferenceOf().Get(FString());
        const FString VerifyType = Prepared->GetVerifyType().Get(FString());
        const auto TimeOffset = Token->GetTimeOffset();
        const FString ExpectedId = FString::Printf(
            TEXT("grn:gs2:%s:%s:inventory:%s:user:%s:inventory:%s:item:%s:itemSet:%s"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName.Get(FString()),
            *UserId, *InventoryName, *ItemName, *ItemSetName);
        Gs2::Inventory::Model::FItemSetPtr Cached;
        if (!Gs2::Inventory::Model::Cache::FItemSetCache::TryGet(
            Domain->Cache, NamespaceName, UserId, InventoryName, ItemName, ItemSetName, TimeOffset, &Cached) || !Cached.IsValid()) return nullptr;
        if (!VerifyReferenceValue(Cached, ExpectedId, UserId, InventoryName, ItemName, ItemSetName, ReferenceOf, VerifyType))
        {
            const auto Details = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("count"), TEXT("invalid"), TEXT("")));
            return MakeShared<Gs2::Core::Model::FBadRequestError>(Details);
        }
        const auto Guard = [Cache = Domain->Cache, NamespaceName, UserId, InventoryName, ItemName, ItemSetName,
            TimeOffset, ExpectedId, ReferenceOf, VerifyType]()
        {
            Gs2::Inventory::Model::FItemSetPtr Current;
            if (!Gs2::Inventory::Model::Cache::FItemSetCache::TryGet(
                Cache, NamespaceName, UserId, InventoryName, ItemName, ItemSetName, TimeOffset, &Current) || !Current.IsValid()) return false;
            return VerifyReferenceValue(Current, ExpectedId, UserId, InventoryName, ItemName, ItemSetName, ReferenceOf, VerifyType);
        };
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(
            MakeShared<TFunction<void()>>([]() {}), Guard);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVerifyReferenceOfByUserIdSpeculativeExecutor::FCommitTask>> FVerifyReferenceOfByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FVerifyReferenceOfByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    TSharedPtr<FAsyncTask<FVerifyReferenceOfByUserIdSpeculativeExecutor::FCommitTask>> FVerifyReferenceOfByUserIdSpeculativeExecutor::ExecuteInverse(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FVerifyReferenceOfByUserIdRequestPtr& Request
    )
    {
        if (!Request.IsValid()) return nullptr;
        auto Inverse = Gs2::Inventory::Request::FVerifyReferenceOfByUserIdRequest::FromJson(Request->ToJson());
        if (!Inverse.IsValid() || !Inverse->GetVerifyType().IsSet()) return nullptr;
        const FString VerifyType = Inverse->GetVerifyType().Get(FString());
        if (VerifyType == TEXT("not_entry")) Inverse->WithVerifyType(TOptional<FString>(TEXT("already_entry")));
        else if (VerifyType == TEXT("already_entry")) Inverse->WithVerifyType(TOptional<FString>(TEXT("not_entry")));
        else if (VerifyType == TEXT("empty")) Inverse->WithVerifyType(TOptional<FString>(TEXT("not_empty")));
        else if (VerifyType == TEXT("not_empty")) Inverse->WithVerifyType(TOptional<FString>(TEXT("empty")));
        else return nullptr;
        return Execute(Domain, Service, AccessToken, Inverse);
    }

    Gs2::Inventory::Request::FVerifyReferenceOfByUserIdRequestPtr FVerifyReferenceOfByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inventory::Request::FVerifyReferenceOfByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Inventory::Request::FVerifyReferenceOfByUserIdRequestPtr FVerifyReferenceOfByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inventory::Request::FVerifyReferenceOfByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
