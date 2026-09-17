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
#include "Grade/Domain/SpeculativeExecutor/Transaction/MultiplyAcquireActionsByUserIdSpeculativeExecutor.h"

#include "Auth/Model/AccessToken.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/ActionConfig.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Core/Domain/Model/IssueTransactionEvent.h"
#include "Grade/Model/Cache/GradeModel.h"
#include "Grade/Model/Cache/Status.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace Gs2::Grade::Domain::Transaction::SpeculativeExecutor
{
    namespace
    {
        FString GradeSnapshot(const Gs2::Grade::Model::FGradeModelPtr& Item)
        {
            if (!Item.IsValid()) return FString();
            FString Body;
            const TSharedRef<TJsonWriter<TCHAR>> Writer =
                TJsonWriterFactory<TCHAR>::Create(&Body);
            FJsonSerializer::Serialize(Item->ToJson().ToSharedRef(), Writer);
            return Body;
        }

        FString GradeStatusSnapshot(const Gs2::Grade::Model::FStatusPtr& Item)
        {
            if (!Item.IsValid()) return FString();
            FString Body;
            const TSharedRef<TJsonWriter<TCHAR>> Writer =
                TJsonWriterFactory<TCHAR>::Create(&Body);
            FJsonSerializer::Serialize(Item->ToJson().ToSharedRef(), Writer);
            return Body;
        }

        bool GradeUnitRate(
            const Gs2::Grade::Model::FAcquireActionRatePtr& Definition,
            const int32 Index
        )
        {
            if (!Definition.IsValid() || Index < 0 || !Definition->GetMode().IsSet())
            {
                return false;
            }
            if (*Definition->GetMode() == TEXT("double"))
            {
                return Definition->GetRates().IsValid() &&
                    Definition->GetRates()->IsValidIndex(Index) &&
                    (*Definition->GetRates())[Index] == 1.0;
            }
            return *Definition->GetMode() == TEXT("big") &&
                Definition->GetBigRates().IsValid() &&
                Definition->GetBigRates()->IsValidIndex(Index) &&
                (*Definition->GetBigRates())[Index] == TEXT("1");
        }
    }

    FString FMultiplyAcquireActionsByUserIdSpeculativeExecutor::Action()
    {
        return TEXT("Gs2Grade:MultiplyAcquireActionsByUserId");
    }

    FMultiplyAcquireActionsByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Grade::Domain::FGs2GradeDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Grade::Request::FMultiplyAcquireActionsByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {
    }

    FMultiplyAcquireActionsByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr
    FMultiplyAcquireActionsByUserIdSpeculativeExecutor::FCommitTask::Action(
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

        Gs2::Grade::Request::FMultiplyAcquireActionsByUserIdRequestPtr Prepared =
            nullptr;
        if (Request.IsValid())
        {
            Prepared =
                Gs2::Grade::Request::FMultiplyAcquireActionsByUserIdRequest::FromJson(
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
            !Prepared->GetGradeName().IsSet() ||
            !Prepared->GetPropertyId().IsSet() ||
            !Prepared->GetRateName().IsSet() ||
            !Prepared->GetAcquireActions().IsValid())
        {
            return nullptr;
        }

        auto PropertyId = Prepared->GetPropertyId();
        PropertyId = TOptional<FString>(
            PropertyId.Get(FString())
                .Replace(TEXT("{region}"), *Domain->RestSession->RegionName())
                .Replace(TEXT("{ownerId}"), *Domain->RestSession->OwnerId())
                .Replace(TEXT("{userId}"), *Token->GetUserId().Get(FString()))
        );
        Prepared->WithPropertyId(PropertyId);

        const auto Namespace = Prepared->GetNamespaceName();
        const auto Name = Prepared->GetGradeName();
        const auto UserId = Token->GetUserId();
        const auto Offset = Token->GetTimeOffset();
        const FString ModelId = FString::Printf(
            TEXT("grn:gs2:%s:%s:grade:%s:model:%s"),
            *Domain->RestSession->RegionName(),
            *Domain->RestSession->OwnerId(),
            *Namespace.Get(FString()),
            *Name.Get(FString())
        );
        const FString StatusId = FString::Printf(
            TEXT("grn:gs2:%s:%s:grade:%s:user:%s:gradeModel:%s:property:%s"),
            *Domain->RestSession->RegionName(),
            *Domain->RestSession->OwnerId(),
            *Namespace.Get(FString()),
            *UserId.Get(FString()),
            *Name.Get(FString()),
            *PropertyId.Get(FString())
        );

        Gs2::Grade::Model::FGradeModelPtr Model = nullptr;
        Gs2::Grade::Model::FStatusPtr Status = nullptr;
        if (!Gs2::Grade::Model::Cache::FGradeModelCache::TryGet(
                Domain->Cache, Namespace, Name, TOptional<int32>(), &Model
            ) ||
            !Gs2::Grade::Model::Cache::FStatusCache::TryGet(
                Domain->Cache, Namespace, UserId, Name, PropertyId, Offset, &Status
            ) ||
            !Model.IsValid() || !Status.IsValid() ||
            !Model->GetGradeModelId().IsSet() ||
            *Model->GetGradeModelId() != ModelId ||
            !Model->GetName().IsSet() ||
            *Model->GetName() != Name.Get(FString()) ||
            !Status->GetStatusId().IsSet() ||
            *Status->GetStatusId() != StatusId ||
            !Status->GetUserId().IsSet() ||
            *Status->GetUserId() != UserId.Get(FString()) ||
            !Status->GetGradeName().IsSet() ||
            *Status->GetGradeName() != Name.Get(FString()) ||
            !Status->GetPropertyId().IsSet() ||
            *Status->GetPropertyId() != PropertyId.Get(FString()) ||
            !Status->GetGradeValue().IsSet() ||
            *Status->GetGradeValue() <= 0 ||
            *Status->GetGradeValue() > MAX_int32)
        {
            return nullptr;
        }

        Gs2::Grade::Model::FAcquireActionRatePtr Rate = nullptr;
        if (Model->GetAcquireActionRates().IsValid())
        {
            for (const auto& Candidate : *Model->GetAcquireActionRates())
            {
                if (Candidate.IsValid() && Candidate->GetName().IsSet() &&
                    *Candidate->GetName() ==
                        Prepared->GetRateName().Get(FString()))
                {
                    Rate = Candidate;
                    break;
                }
            }
        }
        if (!GradeUnitRate(
                Rate, static_cast<int32>(*Status->GetGradeValue()) - 1
            ))
        {
            return nullptr;
        }

        const auto Consumes =
            MakeShared<TArray<Gs2::Core::Model::FConsumeActionPtr>>();
        const auto Acquires =
            MakeShared<TArray<Gs2::Core::Model::FAcquireActionPtr>>();
        for (const auto& Source : *Prepared->GetAcquireActions())
        {
            if (Source.IsValid())
            {
                Gs2::Core::Model::FAcquireActionPtr SourceAction =
                    MakeShared<Gs2::Core::Model::FAcquireAction>(*Source);
                const auto Action =
                    Gs2::Core::Domain::SpeculativeExecutor::ApplyConfig(
                        SourceAction, TOptional<FString>(TEXT("userId")), UserId
                    );
                if (Action.IsValid()) Acquires->Add(Action);
            }
        }
        if (Acquires->Num() == 0) return nullptr;

        const auto Event =
            MakeShared<Gs2::Core::Domain::Model::FIssueTransactionEvent>(
                Token, Consumes, Acquires, TBigInt<1024, false>(1)
            );
        Service->OnIssueTransaction.Broadcast(Event);
        if (Event->GetError().IsValid()) return Event->GetError();
        const auto Child = Event->GetCommit();
        if (!Child.IsValid()) return nullptr;

        const FString ExpectedModel = GradeSnapshot(Model);
        const FString ExpectedStatus = GradeStatusSnapshot(Status);
        *Result =
            Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(
                MakeShared<TFunction<void()>>([Child] { (*Child)(); }),
                [Domain = Domain, Namespace, Name, UserId, PropertyId, Offset,
                    ExpectedModel, ExpectedStatus]
                {
                    Gs2::Grade::Model::FGradeModelPtr CurrentModel = nullptr;
                    Gs2::Grade::Model::FStatusPtr CurrentStatus = nullptr;
                    return
                        Gs2::Grade::Model::Cache::FGradeModelCache::TryGet(
                            Domain->Cache, Namespace, Name, TOptional<int32>(),
                            &CurrentModel
                        ) &&
                        Gs2::Grade::Model::Cache::FStatusCache::TryGet(
                            Domain->Cache, Namespace, UserId, Name, PropertyId,
                            Offset, &CurrentStatus
                        ) &&
                        GradeSnapshot(CurrentModel) == ExpectedModel &&
                        GradeStatusSnapshot(CurrentStatus) == ExpectedStatus;
                }
            );
        return nullptr;
    }

    TSharedPtr<FAsyncTask<
        FMultiplyAcquireActionsByUserIdSpeculativeExecutor::FCommitTask>>
    FMultiplyAcquireActionsByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Grade::Domain::FGs2GradeDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Grade::Request::FMultiplyAcquireActionsByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(
            Domain, Service, AccessToken, Request
        );
    }
}
