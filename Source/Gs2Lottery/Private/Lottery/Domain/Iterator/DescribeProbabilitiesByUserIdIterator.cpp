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

#include "Lottery/Domain/Iterator/DescribeProbabilitiesByUserIdIterator.h"
#include "Lottery/Domain/Model/Lottery.h"
#include "Lottery/Domain/Model/Probability.h"

namespace Gs2::Lottery::Domain::Iterator
{

    FDescribeProbabilitiesByUserIdIterator::FDescribeProbabilitiesByUserIdIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Lottery::FGs2LotteryRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> LotteryName,
        const TOptional<FString> UserId,
        const TOptional<FString> TimeOffsetToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        LotteryName(LotteryName),
        UserId(UserId),
        TimeOffsetToken(TimeOffsetToken)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeProbabilitiesByUserIdIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FProbability>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeProbabilitiesByUserIdIterator::FIterator::FIterator(
        const TSharedRef<FDescribeProbabilitiesByUserIdIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeProbabilitiesByUserIdIterator::FIterator& FDescribeProbabilitiesByUserIdIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::Lottery::Domain::Model::FLotteryDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->UserId,
                Self->LotteryName,
                "Probability"
            );

            if (!RangeIteratorOpt)
            {
                Range = Self->Cache->TryGetList<Gs2::Lottery::Model::FProbability>(ListParentKey);

                if (Range)
                {
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }

            const auto Future = Self->Client->DescribeProbabilitiesByUserId(
                MakeShared<Gs2::Lottery::Request::FDescribeProbabilitiesByUserIdRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithLotteryName(Self->LotteryName)
                    ->WithUserId(Self->UserId)
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
                    Gs2::Lottery::Model::FProbability::TypeName,
                    ListParentKey,
                    Gs2::Lottery::Domain::Model::FProbabilityDomain::CreateCacheKey(
                        Item->GetPrize().IsValid() && Item->GetPrize()->GetPrizeId().IsSet() ? Item->GetPrize()->GetPrizeId() : TOptional<FString>()
                    ),
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (Range)
            {
            }
            RangeIteratorOpt = Range->CreateIterator();
            bLast = true;
            if (bLast) {
                Self->Cache->SetListCached(
                    Gs2::Lottery::Model::FProbability::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeProbabilitiesByUserIdIterator::FIterator FDescribeProbabilitiesByUserIdIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeProbabilitiesByUserIdIterator::FIterator FDescribeProbabilitiesByUserIdIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeProbabilitiesByUserIdIterator::FIterator FDescribeProbabilitiesByUserIdIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

