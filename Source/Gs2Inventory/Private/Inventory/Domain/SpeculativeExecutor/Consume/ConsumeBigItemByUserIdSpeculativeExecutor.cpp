// deny overwrite: BigItem の数量は文字列（BigInt）なので、生成器の数値前提の Rate() は使えない。FBigInteger（BigItemMutationSpeculativeCommit.h）で手書き
/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458)
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"
#endif

#include "Inventory/Domain/SpeculativeExecutor/Consume/ConsumeBigItemByUserIdSpeculativeExecutor.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Inventory/Domain/SpeculativeExecutor/BigItemMutationSpeculativeCommit.h"

namespace Gs2::Inventory::Domain::SpeculativeExecutor
{
using Private::FBigInteger;
using Private::FBigItemMutationSpeculativeCommit;

FString FConsumeBigItemByUserIdSpeculativeExecutor::Action()
{
    return FString("Gs2Inventory:ConsumeBigItemByUserId");
}

Gs2::Core::Model::FGs2ErrorPtr FConsumeBigItemByUserIdSpeculativeExecutor::Transform(
    const Gs2::Core::Domain::FGs2Ptr& Domain,
    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
    const Gs2::Inventory::Request::FConsumeBigItemByUserIdRequestPtr& Request,
    Gs2::Inventory::Model::FBigItemPtr Item
)
{
    return nullptr;
}

FConsumeBigItemByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
    const Gs2::Core::Domain::FGs2Ptr& Domain,
    const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
    const Gs2::Inventory::Request::FConsumeBigItemByUserIdRequestPtr& Request
):
    Domain(Domain), Service(Service), AccessToken(AccessToken), Request(Request)
{
}

FConsumeBigItemByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(const FCommitTask& From):
    Domain(From.Domain), Service(From.Service), AccessToken(From.AccessToken), Request(From.Request)
{
}

Gs2::Core::Model::FGs2ErrorPtr FConsumeBigItemByUserIdSpeculativeExecutor::FCommitTask::Action(
    TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
)
{
    *Result = nullptr;
    Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
    if (AccessToken.IsValid()) Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
    Gs2::Inventory::Request::FConsumeBigItemByUserIdRequestPtr Prepared = nullptr;
    if (Request.IsValid()) Prepared = MakeShared<Gs2::Inventory::Request::FConsumeBigItemByUserIdRequest>(*Request);
    if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Domain->Cache.IsValid() ||
        !Token.IsValid() || !Prepared.IsValid() || !Token->GetUserId().IsSet() ||
        Token->GetUserId().Get(FString()).IsEmpty()) return nullptr;
    if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}"))
        Prepared->WithUserId(Token->GetUserId());
    if (!Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != Token->GetUserId().Get(FString()) ||
        !Prepared->GetNamespaceName().IsSet() || !Prepared->GetInventoryName().IsSet() ||
        !Prepared->GetItemName().IsSet() || !Prepared->GetConsumeCount().IsSet()) return nullptr;

    const auto NamespaceName = Prepared->GetNamespaceName();
    const auto InventoryName = Prepared->GetInventoryName();
    const auto ItemName = Prepared->GetItemName();
    const auto UserId = Token->GetUserId();
    const auto TimeOffset = Token->GetTimeOffset();
    const FString ExpectedId = Private::BigItemExpectedId(
        Domain->RestSession->RegionName(), Domain->RestSession->OwnerId(),
        NamespaceName.Get(FString()), UserId.Get(FString()), InventoryName.Get(FString()), ItemName.Get(FString())
    );
    Gs2::Inventory::Model::FBigItemPtr Cached;
    const bool Found = Gs2::Inventory::Model::Cache::FBigItemCache::TryGet(
        Domain->Cache, NamespaceName, UserId, InventoryName, ItemName, TimeOffset, &Cached
    );
    if (!Found || !Cached.IsValid() || !Cached->GetItemId().IsSet() || Cached->GetItemId().Get(FString()) != ExpectedId ||
        !Cached->GetUserId().IsSet() || Cached->GetUserId().Get(FString()) != UserId.Get(FString()) ||
        !Cached->GetItemName().IsSet() || Cached->GetItemName().Get(FString()) != ItemName.Get(FString()) ||
        !Cached->GetCount().IsSet()) return nullptr;
    FBigInteger PreparedCount;
    FBigInteger CachedCount;
    if (!FBigInteger::TryParse(Prepared->GetConsumeCount().Get(FString()), PreparedCount) ||
        !FBigInteger::TryParse(Cached->GetCount().Get(FString()), CachedCount)) return nullptr;
    const auto PreparedResult = FBigInteger::Subtract(CachedCount, PreparedCount);
    if (PreparedResult.IsNegative()) return nullptr;

    const auto Commit = MakeShared<FBigItemMutationSpeculativeCommit>(
        Domain->Cache, NamespaceName, UserId.Get(FString()), InventoryName.Get(FString()), ItemName.Get(FString()),
        TimeOffset, ExpectedId, Cached->GetRevision(), false,
        [ConsumeCount = Prepared->GetConsumeCount().Get(FString())](const Gs2::Inventory::Model::FBigItemPtr& Current)
        {
            FBigInteger Left;
            FBigInteger Right;
            if (!Current.IsValid() || !Current->GetCount().IsSet() ||
                !FBigInteger::TryParse(Current->GetCount().Get(FString()), Left) ||
                !FBigInteger::TryParse(ConsumeCount, Right)) return Gs2::Inventory::Model::FBigItemPtr(nullptr);
            const auto Count = FBigInteger::Subtract(Left, Right);
            if (Count.IsNegative()) return Gs2::Inventory::Model::FBigItemPtr(nullptr);
            return MakeShared<Gs2::Inventory::Model::FBigItem>(*Current)->WithCount(Count.ToString())->WithRevision(0);
        }
    );
    *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateComposable(
        Commit->CompositionKey(),
        [Commit](const TSharedPtr<void>& Current, const bool HasCurrent, TSharedPtr<void>& Next)
        { return Commit->TryCompose(Current, HasCurrent, Next); },
        [Commit](const TSharedPtr<void>& State) { Commit->Commit(State); }
    );
    return nullptr;
}

TSharedPtr<FAsyncTask<FConsumeBigItemByUserIdSpeculativeExecutor::FCommitTask>> FConsumeBigItemByUserIdSpeculativeExecutor::Execute(
    const Gs2::Core::Domain::FGs2Ptr& Domain,
    const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
    const Gs2::Inventory::Request::FConsumeBigItemByUserIdRequestPtr& Request
)
{
    return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
}

Gs2::Inventory::Request::FConsumeBigItemByUserIdRequestPtr FConsumeBigItemByUserIdSpeculativeExecutor::Rate(
    const Gs2::Inventory::Request::FConsumeBigItemByUserIdRequestPtr& Request, const double Rate
)
{
    if (!Request.IsValid()) return nullptr;
    const auto Count = FBigInteger::ParseCountOrOne(Request->GetConsumeCount());
    FBigInteger Result;
    if (!FBigInteger::TryApplyRate(Count, Rate, Result)) return nullptr;
    Request->WithConsumeCount(Result.ToString());
    return Request;
}

Gs2::Inventory::Request::FConsumeBigItemByUserIdRequestPtr FConsumeBigItemByUserIdSpeculativeExecutor::Rate(
    const Gs2::Inventory::Request::FConsumeBigItemByUserIdRequestPtr& Request, TBigInt<1024, false> Rate
)
{
    if (!Request.IsValid()) return nullptr;
    const auto Count = FBigInteger::ParseCountOrOne(Request->GetConsumeCount());
    FBigInteger Result;
    if (!FBigInteger::TryApplyRate(Count, Rate.ToString(), Result)) return nullptr;
    Request->WithConsumeCount(Result.ToString());
    return Request;
}
}
