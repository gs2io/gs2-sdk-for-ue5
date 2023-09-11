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

#include "Enchant/Domain/Iterator/DescribeRarityParameterStatusesIterator.h"
#include "Enchant/Domain/Model/RarityParameterStatus.h"
#include "Enchant/Domain/Model/User.h"

namespace Gs2::Enchant::Domain::Iterator
{

    FDescribeRarityParameterStatusesIterator::FDescribeRarityParameterStatusesIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Enchant::FGs2EnchantRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> ParameterName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParameterName(ParameterName)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeRarityParameterStatusesIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Enchant::Model::FRarityParameterStatus>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeRarityParameterStatusesIterator::FIterator::FIterator(
        const TSharedRef<FDescribeRarityParameterStatusesIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeRarityParameterStatusesIterator::FIterator& FDescribeRarityParameterStatusesIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::Enchant::Domain::Model::FUserDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->UserId(),
                "RarityParameterStatus"
            );

            if (!RangeIteratorOpt)
            {
                Range = Self->Cache->TryGetList<Gs2::Enchant::Model::FRarityParameterStatus>(ListParentKey);

                if (Range)
                {
                    Range->RemoveAll([this](const Gs2::Enchant::Model::FRarityParameterStatusPtr& Item) { return Self->ParameterName && Item->GetParameterName() != Self->ParameterName; });
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    PageToken = TOptional<FString>();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }

            const auto Future = Self->Client->DescribeRarityParameterStatuses(
                MakeShared<Gs2::Enchant::Request::FDescribeRarityParameterStatusesRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
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
                Self->Cache->Put(
                    Gs2::Enchant::Model::FRarityParameterStatus::TypeName,
                    ListParentKey,
                    Gs2::Enchant::Domain::Model::FRarityParameterStatusDomain::CreateCacheKey(
                        Item->GetParameterName(),
                        Item->GetPropertyId()
                    ),
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (Range)
            {
                Range->RemoveAll([this](const Gs2::Enchant::Model::FRarityParameterStatusPtr& Item) { return Self->ParameterName && Item->GetParameterName() != Self->ParameterName; });
            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
            if (bLast) {
                Self->Cache->SetListCached(
                    Gs2::Enchant::Model::FRarityParameterStatus::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeRarityParameterStatusesIterator::FIterator FDescribeRarityParameterStatusesIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeRarityParameterStatusesIterator::FIterator FDescribeRarityParameterStatusesIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeRarityParameterStatusesIterator::FIterator FDescribeRarityParameterStatusesIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

