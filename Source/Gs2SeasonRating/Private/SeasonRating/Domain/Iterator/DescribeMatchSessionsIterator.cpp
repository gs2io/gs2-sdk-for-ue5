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
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

// ReSharper disable CppUnusedIncludeDirective

#include "SeasonRating/Domain/Iterator/DescribeMatchSessionsIterator.h"
#include "SeasonRating/Domain/Model/MatchSession.h"
#include "SeasonRating/Domain/Model/Namespace.h"

namespace Gs2::SeasonRating::Domain::Iterator
{

    FDescribeMatchSessionsIterator::FDescribeMatchSessionsIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::SeasonRating::FGs2SeasonRatingRestClientPtr Client,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeMatchSessionsIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::SeasonRating::Model::FMatchSession>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeMatchSessionsIterator::FIterator::FIterator(
        const TSharedRef<FDescribeMatchSessionsIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeMatchSessionsIterator::FIterator& FDescribeMatchSessionsIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::SeasonRating::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                Self->NamespaceName,
                "MatchSession"
            );

            if (!RangeIteratorOpt)
            {
                Range = Self->Cache->TryGetList<Gs2::SeasonRating::Model::FMatchSession>(ListParentKey);

                if (Range)
                {
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    PageToken = TOptional<FString>();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }

            const auto Future = Self->Client->DescribeMatchSessions(
                MakeShared<Gs2::SeasonRating::Request::FDescribeMatchSessionsRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
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
                Self->Cache->Put(
                    Gs2::SeasonRating::Model::FMatchSession::TypeName,
                    ListParentKey,
                    Gs2::SeasonRating::Domain::Model::FMatchSessionDomain::CreateCacheKey(
                        Item->GetName()
                    ),
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (Range)
            {
            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
            if (bLast) {
                Self->Cache->SetListCached(
                    Gs2::SeasonRating::Model::FMatchSession::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeMatchSessionsIterator::FIterator FDescribeMatchSessionsIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeMatchSessionsIterator::FIterator FDescribeMatchSessionsIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeMatchSessionsIterator::FIterator FDescribeMatchSessionsIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

