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
#include "Formation/Domain/SpeculativeExecutor/Transaction/AcquireActionsToPropertyFormPropertiesSpeculativeExecutor.h"
#include "Formation/Domain/SpeculativeExecutor/Transaction/AcquireActionsToFormPropertiesSpeculativeExecutor.h"

#include "Auth/Model/AccessToken.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/ActionConfig.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Core/Domain/Model/IssueTransactionEvent.h"
#include "Formation/Model/Cache/PropertyForm.h"
#include "Formation/Model/Config.h"
#include "Formation/Model/Form.h"
#include "Formation/Model/Slot.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace Gs2::Formation::Domain::Transaction::SpeculativeExecutor
{
    namespace
    {
        FString PropertyFormSnapshot(
            const Gs2::Formation::Model::FPropertyFormPtr& Item
        )
        {
            if (!Item.IsValid()) return FString();
            auto Copy = MakeShared<Gs2::Formation::Model::FPropertyForm>(*Item);
            const auto Slots =
                MakeShared<TArray<Gs2::Formation::Model::FSlotPtr>>();
            if (Item->GetSlots().IsValid())
            {
                for (const auto& Slot : *Item->GetSlots())
                {
                    if (Slot.IsValid())
                    {
                        Slots->Add(
                            MakeShared<Gs2::Formation::Model::FSlot>(*Slot)
                        );
                    }
                }
            }
            Copy->WithSlots(Slots);
            FString Body;
            const TSharedRef<TJsonWriter<TCHAR>> Writer =
                TJsonWriterFactory<TCHAR>::Create(&Body);
            FJsonSerializer::Serialize(Copy->ToJson().ToSharedRef(), Writer);
            return Body;
        }
    }

    FString
    FAcquireActionsToPropertyFormPropertiesSpeculativeExecutor::Action()
    {
        return TEXT("Gs2Formation:AcquireActionsToPropertyFormProperties");
    }

    FAcquireActionsToPropertyFormPropertiesSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Formation::Domain::FGs2FormationDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Formation::Request::FAcquireActionsToPropertyFormPropertiesRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {
    }

    FAcquireActionsToPropertyFormPropertiesSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr
    FAcquireActionsToPropertyFormPropertiesSpeculativeExecutor::FCommitTask::Action(
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
        Gs2::Formation::Request::
            FAcquireActionsToPropertyFormPropertiesRequestPtr Prepared = nullptr;
        if (Request.IsValid())
        {
            Prepared =
                Gs2::Formation::Request::
                    FAcquireActionsToPropertyFormPropertiesRequest::FromJson(
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
            !Prepared->GetPropertyFormModelName().IsSet() ||
            !Prepared->GetPropertyId().IsSet() ||
            !Prepared->GetAcquireAction().IsValid())
        {
            return nullptr;
        }

        const auto Namespace = Prepared->GetNamespaceName();
        const auto UserId = Token->GetUserId();
        const auto Name = Prepared->GetPropertyFormModelName();
        const auto PropertyId = Prepared->GetPropertyId();
        const auto Offset = Token->GetTimeOffset();
        const FString ExpectedId = FString::Printf(
            TEXT("grn:gs2:%s:%s:formation:%s:user:%s:propertyForm:%s:%s"),
            *Domain->RestSession->RegionName(),
            *Domain->RestSession->OwnerId(),
            *Namespace.Get(FString()),
            *UserId.Get(FString()),
            *Name.Get(FString()),
            *PropertyId.Get(FString())
        );

        Gs2::Formation::Model::FPropertyFormPtr Item = nullptr;
        if (!Gs2::Formation::Model::Cache::FPropertyFormCache::TryGet(
                Domain->Cache, Namespace, UserId, Name, PropertyId, Offset, &Item
            ) ||
            !Item.IsValid() || !Item->GetFormId().IsSet() ||
            *Item->GetFormId() != ExpectedId || !Item->GetUserId().IsSet() ||
            *Item->GetUserId() != UserId.Get(FString()) ||
            !Item->GetName().IsSet() ||
            *Item->GetName() != Name.Get(FString()) ||
            !Item->GetPropertyId().IsSet() ||
            *Item->GetPropertyId() != PropertyId.Get(FString()) ||
            !Item->GetSlots().IsValid() ||
            !Prepared->GetAcquireAction()->GetAction().IsSet() ||
            *Prepared->GetAcquireAction()->GetAction() == FAcquireActionsToPropertyFormPropertiesSpeculativeExecutor::Action() ||
            *Prepared->GetAcquireAction()->GetAction() ==
                FAcquireActionsToFormPropertiesSpeculativeExecutor::Action())
        {
            return nullptr;
        }

        const auto Consumes =
            MakeShared<TArray<Gs2::Core::Model::FConsumeActionPtr>>();
        const auto Acquires =
            MakeShared<TArray<Gs2::Core::Model::FAcquireActionPtr>>();
        for (const auto& Slot : *Item->GetSlots())
        {
            if (!Slot.IsValid()) continue;
            Gs2::Core::Model::FAcquireActionPtr SourceAction =
                MakeShared<Gs2::Core::Model::FAcquireAction>(
                    *Prepared->GetAcquireAction()
                );
            auto Action =
                Gs2::Core::Domain::SpeculativeExecutor::ApplyConfig(
                    SourceAction,
                    TOptional<FString>(TEXT("propertyId")),
                    TOptional<FString>(Slot->GetPropertyId().Get(FString()))
                );
            Action = Gs2::Core::Domain::SpeculativeExecutor::ApplyConfig(
                Action, TOptional<FString>(TEXT("userId")), UserId
            );
            if (Prepared->GetConfig().IsValid())
            {
                for (const auto& Config : *Prepared->GetConfig())
                {
                    if (Config.IsValid() && Config->GetValue().IsSet())
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
        if (Item->GetSlots()->Num() > 0 && Acquires->Num() == 0)
        {
            return nullptr;
        }

        const auto Event =
            MakeShared<Gs2::Core::Domain::Model::FIssueTransactionEvent>(
                Token, Consumes, Acquires, TBigInt<1024, false>(1)
            );
        Service->OnIssueTransaction.Broadcast(Event);
        if (Event->GetError().IsValid()) return Event->GetError();
        const auto Child = Event->GetCommit();
        if (!Child.IsValid()) return nullptr;

        const FString Expected = PropertyFormSnapshot(Item);
        *Result =
            Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(
                MakeShared<TFunction<void()>>(
                    [Child] { (*Child)(); }
                ),
                [Domain = Domain, Namespace, UserId, Name, PropertyId, Offset,
                    Expected]
                {
                    Gs2::Formation::Model::FPropertyFormPtr Current = nullptr;
                    return
                        Gs2::Formation::Model::Cache::FPropertyFormCache::TryGet(
                            Domain->Cache, Namespace, UserId, Name, PropertyId,
                            Offset, &Current
                        ) &&
                        PropertyFormSnapshot(Current) == Expected;
                }
            );
        return nullptr;
    }

    TSharedPtr<FAsyncTask<
        FAcquireActionsToPropertyFormPropertiesSpeculativeExecutor::FCommitTask>>
    FAcquireActionsToPropertyFormPropertiesSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Formation::Domain::FGs2FormationDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Formation::Request::FAcquireActionsToPropertyFormPropertiesRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(
            Domain, Service, AccessToken, Request
        );
    }
}
