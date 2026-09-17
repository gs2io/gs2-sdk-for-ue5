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

#include "Formation/Domain/SpeculativeExecutor/Acquire/SetFormByUserIdSpeculativeExecutor.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Formation/Model/Cache/Form.h"

namespace Gs2::Formation::Domain::SpeculativeExecutor
{
namespace
{
    bool SetFormNamesEqual(const TOptional<FString>& Left, const TOptional<FString>& Right)
    {
        return Left.IsSet() == Right.IsSet() && (!Left.IsSet() || Left.Get(FString()) == Right.Get(FString()));
    }

    bool SetFormExpected(
        const Gs2::Formation::Model::FFormPtr& Item,
        const FString& ExpectedId,
        const FString& MoldModelName,
        const int32 Index
    )
    {
        return Item.IsValid() && Item->GetFormId().IsSet() && Item->GetFormId().Get(FString()) == ExpectedId &&
            Item->GetName().IsSet() && Item->GetName().Get(FString()) == MoldModelName &&
            Item->GetIndex().IsSet() && Item->GetIndex().Get(0) == Index && Item->GetSlots().IsValid();
    }

    class FSetFormMutationSpeculativeCommit final
    {
        const Gs2::Core::Domain::FCacheDatabasePtr Cache;
        const TOptional<FString> NamespaceName;
        const FString UserId;
        const FString MoldModelName;
        const TOptional<int32> Index;
        const TOptional<int32> TimeOffset;
        const FString ExpectedId;
        const TOptional<int64> PreparedRevision;
        const TSharedPtr<TArray<Gs2::Formation::Model::FSlotPtr>> RequestedSlots;

        bool IsExpected(const Gs2::Formation::Model::FFormPtr& Item) const
        {
            return SetFormExpected(Item, ExpectedId, MoldModelName, Index.Get(0));
        }

    public:
        FSetFormMutationSpeculativeCommit(
            const Gs2::Core::Domain::FCacheDatabasePtr& InCache,
            const TOptional<FString>& InNamespaceName,
            const FString& InUserId,
            const FString& InMoldModelName,
            const TOptional<int32>& InIndex,
            const TOptional<int32>& InTimeOffset,
            const FString& InExpectedId,
            const TOptional<int64>& InPreparedRevision,
            const TSharedPtr<TArray<Gs2::Formation::Model::FSlotPtr>>& InRequestedSlots
        ):
            Cache(InCache), NamespaceName(InNamespaceName), UserId(InUserId), MoldModelName(InMoldModelName),
            Index(InIndex), TimeOffset(InTimeOffset), ExpectedId(InExpectedId), PreparedRevision(InPreparedRevision),
            RequestedSlots(InRequestedSlots)
        {
        }

        FString CompositionKey() const
        {
            return Gs2::Formation::Model::Cache::FFormCache::CreateCacheParentKey(
                NamespaceName, UserId, MoldModelName, TimeOffset
            ) + TEXT(":") + Gs2::Formation::Model::Cache::FFormCache::CreateCacheKey(Index);
        }

        bool TryCompose(const TSharedPtr<void>& Current, const bool HasCurrent, TSharedPtr<void>& Next) const
        {
            try
            {
                Gs2::Formation::Model::FFormPtr Form;
                if (HasCurrent)
                {
                    Form = StaticCastSharedPtr<Gs2::Formation::Model::FForm>(Current);
                }
                else if (!Gs2::Formation::Model::Cache::FFormCache::TryGet(
                    Cache, NamespaceName, UserId, MoldModelName, Index, TimeOffset, &Form
                ) || !IsExpected(Form))
                {
                    Next = nullptr;
                    return false;
                }
                if (!IsExpected(Form))
                {
                    Next = nullptr;
                    return false;
                }
                if (!HasCurrent && Form->GetRevision().IsSet() && Form->GetRevision().Get(0) > 0 &&
                    (!PreparedRevision.IsSet() || Form->GetRevision().Get(0) != PreparedRevision.Get(0)))
                {
                    Next = nullptr;
                    return false;
                }
                auto Slots = MakeShared<TArray<Gs2::Formation::Model::FSlotPtr>>();
                for (const auto& Existing : *Form->GetSlots())
                {
                    if (!Existing.IsValid()) { Next = nullptr; return false; }
                    bool Removed = false;
                    for (const auto& Requested : *RequestedSlots)
                    {
                        if (!Requested.IsValid()) { Next = nullptr; return false; }
                        if (SetFormNamesEqual(Existing->GetName(), Requested->GetName())) { Removed = true; break; }
                    }
                    if (!Removed) Slots->Add(MakeShared<Gs2::Formation::Model::FSlot>(*Existing));
                }
                for (const auto& Requested : *RequestedSlots)
                {
                    if (!Requested.IsValid()) { Next = nullptr; return false; }
                    if (Requested->GetPropertyId().IsSet())
                        Slots->Add(MakeShared<Gs2::Formation::Model::FSlot>(*Requested));
                }
                Gs2::Formation::Model::FFormPtr Changed = MakeShared<Gs2::Formation::Model::FForm>(*Form);
                Changed->WithSlots(Slots)->WithRevision(0);
                if (!IsExpected(Changed)) { Next = nullptr; return false; }
                Next = Changed;
                return true;
            }
            catch (...)
            {
                Next = nullptr;
                return false;
            }
        }

        void Commit(const TSharedPtr<void>& State) const
        {
            try
            {
                const auto Item = StaticCastSharedPtr<Gs2::Formation::Model::FForm>(State);
                if (!IsExpected(Item) || !Item->GetRevision().IsSet() || Item->GetRevision().Get(0) != 0) return;
                Cache->Put(
                    Gs2::Formation::Model::FForm::TypeName,
                    Gs2::Formation::Model::Cache::FFormCache::CreateCacheParentKey(
                        NamespaceName, UserId, MoldModelName, TimeOffset
                    ),
                    Gs2::Formation::Model::Cache::FFormCache::CreateCacheKey(Index), Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            catch (...) { }
        }
    };
}

FString FSetFormByUserIdSpeculativeExecutor::Action()
{
    return FString("Gs2Formation:SetFormByUserId");
}

Gs2::Core::Model::FGs2ErrorPtr FSetFormByUserIdSpeculativeExecutor::Transform(
    const Gs2::Core::Domain::FGs2Ptr&, const Gs2::Auth::Model::FAccessTokenPtr&,
    const Gs2::Formation::Request::FSetFormByUserIdRequestPtr&, Gs2::Formation::Model::FFormPtr
)
{
    return nullptr;
}

FSetFormByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
    const Gs2::Core::Domain::FGs2Ptr& Domain,
    const Gs2::Formation::Domain::FGs2FormationDomainPtr& Service,
    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
    const Gs2::Formation::Request::FSetFormByUserIdRequestPtr& Request
): Domain(Domain), Service(Service), AccessToken(AccessToken), Request(Request) {}

FSetFormByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(const FCommitTask& From):
    Domain(From.Domain), Service(From.Service), AccessToken(From.AccessToken), Request(From.Request) {}

Gs2::Core::Model::FGs2ErrorPtr FSetFormByUserIdSpeculativeExecutor::FCommitTask::Action(
    TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
)
{
    *Result = nullptr;
    Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
    if (AccessToken.IsValid()) Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
    Gs2::Formation::Request::FSetFormByUserIdRequestPtr Prepared = nullptr;
    if (Request.IsValid()) Prepared = MakeShared<Gs2::Formation::Request::FSetFormByUserIdRequest>(*Request);
    if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Token.IsValid() || !Prepared.IsValid() ||
        !Token->GetUserId().IsSet() || Token->GetUserId().Get(FString()).IsEmpty() ||
        !Prepared->GetIndex().IsSet() || !Prepared->GetSlots().IsValid() || Prepared->GetSlots()->Num() == 0) return nullptr;
    if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}"))
        Prepared->WithUserId(Token->GetUserId());
    if (!Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != Token->GetUserId().Get(FString())) return nullptr;
    auto RequestedSlots = MakeShared<TArray<Gs2::Formation::Model::FSlotPtr>>();
    for (const auto& Slot : *Prepared->GetSlots())
    {
        if (!Slot.IsValid()) return nullptr;
        RequestedSlots->Add(MakeShared<Gs2::Formation::Model::FSlot>(*Slot));
    }
    const auto NamespaceName = Prepared->GetNamespaceName();
    const auto MoldModelName = Prepared->GetMoldModelName();
    const auto UserId = Token->GetUserId();
    const auto Index = Prepared->GetIndex();
    const auto TimeOffset = Token->GetTimeOffset();
    const FString ExpectedId = FString::Printf(
        TEXT("grn:gs2:%s:%s:formation:%s:user:%s:mold:%s:form:%d"),
        *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName.Get(FString()),
        *UserId.Get(FString()), *MoldModelName.Get(FString()), Index.Get(0)
    );
    Gs2::Formation::Model::FFormPtr Form;
    if (!Gs2::Formation::Model::Cache::FFormCache::TryGet(
        Domain->Cache, NamespaceName, UserId, MoldModelName, Index, TimeOffset, &Form
    ) || !SetFormExpected(Form, ExpectedId, MoldModelName.Get(FString()), Index.Get(0))) return nullptr;
    const auto Commit = MakeShared<FSetFormMutationSpeculativeCommit>(
        Domain->Cache, NamespaceName, UserId.Get(FString()), MoldModelName.Get(FString()), Index, TimeOffset,
        ExpectedId, Form->GetRevision(), RequestedSlots
    );
    *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateComposable(
        Commit->CompositionKey(),
        [Commit](const TSharedPtr<void>& Current, const bool HasCurrent, TSharedPtr<void>& Next)
        { return Commit->TryCompose(Current, HasCurrent, Next); },
        [Commit](const TSharedPtr<void>& State) { Commit->Commit(State); }
    );
    return nullptr;
}

TSharedPtr<FAsyncTask<FSetFormByUserIdSpeculativeExecutor::FCommitTask>> FSetFormByUserIdSpeculativeExecutor::Execute(
    const Gs2::Core::Domain::FGs2Ptr& Domain,
    const Gs2::Formation::Domain::FGs2FormationDomainPtr& Service,
    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
    const Gs2::Formation::Request::FSetFormByUserIdRequestPtr& Request
)
{
    return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
}

Gs2::Formation::Request::FSetFormByUserIdRequestPtr FSetFormByUserIdSpeculativeExecutor::Rate(
    const Gs2::Formation::Request::FSetFormByUserIdRequestPtr& Request, const double
)
{ return Request; }

Gs2::Formation::Request::FSetFormByUserIdRequestPtr FSetFormByUserIdSpeculativeExecutor::Rate(
    const Gs2::Formation::Request::FSetFormByUserIdRequestPtr& Request, TBigInt<1024, false>
)
{ return Request; }
}
