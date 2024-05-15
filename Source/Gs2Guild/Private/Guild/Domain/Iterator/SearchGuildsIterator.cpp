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

#include "Guild/Domain/Iterator/SearchGuildsIterator.h"

#include "Core/Domain/Gs2.h"
#include "Guild/Domain/Model/Guild.h"
#include "Guild/Domain/Model/Namespace.h"

namespace Gs2::Guild::Domain::Iterator
{

    FSearchGuildsIterator::FSearchGuildsIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Guild::FGs2GuildRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> GuildModelName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> DisplayName,
        const TSharedPtr<TArray<int32>> Attributes1,
        const TSharedPtr<TArray<int32>> Attributes2,
        const TSharedPtr<TArray<int32>> Attributes3,
        const TSharedPtr<TArray<int32>> Attributes4,
        const TSharedPtr<TArray<int32>> Attributes5,
        const TSharedPtr<TArray<FString>> JoinPolicies,
        const TOptional<bool> IncludeFullMembersGuild
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client),
        NamespaceName(NamespaceName),
        GuildModelName(GuildModelName),
        AccessToken(AccessToken),
        DisplayName(DisplayName),
        Attributes1(Attributes1),
        Attributes2(Attributes2),
        Attributes3(Attributes3),
        Attributes4(Attributes4),
        Attributes5(Attributes5),
        JoinPolicies(JoinPolicies),
        IncludeFullMembersGuild(IncludeFullMembersGuild)
    {
        
    }

    FSearchGuildsIterator::FSearchGuildsIterator(
        const FSearchGuildsIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        GuildModelName(From.GuildModelName),
        AccessToken(From.AccessToken),
        DisplayName(From.DisplayName),
        Attributes1(From.Attributes1),
        Attributes2(From.Attributes2),
        Attributes3(From.Attributes3),
        Attributes4(From.Attributes4),
        Attributes5(From.Attributes5),
        JoinPolicies(From.JoinPolicies),
        IncludeFullMembersGuild(From.IncludeFullMembersGuild)
    {
        
    }

    Gs2::Core::Model::FGs2ErrorPtr FSearchGuildsIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Guild::Model::FGuild>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FSearchGuildsIterator::FIterator::FIterator(
        const TSharedRef<FSearchGuildsIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FSearchGuildsIterator::FIterator& FSearchGuildsIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::Guild::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                Self->NamespaceName,
                "Guild"
            );
            const auto Future = Self->Client->SearchGuilds(
                MakeShared<Gs2::Guild::Request::FSearchGuildsRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithGuildModelName(Self->GuildModelName)
                    ->WithAccessToken(Self->AccessToken == nullptr ? TOptional<FString>() : Self->AccessToken->GetToken())
                    ->WithDisplayName(Self->DisplayName)
                    ->WithAttributes1(Self->Attributes1)
                    ->WithAttributes2(Self->Attributes2)
                    ->WithAttributes3(Self->Attributes3)
                    ->WithAttributes4(Self->Attributes4)
                    ->WithAttributes5(Self->Attributes5)
                    ->WithJoinPolicies(Self->JoinPolicies)
                    ->WithIncludeFullMembersGuild(Self->IncludeFullMembersGuild)
                    ->WithPageToken(PageToken)
                    ->WithLimit(FetchSize)
            );
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
            Range = R->GetItems();
            for (auto Item : *R->GetItems())
            {
                Self->Gs2->Cache->Put(
                    Gs2::Guild::Model::FGuild::TypeName,
                    ListParentKey,
                    Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheKey(
                        Item->GetGuildModelName(),
                        Item->GetName()
                    ),
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FSearchGuildsIterator::FIterator FSearchGuildsIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FSearchGuildsIterator::FIterator FSearchGuildsIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FSearchGuildsIterator::FIterator FSearchGuildsIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

