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

// ReSharper disable CppUnusedIncludeDirective

#include "Guild/Domain/Iterator/SearchGuildsByUserIdIterator.h"

#include "Core/Domain/Gs2.h"
#include "Guild/Domain/Model/Guild.h"
#include "Guild/Domain/Model/Namespace.h"

#include "Guild/Model/Cache/Guild.h"

namespace Gs2::Guild::Domain::Iterator
{

    FSearchGuildsByUserIdIterator::FSearchGuildsByUserIdIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Guild::FGs2GuildRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> GuildModelName,
        const TOptional<FString> UserId,
        const TOptional<FString> DisplayName,
        const TSharedPtr<TArray<int32>> Attributes1,
        const TSharedPtr<TArray<int32>> Attributes2,
        const TSharedPtr<TArray<int32>> Attributes3,
        const TSharedPtr<TArray<int32>> Attributes4,
        const TSharedPtr<TArray<int32>> Attributes5,
        const TSharedPtr<TArray<FString>> JoinPolicies,
        const TOptional<bool> IncludeFullMembersGuild,
        const TOptional<FString> OrderBy,
        const TOptional<FString> TimeOffsetToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client),
        NamespaceName(NamespaceName),
        GuildModelName(GuildModelName),
        UserId(UserId),
        DisplayName(DisplayName),
        Attributes1(Attributes1),
        Attributes2(Attributes2),
        Attributes3(Attributes3),
        Attributes4(Attributes4),
        Attributes5(Attributes5),
        JoinPolicies(JoinPolicies),
        IncludeFullMembersGuild(IncludeFullMembersGuild),
        OrderBy(OrderBy),
        TimeOffsetToken(TimeOffsetToken)
    {
    }

    FSearchGuildsByUserIdIterator::FSearchGuildsByUserIdIterator(
        const FSearchGuildsByUserIdIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        GuildModelName(From.GuildModelName),
        UserId(From.UserId),
        DisplayName(From.DisplayName),
        Attributes1(From.Attributes1),
        Attributes2(From.Attributes2),
        Attributes3(From.Attributes3),
        Attributes4(From.Attributes4),
        Attributes5(From.Attributes5),
        JoinPolicies(From.JoinPolicies),
        IncludeFullMembersGuild(From.IncludeFullMembersGuild),
        OrderBy(From.OrderBy),
        TimeOffsetToken(From.TimeOffsetToken)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSearchGuildsByUserIdIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Guild::Model::FGuild>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FSearchGuildsByUserIdIterator::FIterator::FIterator(
        const TSharedRef<FSearchGuildsByUserIdIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FSearchGuildsByUserIdIterator::FIterator& FSearchGuildsByUserIdIterator::FIterator::operator++()
    {
        

        if (bEnd) return *this;

        if (ErrorValue && bLast)
        {
            bEnd = true;
            return *this;
        }

        if (RangeIteratorOpt) ++*RangeIteratorOpt;

        if (!RangeIteratorOpt || (!*RangeIteratorOpt && !bLast))
        {
            const auto ListParentKey = Gs2::Guild::Model::Cache::FGuildCache::CreateCacheParentKey(
                Self->NamespaceName,
                TOptional<int32>()
            );
            if (!RangeIteratorOpt && (!Self->UserId.IsSet() && !Self->Attributes1.IsValid() && !Self->Attributes2.IsValid() && !Self->Attributes3.IsValid() && !Self->Attributes4.IsValid() && !Self->Attributes5.IsValid() && !Self->JoinPolicies.IsValid() && !Self->IncludeFullMembersGuild.IsSet() && !Self->OrderBy.IsSet()))
            {
                Range = Self->Gs2->Cache->TryGetList<Gs2::Guild::Model::FGuild>(ListParentKey);

                if (Range)
                {
                    Range->RemoveAll([this](const Gs2::Guild::Model::FGuildPtr& Item) { return Self->GuildModelName && Item->GetGuildModelName() != Self->GuildModelName; });
                    Range->RemoveAll([this](const Gs2::Guild::Model::FGuildPtr& Item) { return Self->DisplayName && Item->GetDisplayName() != Self->DisplayName; });
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    PageToken = TOptional<FString>();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }

            const auto Request =
                MakeShared<Gs2::Guild::Request::FSearchGuildsByUserIdRequest>()
                    ->WithContextStack(Self->Gs2->DefaultContextStack)
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithGuildModelName(Self->GuildModelName)
                    ->WithUserId(Self->UserId)
                    ->WithOrderBy(Self->OrderBy)
                    ->WithDisplayName(Self->DisplayName)
                    ->WithAttributes1(Self->Attributes1)
                    ->WithAttributes2(Self->Attributes2)
                    ->WithAttributes3(Self->Attributes3)
                    ->WithAttributes4(Self->Attributes4)
                    ->WithAttributes5(Self->Attributes5)
                    ->WithJoinPolicies(Self->JoinPolicies)
                    ->WithIncludeFullMembersGuild(Self->IncludeFullMembersGuild)
                    ->WithTimeOffsetToken(Self->TimeOffsetToken)
                    ->WithPageToken(PageToken)
                    ->WithLimit(FetchSize)
            ;
            const auto Future = Self->Client->SearchGuildsByUserId(Request);
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                ErrorValue = Future->GetTask().Error();
                bLast = true;
                return *this;
            }
            else
            {
                ErrorValue = nullptr;
            }
            const auto R = Future->GetTask().Result();
            Future->EnsureCompletion();
            Range = R->GetItems().IsValid() ? R->GetItems() : MakeShared<TArray<Gs2::Guild::Model::FGuildPtr>>();
            if (Range.IsValid())
            {
                for (const auto& Item : *Range)
                {
                    if (!Item.IsValid()) continue;
                    Gs2::Guild::Model::Cache::FGuildCache::Put(
                        Self->Gs2->Cache,
                        Request->GetNamespaceName(), Item->GetGuildModelName(), Item->GetName(),
                        TOptional<int32>(), Item
                    );
                }
            }
            Range->RemoveAll([this](const Gs2::Guild::Model::FGuildPtr& Item) { return Self->GuildModelName && Item->GetGuildModelName() != Self->GuildModelName; });
            Range->RemoveAll([this](const Gs2::Guild::Model::FGuildPtr& Item) { return Self->DisplayName && Item->GetDisplayName() != Self->DisplayName; });
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
            if (bLast && (!Self->UserId.IsSet() && !Self->Attributes1.IsValid() && !Self->Attributes2.IsValid() && !Self->Attributes3.IsValid() && !Self->Attributes4.IsValid() && !Self->Attributes5.IsValid() && !Self->JoinPolicies.IsValid() && !Self->IncludeFullMembersGuild.IsSet() && !Self->OrderBy.IsSet()))
            {
                Self->Gs2->Cache->SetListCached(
                    Gs2::Guild::Model::FGuild::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FSearchGuildsByUserIdIterator::FIterator FSearchGuildsByUserIdIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FSearchGuildsByUserIdIterator::FIterator FSearchGuildsByUserIdIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FSearchGuildsByUserIdIterator::FIterator FSearchGuildsByUserIdIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
