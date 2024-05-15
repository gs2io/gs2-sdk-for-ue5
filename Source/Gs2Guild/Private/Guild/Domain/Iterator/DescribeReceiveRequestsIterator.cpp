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

#include "Guild/Domain/Iterator/DescribeReceiveRequestsIterator.h"

#include "Core/Domain/Gs2.h"
#include "Guild/Domain/Model/ReceiveMemberRequest.h"
#include "Guild/Domain/Model/Guild.h"

namespace Gs2::Guild::Domain::Iterator
{

    FDescribeReceiveRequestsIterator::FDescribeReceiveRequestsIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Guild::FGs2GuildRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> GuildModelName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client),
        NamespaceName(NamespaceName),
        GuildModelName(GuildModelName),
        AccessToken(AccessToken)
    {
    }

    FDescribeReceiveRequestsIterator::FDescribeReceiveRequestsIterator(
        const FDescribeReceiveRequestsIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        GuildModelName(From.GuildModelName),
        AccessToken(From.AccessToken)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeReceiveRequestsIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Guild::Model::FReceiveMemberRequest>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeReceiveRequestsIterator::FIterator::FIterator(
        const TSharedRef<FDescribeReceiveRequestsIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeReceiveRequestsIterator::FIterator& FDescribeReceiveRequestsIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->GuildModelName,
                Self->GuildName(),
                "ReceiveMemberRequest"
            );

            if (!RangeIteratorOpt)
            {
                Range = Self->Gs2->Cache->TryGetList<Gs2::Guild::Model::FReceiveMemberRequest>(ListParentKey);

                if (Range)
                {
                    Range->RemoveAll([this](const Gs2::Guild::Model::FReceiveMemberRequestPtr& Item) { return Self->AccessToken && Item->GetTargetGuildName() != Self->GuildName(); });
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    PageToken = TOptional<FString>();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }

            const auto Future = Self->Client->DescribeReceiveRequests(
                MakeShared<Gs2::Guild::Request::FDescribeReceiveRequestsRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithGuildModelName(Self->GuildModelName)
                    ->WithAccessToken(Self->AccessToken == nullptr ? TOptional<FString>() : Self->AccessToken->GetToken())
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
                    Gs2::Guild::Model::FReceiveMemberRequest::TypeName,
                    ListParentKey,
                    Gs2::Guild::Domain::Model::FReceiveMemberRequestDomain::CreateCacheKey(
                        Item->GetUserId()
                    ),
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (Range)
            {
                Range->RemoveAll([this](const Gs2::Guild::Model::FReceiveMemberRequestPtr& Item) { return Self->AccessToken && Item->GetTargetGuildName() != Self->GuildName(); });
            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
            if (bLast) {
                Self->Gs2->Cache->SetListCached(
                    Gs2::Guild::Model::FReceiveMemberRequest::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeReceiveRequestsIterator::FIterator FDescribeReceiveRequestsIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeReceiveRequestsIterator::FIterator FDescribeReceiveRequestsIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeReceiveRequestsIterator::FIterator FDescribeReceiveRequestsIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

