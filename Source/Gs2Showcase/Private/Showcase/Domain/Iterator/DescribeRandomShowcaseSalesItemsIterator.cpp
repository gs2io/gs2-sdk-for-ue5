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

#include "Showcase/Domain/Iterator/DescribeRandomShowcaseSalesItemsIterator.h"
#include "Showcase/Domain/Model/RandomShowcase.h"
#include "Showcase/Domain/Model/User.h"

namespace Gs2::Showcase::Domain::Iterator
{

    FDescribeRandomShowcaseSalesItemsIterator::FDescribeRandomShowcaseSalesItemsIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Showcase::FGs2ShowcaseRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> ShowcaseName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        ShowcaseName(ShowcaseName),
        AccessToken(AccessToken)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeRandomShowcaseSalesItemsIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FRandomDisplayItem>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeRandomShowcaseSalesItemsIterator::FIterator::FIterator(
        const TSharedRef<FDescribeRandomShowcaseSalesItemsIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeRandomShowcaseSalesItemsIterator::FIterator& FDescribeRandomShowcaseSalesItemsIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::Showcase::Domain::Model::FRandomShowcaseDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->UserId(),
                Self->ShowcaseName,
                "RandomDisplayItem"
            );

            if (!RangeIteratorOpt)
            {
                Range = Self->Cache->TryGetList<Gs2::Showcase::Model::FRandomDisplayItem>(ListParentKey);

                if (Range)
                {
                    Range->RemoveAll([this](const Gs2::Showcase::Model::FRandomDisplayItemPtr& Item) { return Self->ShowcaseName && Item->GetShowcaseName() != Self->ShowcaseName; });
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }

            const auto Future = Self->Client->DescribeRandomShowcaseSalesItems(
                MakeShared<Gs2::Showcase::Request::FDescribeRandomShowcaseSalesItemsRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithShowcaseName(Self->ShowcaseName)
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
                    Gs2::Showcase::Model::FRandomDisplayItem::TypeName,
                    ListParentKey,
                    Gs2::Showcase::Domain::Model::FRandomShowcaseDomain::CreateCacheKey(
                        Item->GetName()
                    ),
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            RangeIteratorOpt = Range->CreateIterator();
            bLast = true;
            if (bLast) {
                Self->Cache->SetListCached(
                    Gs2::Showcase::Model::FRandomDisplayItem::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeRandomShowcaseSalesItemsIterator::FIterator FDescribeRandomShowcaseSalesItemsIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeRandomShowcaseSalesItemsIterator::FIterator FDescribeRandomShowcaseSalesItemsIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeRandomShowcaseSalesItemsIterator::FIterator FDescribeRandomShowcaseSalesItemsIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

