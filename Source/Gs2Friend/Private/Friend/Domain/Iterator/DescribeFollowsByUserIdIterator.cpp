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

#include "Friend/Domain/Iterator/DescribeFollowsByUserIdIterator.h"
#include "Friend/Domain/Model/FollowUser.h"
#include "Friend/Domain/Model/Follow.h"

namespace Gs2::Friend::Domain::Iterator
{

    FDescribeFollowsByUserIdIterator::FDescribeFollowsByUserIdIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Friend::FGs2FriendRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<bool> WithProfile
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        UserId(UserId),
        WithProfile(WithProfile)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeFollowsByUserIdIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Friend::Model::FFollowUser>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeFollowsByUserIdIterator::FIterator::FIterator(
        const TSharedRef<FDescribeFollowsByUserIdIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeFollowsByUserIdIterator::FIterator& FDescribeFollowsByUserIdIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::Friend::Domain::Model::FFollowDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->UserId,
                Self->WithProfile.IsSet() ? *Self->WithProfile ? TOptional<FString>("True") : TOptional<FString>("False") : TOptional<FString>("False"),
                FString("FollowUser:") + (Self->WithProfile.IsSet() ? *Self->WithProfile == true ? "True" : "False" : "False")
            );

            if (!RangeIteratorOpt)
            {
                Range = Self->Cache->TryGetList<Gs2::Friend::Model::FFollowUser>(ListParentKey);

                if (Range)
                {
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    PageToken = TOptional<FString>();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }

            const auto Future = Self->Client->DescribeFollowsByUserId(
                MakeShared<Gs2::Friend::Request::FDescribeFollowsByUserIdRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithUserId(Self->UserId)
                    ->WithWithProfile(Self->WithProfile)
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
                    Gs2::Friend::Model::FFollowUser::TypeName,
                    ListParentKey,
                    Gs2::Friend::Domain::Model::FFollowUserDomain::CreateCacheKey(
                        Item->GetUserId()
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
                    Gs2::Friend::Model::FFollowUser::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeFollowsByUserIdIterator::FIterator FDescribeFollowsByUserIdIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeFollowsByUserIdIterator::FIterator FDescribeFollowsByUserIdIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeFollowsByUserIdIterator::FIterator FDescribeFollowsByUserIdIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

