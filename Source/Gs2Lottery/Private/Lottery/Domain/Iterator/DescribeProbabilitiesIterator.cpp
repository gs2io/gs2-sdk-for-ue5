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

#include "Lottery/Domain/Iterator/DescribeProbabilitiesIterator.h"
#include "Lottery/Domain/Model/Probability.h"
#include "Lottery/Domain/Model/User.h"

namespace Gs2::Lottery::Domain::Iterator
{

    FDescribeProbabilitiesIterator::FDescribeProbabilitiesIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Lottery::FGs2LotteryRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> LotteryName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        LotteryName(LotteryName),
        AccessToken(AccessToken)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeProbabilitiesIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FProbability>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeProbabilitiesIterator::FIterator::FIterator(
        const TSharedRef<FDescribeProbabilitiesIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeProbabilitiesIterator::FIterator& FDescribeProbabilitiesIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::Lottery::Domain::Model::FUserDomain::CreateCacheParentKey(
            Self->NamespaceName,
            Self->UserId(),
            "Probability"
        );
            if (Self->Cache->IsListCached(
                Gs2::Lottery::Model::FProbability::TypeName,
                ListParentKey
            )) {
                Range = MakeShared<TArray<Gs2::Lottery::Model::FProbabilityPtr>>();
                *Range = Self->Cache->List<Gs2::Lottery::Model::FProbability>(
                    ListParentKey
                );
                RangeIteratorOpt = Range->CreateIterator();
                bLast = true;
                bEnd = static_cast<bool>(*RangeIteratorOpt);
                return *this;
            }
            const auto Future = Self->Client->DescribeProbabilities(
                MakeShared<Gs2::Lottery::Request::FDescribeProbabilitiesRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithLotteryName(Self->LotteryName)
                    ->WithAccessToken(Self->AccessToken == nullptr ? TOptional<FString>() : Self->AccessToken->GetToken())
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
                    ),
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            RangeIteratorOpt = Range->CreateIterator();
            bLast = true;
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeProbabilitiesIterator::FIterator FDescribeProbabilitiesIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeProbabilitiesIterator::FIterator FDescribeProbabilitiesIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeProbabilitiesIterator::FIterator FDescribeProbabilitiesIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

