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

#include "Datastore/Domain/Iterator/DescribeDataObjectHistoriesIterator.h"
#include "Datastore/Domain/Model/DataObjectHistory.h"
#include "Datastore/Domain/Model/DataObject.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Datastore::Domain::Iterator
{

    FDescribeDataObjectHistoriesIterator::FDescribeDataObjectHistoriesIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Datastore::FGs2DatastoreRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> DataObjectName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        DataObjectName(DataObjectName)
    {
    }

    FDescribeDataObjectHistoriesIterator::FDescribeDataObjectHistoriesIterator(
        const FDescribeDataObjectHistoriesIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        DataObjectName(From.DataObjectName)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeDataObjectHistoriesIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Datastore::Model::FDataObjectHistory>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeDataObjectHistoriesIterator::FIterator::FIterator(
        const TSharedRef<FDescribeDataObjectHistoriesIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeDataObjectHistoriesIterator::FIterator& FDescribeDataObjectHistoriesIterator::FIterator::operator++()
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
                Self->UserId(),
                Self->DataObjectName,
                "DataObjectHistory"
            );

            if (!RangeIteratorOpt)
            {
                Range = Self->Gs2->Cache->TryGetList<Gs2::Datastore::Model::FDataObjectHistory>(ListParentKey);

                if (Range)
                {
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    PageToken = TOptional<FString>();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }

            const auto Future = Self->Client->DescribeDataObjectHistories(
                MakeShared<Gs2::Datastore::Request::FDescribeDataObjectHistoriesRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithAccessToken(Self->AccessToken == nullptr ? TOptional<FString>() : Self->AccessToken->GetToken())
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
                Self->Gs2->Cache->Put(
                    Gs2::Datastore::Model::FDataObjectHistory::TypeName,
                    ListParentKey,
                    Gs2::Datastore::Domain::Model::FDataObjectHistoryDomain::CreateCacheKey(
                        Item->GetGeneration()
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
                Self->Gs2->Cache->SetListCached(
                    Gs2::Datastore::Model::FDataObjectHistory::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeDataObjectHistoriesIterator::FIterator FDescribeDataObjectHistoriesIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeDataObjectHistoriesIterator::FIterator FDescribeDataObjectHistoriesIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeDataObjectHistoriesIterator::FIterator FDescribeDataObjectHistoriesIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

