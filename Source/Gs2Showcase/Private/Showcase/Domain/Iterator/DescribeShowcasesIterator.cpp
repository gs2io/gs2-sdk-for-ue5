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

#include "Showcase/Domain/Iterator/DescribeShowcasesIterator.h"
#include "Showcase/Domain/Model/Showcase.h"
#include "Showcase/Domain/Model/User.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Showcase::Domain::Iterator
{

    FDescribeShowcasesIterator::FDescribeShowcasesIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Showcase::FGs2ShowcaseRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken)
    {
    }

    FDescribeShowcasesIterator::FDescribeShowcasesIterator(
        const FDescribeShowcasesIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeShowcasesIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Showcase::Model::FShowcase>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeShowcasesIterator::FIterator::FIterator(
        const TSharedRef<FDescribeShowcasesIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeShowcasesIterator::FIterator& FDescribeShowcasesIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::Showcase::Domain::Model::FUserDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->UserId(),
                "Showcase"
            );

            if (!RangeIteratorOpt)
            {
                Range = Self->Gs2->Cache->TryGetList<Gs2::Showcase::Model::FShowcase>(ListParentKey);

                if (Range)
                {
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }

            const auto Future = Self->Client->DescribeShowcases(
                MakeShared<Gs2::Showcase::Request::FDescribeShowcasesRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
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
                Self->Gs2->Cache->Put(
                    Gs2::Showcase::Model::FShowcase::TypeName,
                    ListParentKey,
                    Gs2::Showcase::Domain::Model::FShowcaseDomain::CreateCacheKey(
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
            bLast = true;
            if (bLast) {
                Self->Gs2->Cache->SetListCached(
                    Gs2::Showcase::Model::FShowcase::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeShowcasesIterator::FIterator FDescribeShowcasesIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeShowcasesIterator::FIterator FDescribeShowcasesIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeShowcasesIterator::FIterator FDescribeShowcasesIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

