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

#include "Enhance/Domain/SpeculativeExecutor/Transaction/StartByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Auth/Model/AccessToken.h"
#include "Core/Domain/SpeculativeExecutor/ActionConfig.h"
#include "Core/Domain/Model/IssueTransactionEvent.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Enhance/Model/Material.h"
#include "Inventory/Model/ConsumeCount.h"
#include "Inventory/Request/ConsumeItemSetByUserIdRequest.h"
#include "Inventory/Request/ConsumeSimpleItemsByUserIdRequest.h"
#include "Internationalization/Regex.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace Gs2::Enhance::Domain::Transaction::SpeculativeExecutor
{
    namespace
    {
        FString SerializeStartRequest(const TSharedPtr<FJsonObject>& Object)
        {
            if (!Object.IsValid()) return FString();
            FString Body;
            const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Body);
            FJsonSerializer::Serialize(Object.ToSharedRef(), Writer);
            return Body;
        }

        Gs2::Core::Model::FConsumeActionPtr BuildStartConsumeAction(
            const Gs2::Auth::Model::FAccessTokenPtr& Token,
            const Gs2::Enhance::Model::FMaterialPtr& Material
        )
        {
            if (!Token.IsValid() || !Token->GetUserId().IsSet() || !Material.IsValid() ||
                !Material->GetMaterialItemSetId().IsSet() || !Material->GetCount().IsSet())
            {
                return nullptr;
            }
            const FString ItemSetId = Material->GetMaterialItemSetId().GetValue();
            const int64 Count = Material->GetCount().GetValue();
            const auto ItemSetPattern = FRegexPattern(
                TEXT("^grn:gs2:[-_.{}a-zA-Z0-9]+:[-_.{}a-zA-Z0-9]+:inventory:([-_.{}a-zA-Z0-9]+):user:[-_.{}a-zA-Z0-9]+:inventory:([-_.{}a-zA-Z0-9]+):item:([-_.{}a-zA-Z0-9]+):itemSet:([-_.{}a-zA-Z0-9]+)$"));
            FRegexMatcher ItemSetMatcher(ItemSetPattern, ItemSetId);
            if (ItemSetMatcher.FindNext())
            {
                const auto Request = MakeShared<Gs2::Inventory::Request::FConsumeItemSetByUserIdRequest>()
                    ->WithNamespaceName(ItemSetMatcher.GetCaptureGroup(1))
                    ->WithInventoryName(ItemSetMatcher.GetCaptureGroup(2))
                    ->WithUserId(Token->GetUserId())
                    ->WithItemName(ItemSetMatcher.GetCaptureGroup(3))
                    ->WithItemSetName(ItemSetMatcher.GetCaptureGroup(4))
                    ->WithConsumeCount(Count);
                return MakeShared<Gs2::Core::Model::FConsumeAction>()
                    ->WithAction(FString("Gs2Inventory:ConsumeItemSetByUserId"))
                    ->WithRequest(SerializeStartRequest(Request->ToJson()));
            }

            const auto SimplePattern = FRegexPattern(
                TEXT("^grn:gs2:[-_.{}a-zA-Z0-9]+:[-_.{}a-zA-Z0-9]+:inventory:([-_.{}a-zA-Z0-9]+):user:[-_.{}a-zA-Z0-9]+:simple:inventory:([-_.{}a-zA-Z0-9]+):item:([-_.{}a-zA-Z0-9]+)$"));
            FRegexMatcher SimpleMatcher(SimplePattern, ItemSetId);
            if (!SimpleMatcher.FindNext()) return nullptr;
            const auto ConsumeCounts = MakeShared<TArray<Gs2::Inventory::Model::FConsumeCountPtr>>();
            ConsumeCounts->Add(
                MakeShared<Gs2::Inventory::Model::FConsumeCount>()
                    ->WithItemName(SimpleMatcher.GetCaptureGroup(3))
                    ->WithCount(Count)
            );
            const auto Request = MakeShared<Gs2::Inventory::Request::FConsumeSimpleItemsByUserIdRequest>()
                ->WithNamespaceName(SimpleMatcher.GetCaptureGroup(1))
                ->WithInventoryName(SimpleMatcher.GetCaptureGroup(2))
                ->WithUserId(Token->GetUserId())
                ->WithConsumeCounts(ConsumeCounts);
            return MakeShared<Gs2::Core::Model::FConsumeAction>()
                ->WithAction(FString("Gs2Inventory:ConsumeSimpleItemsByUserId"))
                ->WithRequest(SerializeStartRequest(Request->ToJson()));
        }
    }

    FString FStartByUserIdSpeculativeExecutor::Action() {
        return "Gs2Enhance:StartByUserId";
    }

    FStartByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Enhance::Domain::FGs2EnhanceDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Enhance::Request::FStartByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {
    }

    FStartByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStartByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result)
    {
        if (!Result.IsValid() || !Domain.IsValid() || !Domain->RestSession.IsValid() ||
            !AccessToken.IsValid() || !Request.IsValid())
        {
            if (Result.IsValid()) *Result = nullptr;
            return nullptr;
        }
        const auto PreparedAccessToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        const auto PreparedRequest = Gs2::Enhance::Request::FStartByUserIdRequest::FromJson(Request->ToJson());
        if (!PreparedRequest.IsValid() || !PreparedAccessToken->GetUserId().IsSet() ||
            PreparedAccessToken->GetUserId()->IsEmpty())
        {
            *Result = nullptr;
            return nullptr;
        }
        if (PreparedRequest->GetUserId().IsSet() && *PreparedRequest->GetUserId() == TEXT("#{userId}"))
        {
            PreparedRequest->WithUserId(PreparedAccessToken->GetUserId());
        }
        if (!PreparedRequest->GetUserId().IsSet() ||
            *PreparedRequest->GetUserId() != *PreparedAccessToken->GetUserId())
        {
            *Result = nullptr;
            return nullptr;
        }

        const auto ConsumeActions = MakeShared<TArray<Gs2::Core::Model::FConsumeActionPtr>>();
        if (const auto Materials = PreparedRequest->GetMaterials(); Materials.IsValid())
        {
            for (const auto& Material : *Materials)
            {
                Gs2::Core::Model::FConsumeActionPtr Action = BuildStartConsumeAction(PreparedAccessToken, Material);
                if (const auto Config = PreparedRequest->GetConfig(); Config.IsValid())
                {
                    for (const auto& Entry : *Config)
                    {
                        if (!Entry.IsValid())
                        {
                            Action = nullptr;
                            break;
                        }
                        Action = Gs2::Core::Domain::SpeculativeExecutor::ApplyConfig(
                            Gs2::Core::Model::FConsumeActionPtr(Action),
                            TOptional<FString>(Entry->GetKey()), TOptional<FString>(Entry->GetValue()));
                    }
                }
                if (Action.IsValid()) ConsumeActions->Add(Action);
            }
        }
        if (ConsumeActions->Num() == 0)
        {
            *Result = nullptr;
            return nullptr;
        }
        const auto AcquireActions = MakeShared<TArray<Gs2::Core::Model::FAcquireActionPtr>>();
        const auto Event = MakeShared<Gs2::Core::Domain::Model::FIssueTransactionEvent>(
            PreparedAccessToken, ConsumeActions, AcquireActions, TBigInt<1024, false>(1));
        Service->OnIssueTransaction.Broadcast(Event);
        if (Event->GetError().IsValid()) return Event->GetError();
        const auto Commit = Event->GetCommit();
        if (!Commit.IsValid())
        {
            *Result = nullptr;
            return nullptr;
        }
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(Commit);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStartByUserIdSpeculativeExecutor::FCommitTask>> FStartByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Enhance::Domain::FGs2EnhanceDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Enhance::Request::FStartByUserIdRequestPtr& Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }
}
