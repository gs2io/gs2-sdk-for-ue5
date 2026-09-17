
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

#include "Friend/Domain/Iterator/DescribeReceiveRequestsByUserIdIterator.h"
#include "Friend/Domain/Model/ReceiveFriendRequest.h"
#include "Friend/Domain/Model/User.h"

#include "Core/Domain/Gs2.h"

#include "Friend/Model/Cache/ReceiveFriendRequest.h"
#include "Friend/Model/Cache/FriendRequest.h"

namespace Gs2::Friend::Domain::Iterator
{

    FDescribeReceiveRequestsByUserIdIterator::FDescribeReceiveRequestsByUserIdIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Friend::FGs2FriendRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> TimeOffsetToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client),
        NamespaceName(NamespaceName),
        UserId(UserId),
        TimeOffsetToken(TimeOffsetToken)
    {
    }

    FDescribeReceiveRequestsByUserIdIterator::FDescribeReceiveRequestsByUserIdIterator(
        const FDescribeReceiveRequestsByUserIdIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        TimeOffsetToken(From.TimeOffsetToken)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeReceiveRequestsByUserIdIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Friend::Model::FReceiveFriendRequest>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeReceiveRequestsByUserIdIterator::FIterator::FIterator(
        const TSharedRef<FDescribeReceiveRequestsByUserIdIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeReceiveRequestsByUserIdIterator::FIterator& FDescribeReceiveRequestsByUserIdIterator::FIterator::operator++()
    {
                if (bEnd) return *this;

        if (ErrorValue && bLast)
        {
            bEnd = true;
            return *this;
        }

        if (RangeIteratorOpt && *RangeIteratorOpt) ++*RangeIteratorOpt;

        // Keep the previous page alive until its iterator has been replaced.
        const auto PreviousRange = Range;
        if (!RangeIteratorOpt || (!*RangeIteratorOpt && !bLast))
        {
            const auto ListParentKey = Gs2::Friend::Model::Cache::FReceiveFriendRequestCache::CreateCacheParentKey(
                Self->NamespaceName,
                Self->UserId,
                TOptional<int32>()
            );
            if (!RangeIteratorOpt)
            {
                Range = Self->Gs2->Cache->TryGetList<Gs2::Friend::Model::FReceiveFriendRequest>(ListParentKey);

                if (Range)
                {
                    Range->RemoveAll([this](const Gs2::Friend::Model::FReceiveFriendRequestPtr& Item) { return Self->UserId && Item->GetTargetUserId() != Self->UserId; });
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    PageToken = TOptional<FString>();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }
            const auto Request =
                MakeShared<Gs2::Friend::Request::FDescribeReceiveRequestsByUserIdRequest>()
                    ->WithContextStack(Self->Gs2->DefaultContextStack)
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithUserId(Self->UserId)
                    ->WithPageToken(PageToken)
                    ->WithLimit(FetchSize)
            ;
            const auto Future = Self->Client->DescribeReceiveRequestsByUserId(Request);
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
            const auto ProjectedRange = MakeShared<TArray<Gs2::Friend::Model::FReceiveFriendRequestPtr>>();
            if (R.IsValid() && R->GetItems().IsValid())
            {
                for (const auto& Item : *R->GetItems())
                {
                    if (Item.IsValid() && Item->GetUserId().IsSet() && Item->GetTargetUserId().IsSet())
                    {
                        ProjectedRange->Add(MakeShared<Gs2::Friend::Model::FReceiveFriendRequest>()
                            ->WithUserId(Item->GetUserId())
                            ->WithTargetUserId(Item->GetTargetUserId()));
                    }
                    else
                    {
                        const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                        Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("item"), TEXT("item is required."), TEXT("required")));
                        ErrorValue = MakeShared<Gs2::Core::Model::FUnknownError>(Details);
                        bLast = true;
                        return *this;
                    }
                }
            }
            Range = ProjectedRange;
            const auto ResultModel = R;


            if (Range.IsValid())
            {
                for (const auto& Item : *Range)
                {
                    if (!Item.IsValid()) continue;
                    Gs2::Friend::Model::Cache::FReceiveFriendRequestCache::Put(
                        Self->Gs2->Cache,
                        Request->GetNamespaceName(), Request->GetUserId(), Item->GetUserId(),
                        TOptional<int32>(), Item
                    );
                }
            }
            if (Range)
            {
                Range->RemoveAll([this](const Gs2::Friend::Model::FReceiveFriendRequestPtr& Item) { return Self->UserId && Item->GetTargetUserId() != Self->UserId; });
            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
            if (bLast) {
                Self->Gs2->Cache->SetListCached(
                    Gs2::Friend::Model::FReceiveFriendRequest::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeReceiveRequestsByUserIdIterator::FIterator FDescribeReceiveRequestsByUserIdIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeReceiveRequestsByUserIdIterator::FIterator FDescribeReceiveRequestsByUserIdIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeReceiveRequestsByUserIdIterator::FIterator FDescribeReceiveRequestsByUserIdIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

