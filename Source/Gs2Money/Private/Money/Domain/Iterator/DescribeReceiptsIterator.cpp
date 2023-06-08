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

#include "Money/Domain/Iterator/DescribeReceiptsIterator.h"
#include "Money/Domain/Model/Receipt.h"
#include "Money/Domain/Model/User.h"

namespace Gs2::Money::Domain::Iterator
{

    FDescribeReceiptsIterator::FDescribeReceiptsIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Money::FGs2MoneyRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<int32> Slot,
        const TOptional<int64> Begin,
        const TOptional<int64> End
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        UserId(UserId),
        Slot(Slot),
        Begin(Begin),
        End(End)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeReceiptsIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Money::Model::FReceipt>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeReceiptsIterator::FIterator::FIterator(
        const TSharedRef<FDescribeReceiptsIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeReceiptsIterator::FIterator& FDescribeReceiptsIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::Money::Domain::Model::FUserDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->UserId,
                "Receipt"
            );

            if (!RangeIteratorOpt)
            {
                Range = Self->Cache->TryGetList<Gs2::Money::Model::FReceipt>(ListParentKey);

                if (Range)
                {
                    Range->RemoveAll([this](const Gs2::Money::Model::FReceiptPtr& Item) { return Self->Slot && Item->GetSlot() != Self->Slot; });
                    Range->RemoveAll([this](const Gs2::Money::Model::FReceiptPtr& Item) { return Self->Begin && *Item->GetCreatedAt() < *Self->Begin; });
                    Range->RemoveAll([this](const Gs2::Money::Model::FReceiptPtr& Item) { return Self->End && *Item->GetCreatedAt() > *Self->End; });
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    PageToken = TOptional<FString>();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }

            const auto Future = Self->Client->DescribeReceipts(
                MakeShared<Gs2::Money::Request::FDescribeReceiptsRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithUserId(Self->UserId)
                    ->WithSlot(Self->Slot)
                    ->WithBegin(Self->Begin)
                    ->WithEnd(Self->End)
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
                    Gs2::Money::Model::FReceipt::TypeName,
                    ListParentKey,
                    Gs2::Money::Domain::Model::FReceiptDomain::CreateCacheKey(
                        Item->GetTransactionId()
                    ),
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
            if (bLast) {
                Self->Cache->SetListCached(
                    Gs2::Money::Model::FReceipt::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeReceiptsIterator::FIterator FDescribeReceiptsIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeReceiptsIterator::FIterator FDescribeReceiptsIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeReceiptsIterator::FIterator FDescribeReceiptsIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

