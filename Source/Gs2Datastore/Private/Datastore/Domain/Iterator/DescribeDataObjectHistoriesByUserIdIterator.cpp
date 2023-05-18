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

#include "Datastore/Domain/Iterator/DescribeDataObjectHistoriesByUserIdIterator.h"
#include "Datastore/Domain/Model/DataObjectHistory.h"
#include "Datastore/Domain/Model/DataObject.h"

namespace Gs2::Datastore::Domain::Iterator
{

    FDescribeDataObjectHistoriesByUserIdIterator::FDescribeDataObjectHistoriesByUserIdIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Datastore::FGs2DatastoreRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> DataObjectName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        UserId(UserId),
        DataObjectName(DataObjectName)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeDataObjectHistoriesByUserIdIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Datastore::Model::FDataObjectHistory>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeDataObjectHistoriesByUserIdIterator::FIterator::FIterator(
        const TSharedRef<FDescribeDataObjectHistoriesByUserIdIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeDataObjectHistoriesByUserIdIterator::FIterator& FDescribeDataObjectHistoriesByUserIdIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::Datastore::Domain::Model::FDataObjectDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->UserId,
                Self->DataObjectName,
                "DataObjectHistory"
            );
            Range = Self->Cache->TryGetList<Gs2::Datastore::Model::FDataObjectHistory>(ListParentKey);
            if (Range) {
                RangeIteratorOpt = Range->CreateIterator();
                PageToken = TOptional<FString>();
                bLast = true;
                bEnd = !static_cast<bool>(*RangeIteratorOpt);
                return *this;
            }
            const auto Future = Self->Client->DescribeDataObjectHistoriesByUserId(
                MakeShared<Gs2::Datastore::Request::FDescribeDataObjectHistoriesByUserIdRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithUserId(Self->UserId)
                    ->WithDataObjectName(Self->DataObjectName)
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
                    Gs2::Datastore::Model::FDataObjectHistory::TypeName,
                    ListParentKey,
                    Gs2::Datastore::Domain::Model::FDataObjectHistoryDomain::CreateCacheKey(
                        Item->GetGeneration()
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
                    Gs2::Datastore::Model::FDataObjectHistory::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeDataObjectHistoriesByUserIdIterator::FIterator FDescribeDataObjectHistoriesByUserIdIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeDataObjectHistoriesByUserIdIterator::FIterator FDescribeDataObjectHistoriesByUserIdIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeDataObjectHistoriesByUserIdIterator::FIterator FDescribeDataObjectHistoriesByUserIdIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

