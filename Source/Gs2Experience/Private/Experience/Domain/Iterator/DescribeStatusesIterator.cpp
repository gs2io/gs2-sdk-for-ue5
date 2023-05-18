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

#include "Experience/Domain/Iterator/DescribeStatusesIterator.h"
#include "Experience/Domain/Model/Status.h"
#include "Experience/Domain/Model/User.h"

namespace Gs2::Experience::Domain::Iterator
{

    FDescribeStatusesIterator::FDescribeStatusesIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Experience::FGs2ExperienceRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> ExperienceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        ExperienceName(ExperienceName),
        AccessToken(AccessToken)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeStatusesIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Experience::Model::FStatus>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeStatusesIterator::FIterator::FIterator(
        const TSharedRef<FDescribeStatusesIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeStatusesIterator::FIterator& FDescribeStatusesIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::Experience::Domain::Model::FUserDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->UserId(),
                "Status"
            );
            Range = Self->Cache->TryGetList<Gs2::Experience::Model::FStatus>(ListParentKey);
            if (Range) {
                Range->RemoveAll([this](const Gs2::Experience::Model::FStatusPtr& Item) { return Self->ExperienceName && Item->GetExperienceName() != Self->ExperienceName; });
                RangeIteratorOpt = Range->CreateIterator();
                PageToken = TOptional<FString>();
                bLast = true;
                bEnd = !static_cast<bool>(*RangeIteratorOpt);
                return *this;
            }
            const auto Future = Self->Client->DescribeStatuses(
                MakeShared<Gs2::Experience::Request::FDescribeStatusesRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithExperienceName(Self->ExperienceName)
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
                    Gs2::Experience::Model::FStatus::TypeName,
                    ListParentKey,
                    Gs2::Experience::Domain::Model::FStatusDomain::CreateCacheKey(
                        Item->GetExperienceName(),
                        Item->GetPropertyId()
                    ),
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
            if (bLast) {
                Self->Cache->SetListCache(
                    Gs2::Experience::Model::FStatus::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeStatusesIterator::FIterator FDescribeStatusesIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeStatusesIterator::FIterator FDescribeStatusesIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeStatusesIterator::FIterator FDescribeStatusesIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

