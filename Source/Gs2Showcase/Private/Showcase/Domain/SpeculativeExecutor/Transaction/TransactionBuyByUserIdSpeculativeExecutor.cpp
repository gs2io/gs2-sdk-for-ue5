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
#include "Showcase/Domain/SpeculativeExecutor/Transaction/BuyByUserIdSpeculativeExecutor.h"

#include "Auth/Model/AccessToken.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/ActionConfig.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Core/Domain/Model/IssueTransactionEvent.h"
#include "Showcase/Model/Cache/DisplayItem.h"
#include "Showcase/Model/Config.h"
#include "Showcase/Model/DisplayItem.h"
#include "Showcase/Model/SalesItem.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace Gs2::Showcase::Domain::Transaction::SpeculativeExecutor
{
    namespace
    {
        FString ShowcaseSnapshot(
            const Gs2::Showcase::Model::FDisplayItemPtr& Item
        )
        {
            if (!Item.IsValid()) return FString();
            FString Body;
            const TSharedRef<TJsonWriter<TCHAR>> Writer =
                TJsonWriterFactory<TCHAR>::Create(&Body);
            FJsonSerializer::Serialize(Item->ToJson().ToSharedRef(), Writer);
            return Body;
        }
    }

    FString FBuyByUserIdSpeculativeExecutor::Action()
    {
        return TEXT("Gs2Showcase:BuyByUserId");
    }

    FBuyByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Showcase::Domain::FGs2ShowcaseDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Showcase::Request::FBuyByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {
    }

    FBuyByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr
    FBuyByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<
            Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
        if (AccessToken.IsValid())
        {
            Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        }

        Gs2::Showcase::Request::FBuyByUserIdRequestPtr Prepared = nullptr;
        if (Request.IsValid())
        {
            Prepared =
                Gs2::Showcase::Request::FBuyByUserIdRequest::FromJson(
                    Request->ToJson()
                );
        }
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() ||
            !Domain->Cache.IsValid() || !Token.IsValid() ||
            !Prepared.IsValid() || !Token->GetUserId().IsSet() ||
            Token->GetUserId().Get(FString()).IsEmpty())
        {
            return nullptr;
        }

        if (Prepared->GetUserId().IsSet() &&
            Prepared->GetUserId().Get(FString()) == TEXT("#{userId}"))
        {
            Prepared->WithUserId(Token->GetUserId());
        }
        if (!Prepared->GetUserId().IsSet() ||
            Prepared->GetUserId().Get(FString()) !=
                Token->GetUserId().Get(FString()) ||
            !Prepared->GetNamespaceName().IsSet() ||
            !Prepared->GetShowcaseName().IsSet() ||
            !Prepared->GetDisplayItemId().IsSet() ||
            !Prepared->GetQuantity().IsSet() ||
            Prepared->GetQuantity().Get(0) <= 0)
        {
            return nullptr;
        }

        const auto Namespace = Prepared->GetNamespaceName();
        const auto Showcase = Prepared->GetShowcaseName();
        const auto ItemId = Prepared->GetDisplayItemId();
        const auto UserId = Token->GetUserId();
        const auto Offset = Token->GetTimeOffset();
        Gs2::Showcase::Model::FDisplayItemPtr Item = nullptr;
        if (!Gs2::Showcase::Model::Cache::FDisplayItemCache::TryGet(
                Domain->Cache, Namespace, UserId, Showcase, ItemId, Offset, &Item
            ) ||
            !Item.IsValid() || !Item->GetDisplayItemId().IsSet() ||
            *Item->GetDisplayItemId() != ItemId.Get(FString()) ||
            !Item->GetType().IsSet() ||
            *Item->GetType() != TEXT("salesItem") ||
            !Item->GetSalesItem().IsValid())
        {
            return nullptr;
        }

        const auto SourcesConsume = Item->GetSalesItem()->GetConsumeActions();
        const auto SourcesAcquire = Item->GetSalesItem()->GetAcquireActions();
        const int64 SourceCount =
            (SourcesConsume.IsValid() ? SourcesConsume->Num() : 0) +
            (SourcesAcquire.IsValid() ? SourcesAcquire->Num() : 0);
        if (SourceCount == 0 ||
            SourceCount * Prepared->GetQuantity().Get(0) > 4096)
        {
            return nullptr;
        }

        const auto Consumes =
            MakeShared<TArray<Gs2::Core::Model::FConsumeActionPtr>>();
        const auto Acquires =
            MakeShared<TArray<Gs2::Core::Model::FAcquireActionPtr>>();
        for (int32 N = 0; N < Prepared->GetQuantity().Get(0); ++N)
        {
            if (SourcesConsume.IsValid())
            {
                for (const auto& Source : *SourcesConsume)
                {
                    if (!Source.IsValid()) continue;
                    Gs2::Core::Model::FConsumeActionPtr SourceAction =
                        MakeShared<Gs2::Core::Model::FConsumeAction>(*Source);
                    auto Action =
                        Gs2::Core::Domain::SpeculativeExecutor::ApplyConfig(
                            SourceAction, TOptional<FString>(TEXT("userId")),
                            UserId
                        );
                    if (Prepared->GetConfig().IsValid())
                    {
                        for (const auto& Config : *Prepared->GetConfig())
                        {
                            if (Config.IsValid())
                            {
                                Action =
                                    Gs2::Core::Domain::SpeculativeExecutor::ApplyConfig(
                                        Action, Config->GetKey(), Config->GetValue()
                                    );
                            }
                        }
                    }
                    if (Action.IsValid()) Consumes->Add(Action);
                }
            }
            if (SourcesAcquire.IsValid())
            {
                for (const auto& Source : *SourcesAcquire)
                {
                    if (!Source.IsValid()) continue;
                    Gs2::Core::Model::FAcquireActionPtr SourceAction =
                        MakeShared<Gs2::Core::Model::FAcquireAction>(*Source);
                    auto Action =
                        Gs2::Core::Domain::SpeculativeExecutor::ApplyConfig(
                            SourceAction, TOptional<FString>(TEXT("userId")),
                            UserId
                        );
                    if (Prepared->GetConfig().IsValid())
                    {
                        for (const auto& Config : *Prepared->GetConfig())
                        {
                            if (Config.IsValid())
                            {
                                Action =
                                    Gs2::Core::Domain::SpeculativeExecutor::ApplyConfig(
                                        Action, Config->GetKey(), Config->GetValue()
                                    );
                            }
                        }
                    }
                    if (Action.IsValid()) Acquires->Add(Action);
                }
            }
        }
        if (Consumes->Num() == 0 && Acquires->Num() == 0) return nullptr;

        const auto Event =
            MakeShared<Gs2::Core::Domain::Model::FIssueTransactionEvent>(
                Token, Consumes, Acquires, TBigInt<1024, false>(1)
            );
        Service->OnIssueTransaction.Broadcast(Event);
        if (Event->GetError().IsValid()) return Event->GetError();
        const auto Child = Event->GetCommit();
        if (!Child.IsValid()) return nullptr;

        const FString Expected = ShowcaseSnapshot(Item);
        *Result =
            Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(
                MakeShared<TFunction<void()>>(
                    [Child] { (*Child)(); }
                ),
                [Domain = Domain, Namespace, UserId, Showcase, ItemId, Offset,
                    Expected]
                {
                    Gs2::Showcase::Model::FDisplayItemPtr Current = nullptr;
                    return
                        Gs2::Showcase::Model::Cache::FDisplayItemCache::TryGet(
                            Domain->Cache, Namespace, UserId, Showcase, ItemId,
                            Offset, &Current
                        ) &&
                        ShowcaseSnapshot(Current) == Expected;
                }
            );
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBuyByUserIdSpeculativeExecutor::FCommitTask>>
    FBuyByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Showcase::Domain::FGs2ShowcaseDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Showcase::Request::FBuyByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(
            Domain, Service, AccessToken, Request
        );
    }
}
