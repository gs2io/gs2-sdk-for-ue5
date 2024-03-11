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

#include "Ranking/Domain/Iterator/DescribeScoresByUserIdIterator.h"
#include "Ranking/Domain/Model/Score.h"
#include "Ranking/Domain/Model/User.h"

namespace Gs2::Ranking::Domain::Iterator
{

    FDescribeScoresByUserIdIterator::FDescribeScoresByUserIdIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Ranking::FGs2RankingRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> CategoryName,
        const TOptional<FString> UserId,
        const TOptional<FString> ScorerUserId,
        const TOptional<FString> TimeOffsetToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        CategoryName(CategoryName),
        UserId(UserId),
        ScorerUserId(ScorerUserId),
        TimeOffsetToken(TimeOffsetToken)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeScoresByUserIdIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Ranking::Model::FScore>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeScoresByUserIdIterator::FIterator::FIterator(
        const TSharedRef<FDescribeScoresByUserIdIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeScoresByUserIdIterator::FIterator& FDescribeScoresByUserIdIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::Ranking::Domain::Model::FUserDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->UserId,
                "Score"
            );

            if (!RangeIteratorOpt)
            {
                Range = Self->Cache->TryGetList<Gs2::Ranking::Model::FScore>(ListParentKey);

                if (Range)
                {
                    Range->RemoveAll([this](const Gs2::Ranking::Model::FScorePtr& Item) { return Self->CategoryName && Item->GetCategoryName() != Self->CategoryName; });
                    Range->RemoveAll([this](const Gs2::Ranking::Model::FScorePtr& Item) { return Self->ScorerUserId && Item->GetScorerUserId() != Self->ScorerUserId; });
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    PageToken = TOptional<FString>();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }

            const auto Future = Self->Client->DescribeScoresByUserId(
                MakeShared<Gs2::Ranking::Request::FDescribeScoresByUserIdRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithCategoryName(Self->CategoryName)
                    ->WithUserId(Self->UserId)
                    ->WithScorerUserId(Self->ScorerUserId)
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
                    Gs2::Ranking::Model::FScore::TypeName,
                    ListParentKey,
                    Gs2::Ranking::Domain::Model::FScoreDomain::CreateCacheKey(
                        Item->GetCategoryName(),
                        Item->GetScorerUserId(),
                        Item->GetUniqueId()
                    ),
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (Range)
            {
                Range->RemoveAll([this](const Gs2::Ranking::Model::FScorePtr& Item) { return Self->CategoryName && Item->GetCategoryName() != Self->CategoryName; });
                Range->RemoveAll([this](const Gs2::Ranking::Model::FScorePtr& Item) { return Self->ScorerUserId && Item->GetScorerUserId() != Self->ScorerUserId; });
            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
            if (bLast) {
                Self->Cache->SetListCached(
                    Gs2::Ranking::Model::FScore::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeScoresByUserIdIterator::FIterator FDescribeScoresByUserIdIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeScoresByUserIdIterator::FIterator FDescribeScoresByUserIdIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeScoresByUserIdIterator::FIterator FDescribeScoresByUserIdIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

